# StarTrek — Documentation Technique

> Projet C++ — Serveur REST de gestion d'univers Star Trek  
> Auteur : LALIN Romain

---

## Table des matières

1. [Vue d'ensemble](#vue-densemble)
2. [Prérequis & dépendances](#prérequis--dépendances)
3. [Compilation](#compilation)
4. [Lancement du serveur](#lancement-du-serveur)
5. [Diagramme de classes](#diagramme-de-classes)
6. [Entités du monde — structures JSON complètes](#entités-du-monde--structures-json-complètes)
7. [Règles métier](#règles-métier)
8. [Base de données JSON](#base-de-données-json)
9. [API REST](#api-rest)
10. [Authentification](#authentification)
11. [Codes d'erreur](#codes-derreur)

---

## Vue d'ensemble

StarTrek est un serveur REST écrit en C++ (standard C++17) qui expose une API permettant de gérer un univers de jeu de type Star Trek : planètes, vaisseaux, personnages (héros, PNJ, méchants), missions, objets et grades. L'état du monde est persisté dans un fichier `bdd.json` local.

Le serveur écoute sur le port `8888` et accepte des requêtes HTTP avec authentification par token JWT.

---

## Prérequis & dépendances

| Dépendance | Usage |
|---|---|
| `clang++` (C++17) | Compilation |
| `Boost.Asio` | Serveur TCP asynchrone |
| `Boost.Beast` | Couche HTTP |
| `Boost.JSON` | Sérialisation / désérialisation JSON |
| `OpenSSL` (`libssl`, `libcrypto`) | Génération des tokens JWT (HMAC-SHA256) |
| `libpthread` | Multi-threading (une session = un thread) |

---

## Compilation

```bash
# Build de production
make

# Build de debug (active les logs avec -DDEBUG)
make debug

# Build avec tests unitaires
make test

# Nettoyage
make clean
make fclean

# Recompilation complète
make re
```

Les binaires produits sont respectivement `star_trek`, `star_trek_debug` et `star_trek_test`.

---

## Lancement du serveur

```bash
./star_trek
```

Au démarrage, le serveur :
1. Charge (ou crée) le fichier `bdd.json` dans le répertoire courant.
2. Reconstruit les relations en mémoire (inventaires, équipages, habitants, grades).
3. Commence à écouter sur `0.0.0.0:8888`.

Toutes les routes sont préfixées par `/v1`.

---

## Diagramme de classes

```
┌─────────────────────────────────────────────────────────────────────────────────┐
│ COUCHE DONNÉES                                                                  │
│                                                                                 │
│  World  ──────────────────────────────── (maps de toutes les entités)           │
│    └── LifeDoor  ─────────────────────── (add / delete sur chaque entité)       │
└─────────────────────────────────────────────────────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────────────────────────────────────────────┐
│ COUCHE RÈGLES MÉTIER (héritage virtuel multiple)                                │
│                                                                                 │
│  RuleItem        ◄─── LifeDoor                                                  │
│    └── RuleQuidam                                                               │
│         ├── RuleGrade     (hérite aussi de RuleQuidam)                          │
│         ├── RuleMission   (hérite aussi de LifeDoor)                            │
│         ├── RulePlanete   (hérite aussi de RuleQuidam)                          │
│         └── RuleSpaceship (hérite aussi de RuleQuidam)                          │
│              └── Rule  ──── (façade : agrège les 4 Rule* + dispatch)            │
└─────────────────────────────────────────────────────────────────────────────────┘
         │
         ▼
┌─────────────────────────────────────────────────────────────────────────────────┐
│ COUCHE HTTP                                                                     │
│                                                                                 │
│  Controller ──── (hérite de Rule)                                               │
│    ├── possède Server  ──── (accepteur TCP, 1 thread / connexion)               │
│    └── possède Router  ──── (matching verbe + pattern {param})                  │
│                   └── utilise Context ── (req + res + params extraits)          │
└─────────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────────┐
│ OBJETS MÉTIER                                                                   │
│                                                                                 │
│  Attribut          (AP, HP, DP)                                                 │
│  Inventory         (map<int, unique_ptr<Item>>, max 5 slots)                    │
│  AQuidam           hérite de Attribut + Inventory                               │
│    ├── Heros                                                                    │
│    ├── Pnj                                                                      │
│    └── Evil                                                                     │
│  Spaceship         hérite de Attribut + Inventory                               │
│  Planete           (liste de weak_ptr<AQuidam> habitants)                       │
│  Mission           (nom, description, is_complete)                              │
│  Item              (effet AP/HP/DP, propriétaire optionnel)                     │
│  Grade             (liste de weak_ptr<AQuidam> membres)                         │
│  Token             (JWT HS256)                                                  │
└─────────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────────┐
│ BUILDERS (pattern fluent)                                                       │
│                                                                                 │
│  AttributBuilder<T>    (withAp / withHp / withDp — template CRTP)              │
│    ├── AQuidamBuilder  → Heros / Pnj / Evil                                    │
│    └── SpaceshipBuilder                                                         │
│  PlaneteBuilder                                                                 │
│  MissionBuilder                                                                 │
│  ItemBuilder                                                                    │
│  GradeBuilder                                                                   │
└─────────────────────────────────────────────────────────────────────────────────┘
```

### Notes sur la gestion mémoire

| Entité | Type de pointeur | Raison |
|---|---|---|
| `Heros`, `Pnj`, `Evil`, `Spaceship`, `Planete`, `Mission`, `Grade`, `Token` | `shared_ptr` | Plusieurs structures peuvent référencer la même instance |
| `Item` dans `World::_items` | `unique_ptr` | Propriétaire unique ; transféré via `std::move` lors d'un échange |
| `Item` dans `Inventory::_inventory` | `unique_ptr` | Slot exclusif ; l'item ne peut appartenir qu'à un seul inventaire à la fois |
| Références depuis `Planete::_habitants`, `Spaceship::_equipage`, `Grade::_membre` | `weak_ptr<AQuidam>` | Évite les cycles de référence ; l'entité peut être détruite sans dangling pointer |

---

## Entités du monde — structures JSON complètes

### Identifiants de type (`OBJETS` enum)

| Valeur | Constante | Description |
|---|---|---|
| -1 | `NONE` | Aucun / item sans propriétaire |
| 0 | `PLANETE` | Planète |
| 1 | `SPACESHIP` | Vaisseau spatial |
| 2 | `HEROS` | Personnage joueur |
| 3 | `PNJ` | Personnage non joueur |
| 4 | `EVIL` | Méchant |
| 5 | `MISSION` | Mission |
| 6 | `ITEM` | Objet |
| 7 | `GRADE` | Grade / rang |
| 9 | `TOKEN` | Token JWT |

---

### Planète

```json
{
  "id": 1,
  "name": "Fury",
  "description": "Seul un furien peut y vivre"
}
```

| Champ | Type | Requis | Description |
|---|---|---|---|
| `id` | int | oui (lecture) | Identifiant unique, auto-incrémenté à la création |
| `name` | string | oui | Nom de la planète |
| `description` | string | oui | Description libre |

---

### Vaisseau spatial (Spaceship)

```json
{
  "id": 1,
  "name": "Odyssey",
  "description": "Le vaisseau de la mort",
  "ap": 200,
  "dp": 150,
  "hp": 1000
}
```

| Champ | Type | Requis | Description |
|---|---|---|---|
| `id` | int | oui (lecture) | Identifiant unique |
| `name` | string | oui | Nom du vaisseau |
| `description` | string | oui | Description libre |
| `ap` | int | oui | Points d'attaque |
| `dp` | int | oui | Points de défense |
| `hp` | int | oui | Points de vie |

Le vaisseau possède un inventaire de 5 slots (`unique_ptr<Item>`) et une liste d'équipage (`weak_ptr<AQuidam>`).

---

### Personnage jouable — Heros / PNJ / Evil

Les trois types partagent exactement la même structure JSON. Seule la clé de section dans `bdd.json` diffère (`"2"`, `"3"`, `"4"`), et dans les requêtes le champ `entity_type` indique le type.

```json
{
  "id": 1,
  "name": "Alex",
  "ap": 80,
  "hp": 100,
  "dp": 25,
  "id_planet": 0,
  "id_ship": 1,
  "id_planet_origin": 1,
  "id_grade": 0
}
```

| Champ | Type | Requis | Description |
|---|---|---|---|
| `id` | int | oui (lecture) | Identifiant unique |
| `name` | string | oui | Nom du personnage |
| `ap` | int | oui | Points d'attaque |
| `hp` | int | oui | Points de vie |
| `dp` | int | oui | Points de défense |
| `id_planet` | int | oui | Planète actuelle (`0` = aucune) |
| `id_ship` | int | oui | Vaisseau actuel (`0` = aucun) |
| `id_planet_origin` | int | oui | Planète d'origine (obligatoire > 0) |
| `id_grade` | int | oui | Grade actuel (`0` = aucun) |

Chaque personnage possède un inventaire de 5 slots.

---

### Mission

```json
{
  "id": 1,
  "name": "Sauver Dr Landra",
  "description": "une description de mission",
  "is_complete": false
}
```

| Champ | Type | Requis | Description |
|---|---|---|---|
| `id` | int | oui (lecture) | Identifiant unique |
| `name` | string | oui | Intitulé de la mission |
| `description` | string | oui | Description libre |
| `is_complete` | bool | oui | Statut d'achèvement |

---

### Item (objet)

```json
{
  "id": 3,
  "name": "potion de santé",
  "stat": 90,
  "effect": 2,
  "id_owner": 1,
  "type_owner": 2
}
```

| Champ | Type | Requis | Description |
|---|---|---|---|
| `id` | int | oui (lecture) | Identifiant unique |
| `name` | string | oui | Nom de l'objet |
| `stat` | int | oui | Valeur de l'effet (peut être négatif, ex. poison) |
| `effect` | int | oui | Type d'effet : `1` = AP, `2` = HP, `3` = DP |
| `id_owner` | int | oui | ID du propriétaire (`0` = libre) |
| `type_owner` | int | oui | Type du propriétaire (valeur `OBJETS`) ; `-1` = aucun |

Un item libre (`id_owner: 0`, `type_owner: -1`) est stocké dans `World::_items`. Dès qu'il est pris par une entité, il est déplacé (`std::move`) dans l'inventaire de cette entité et la `_tableDeCorrespondance` est mise à jour.

---

### Grade

```json
{
  "id": 1,
  "name": "Capitaine",
  "level": 5
}
```

| Champ | Type | Requis | Description |
|---|---|---|---|
| `id` | int | oui (lecture) | Identifiant unique |
| `name` | string | oui | Nom du grade |
| `level` | int | oui | Niveau d'accès / rang (>= 0) |

---

### Token

```json
{
  "id": 1,
  "user": "romain",
  "key": "je préfère le Faucon Millenium",
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

| Champ | Type | Description |
|---|---|---|
| `id` | int | Identifiant unique |
| `user` | string | Nom d'utilisateur |
| `key` | string | Clé secrète utilisée pour signer le JWT |
| `token` | string | JWT complet (header.payload.signature) |

---

## Règles métier

### Table de correspondance des items

La structure `_tableDeCorrespondance` (`map<OBJETS, map<int, int>>`) est le registre central de propriété des items :

```
_tableDeCorrespondance[type_owner][id_item] = id_owner
```

Exemples :
- `_tableDeCorrespondance[HEROS][3] = 1` → l'item 3 appartient au héros 1
- `_tableDeCorrespondance[NONE][1] = 0`  → l'item 1 est libre

Elle est mise à jour à chaque opération `takeItem` / `giveItem` / `removeItem` et persistée dans `bdd.json` via les champs `id_owner` et `type_owner` de chaque item.

---

### Combat (`attack`)

La formule de dommages est identique pour les quidams et les vaisseaux :

```
HP_défenseur_new = HP_défenseur - (AP_attaquant - DP_défenseur)
```

**Règles :**
- Un quidam (`HEROS` / `PNJ` / `EVIL`) ne peut attaquer qu'un autre quidam. Un vaisseau ne peut attaquer qu'un autre vaisseau. Toute tentative inter-famille retourne `ENTITY_OUT_RANGE`.
- Si `HP_défenseur_new <= 0`, le code retour est `ENTITY_IS_DEATH`. Le contrôleur déclenche alors `Rule::killEntities()` en cascade complète.
- Les attributs sont modifiés directement en mémoire via `setAttributs`, puis persistés par `saveJSON()`.

---

### Mort et suppression en cascade (`kill`)

La suppression est ordonnée pour respecter les dépendances :

```
1. Grades         (retrait des membres avant suppression)
2. Missions       (indépendantes, suppression directe)
3. Items          (libération du slot dans l'inventaire, mise à jour _tableDeCorrespondance)
4. Quidams        (nettoyage planètes / vaisseaux / grades via weak_ptr)
5. Vaisseaux      (suppression de l'équipage restant)
6. Planètes       (suppression des habitants restants)
```

**Effets de bord lors de la suppression d'une planète :**
- Tous les habitants dont `id_planet == id_planet` sont supprimés.
- Les quidams dont `id_planet_origin == id_planet` voient leur origine remise à `0`.

**Effets de bord lors de la suppression d'un vaisseau :**
- Tous les membres d'équipage sont supprimés.
- Les items dans l'inventaire du vaisseau sont remis en stock libre.

**Effets de bord lors de la suppression d'un quidam :**
- Ses items sont libérés vers `_items` avec `type_owner = NONE`.
- Il est retiré de sa planète, de son vaisseau et de son grade via `cleanHabitants()` / `cleanEquipage()` / `cleanMembres()` (les `weak_ptr` expirés sont purgés automatiquement).

---

### Échange d'items (`exchangeItem`)

Deux actions possibles :

**`pull` — prendre un item libre :**
1. Vérifier que l'item existe et est libre (`_tableDeCorrespondance[NONE]`).
2. Vérifier que l'entité existe et que son inventaire a de la place (< `maxItem` = 5).
3. Déplacer l'item de `_items` vers `Inventory::_inventory` via `addItem` (`std::move`).
4. Mettre à jour `item.setOwner(id, type)`.
5. Mettre à jour `_tableDeCorrespondance` : supprimer `[NONE][id_item]`, ajouter `[type][id_item] = id_owner`.

**`push` — rendre un item :**
1. Vérifier que l'item existe et appartient bien à l'entité déclarée.
2. Swap entre `_items[id_item]` et `Inventory[id_item]` via `std::swap`.
3. Remettre `item.setOwner(0, NONE)`.
4. Mettre à jour `_tableDeCorrespondance` : supprimer `[type][id_item]`, ajouter `[NONE][id_item] = 0`.

> Les opérations `pull` et `push` peuvent être mixées dans le même appel (tableau de plusieurs objets). En cas d'erreur sur l'un d'eux, le traitement s'arrête immédiatement et rien n'est persisté.

---

### Promotion (`promote`)

1. Vérifier que le quidam est de type `HEROS`, `PNJ` ou `EVIL` (les autres types retournent `MISSING_GRADE`).
2. Retirer le quidam de son grade actuel via `Grade::deleteMembre()`.
3. Ajouter le quidam au nouveau grade via `Grade::addMembre()`.
4. Mettre à jour `quidam.setIdGrade(id_grade)`.

---

### Ajout d'entités (`addEntities`)

Chaque objet du tableau est traité indépendamment. Attributs requis par type :

| Type | Attributs obligatoires |
|---|---|
| `PLANETE` | `name`, `description` |
| `SPACESHIP` | `name`, `description`, `ap`, `dp`, `hp` |
| `HEROS` / `PNJ` / `EVIL` | `name`, `ap`, `hp`, `dp`, `id_planet_origin` (> 0), `id_planet`, `id_ship`, `id_grade` — les IDs référencés doivent exister ou valoir `0` |
| `MISSION` | `name`, `description`, `is_complete` |
| `ITEM` | `name`, `stat`, `effect`, `id_owner`, `type_owner` — si `type_owner != NONE`, l'entité propriétaire doit exister et posséder un inventaire |
| `GRADE` | `name`, `level` |

En cas d'erreur sur l'une des entités du tableau, le traitement s'arrête immédiatement et aucune entité créée lors de cet appel n'est persistée.

---

## Base de données JSON

Le fichier `bdd.json` est l'unique source de persistance. Il est rechargé au démarrage et réécrit intégralement après chaque opération de mutation.

```json
{
  "startrek": {
    "0": [ /* planètes */ ],
    "1": [ /* vaisseaux */ ],
    "2": [ /* héros */ ],
    "3": [ /* PNJ */ ],
    "4": [ /* evils */ ],
    "5": [ /* missions */ ],
    "6": [ /* items (avec id_owner et type_owner) */ ],
    "7": [ /* grades */ ],
    "9": [ /* tokens */ ]
  }
}
```

Les clés correspondent aux valeurs numériques de l'enum `OBJETS`. La correspondance items ↔ propriétaires est reconstruite en mémoire au chargement via `_tableDeCorrespondance`.

---

## API REST

Toutes les routes nécessitent un header `Authorization: Bearer <token>` sauf `POST /v1/getToken`.

### Format de réponse standard

**Succès :**
```json
{ "statut": "Success", "code": 0, "return": { } }
```

**Erreur :**
```json
{ "statut": "Error", "code": 42, "description": "[ERROR] message lisible" }
```

---

### Obtenir un token

```
POST /v1/getToken
```

Corps :
```json
{ "security": "je préfère le Faucon Millenium", "user": "romain" }
```

Réponse :
```json
{ "statut": "Success", "code": 0, "return": { "token": "eyJ..." } }
```

Si un token existe déjà pour cet utilisateur, il est retourné tel quel sans en créer un nouveau.

---

### Lire des informations

```
GET /v1/getInfos/{entity_type}/{entity_id}
```

`entity_id` peut valoir `-1` pour tout le type. `entity_type` peut valoir `8` (`LIVING`) pour récupérer héros + PNJ + evils en une seule requête.

---

### Lire les habitants d'une planète

```
GET /v1/getHabitants/{id_planet}
```

---

### Lire l'équipage d'un vaisseau

```
GET /v1/getEquipage/{id_ship}
```

---

### Lire l'inventaire

```
GET /v1/getInventory/{entity_type}/{entity_id}
```

Disponible pour `HEROS` (2), `PNJ` (3), `EVIL` (4), `SPACESHIP` (1). Retourne `MISSING_INVENTORY` pour les autres.

---

### Lire la hiérarchie d'un grade

```
GET /v1/getHierarchy/{id_grade}/{entity_id}
```

---

### Ajouter des entités

```
PUT /v1/addEntities
```

Corps : tableau d'objets avec `entity_type` + attributs requis selon le type.

---

### Attaquer

```
POST /v1/attack
```

Corps :
```json
{
  "startrek": {
    "defenseur": { "type": 2, "id": 1 },
    "attaquant":  { "type": 4, "id": 5 }
  }
}
```

Si le défenseur meurt, `code` vaut `70` (`ENTITY_IS_DEATH`) et l'entité est supprimée.

---

### Supprimer une entité

```
DELETE /v1/kill
```

Corps :
```json
{ "startrek": { "entity_type": 2, "entity_id": 1 } }
```

---

### Échanger des objets

```
POST /v1/exchangeItem
```

Corps : tableau d'opérations avec `entity_type`, `entity_id`, `action` (`"pull"` ou `"push"`), `item` (tableau d'IDs).

---

### Promouvoir vers un grade

```
POST /v1/promote
```

Corps :
```json
[ { "entity_type": 2, "entity_id": 1, "id_grade": 1 } ]
```

---

## Authentification

Le serveur implémente une authentification par **JWT (HS256)**. La clé secrète est définie par la macro `MDP` dans `include/define.hh`.

**Génération du token (`Token::createJwt`) :**
1. Header `{"alg":"HS256","typ":"JWT"}` encodé en Base64Url.
2. Payload `{"iss":"admin","sub":"<user>","iat":<timestamp>}` encodé en Base64Url.
3. Signature HMAC-SHA256 de `header.payload` avec la clé, encodée en Base64Url.
4. Token final = `header.payload.signature`.

À chaque requête, le header `Authorization: Bearer <token>` est comparé aux tokens chargés en mémoire. Si aucun ne correspond, la réponse est `401 Unauthorized`.

> ⚠️ Le token est stocké en clair dans `bdd.json`. En production, préférer une base de données sécurisée et mettre en place une expiration des tokens.

---

## Codes d'erreur

| Code | Constante | Message |
|---|---|---|
| 0 | `OK` | Succès |
| 1 | `UNKWOWN_ERROR` | Erreur inconnue |
| 2 | `UNKNOWN_PLANET` | Planète non trouvée |
| 3 | `UNKNOWN_SPACESHIP` | Vaisseau non trouvé |
| 4 | `UNKNOWN_HEROS` | Héros non trouvé |
| 5 | `UNKNOWN_EVIL` | Evil non trouvé |
| 6 | `UNKNOWN_PNJ` | PNJ non trouvé |
| 7 | `UNKNOWN_MISSION` | Mission non trouvée |
| 8 | `UNKNOWN_ITEM` | Item non trouvé |
| 9 | `UNKNOWN_GRADE` | Grade non trouvé |
| 10 | `UNKNOWN_ENTITY` | Type d'entité inconnu |
| 11 | `UNKNOWN_COMMAND` | Commande inconnue |
| 17 | `UNKNOWN_DEFENSE_OR_ATTACK` | Attaquant ou défenseur inexistant |
| 19 | `UNKNOWN_ACTION` | Action inconnue (exchangeItem) |
| 29 | `MISSING_SECURITY_ATTRIBUT` | Champ `security` manquant |
| 30 | `INCORRECT_PASSWORD` | Mot de passe incorrect |
| 31 | `MISSING_STARTREK_ATTRIBUT` | Champ `startrek` manquant |
| 32 | `MISSING_ENTITY_TYPE_ATTRIBUT` | Champ `entity_type` manquant |
| 61 | `ITEM_OCCUPY` | Item déjà possédé |
| 62 | `MISSING_INVENTORY` | L'entité n'a pas d'inventaire |
| 63 | `MISSING_GRADE` | Ce type d'entité n'a pas de grade |
| 65 | `ENTITY_OUT_RANGE` | Entités incompatibles pour le combat |
| 66 | `UNAUTHORIZED` | Token invalide |
| 70 | `ENTITY_IS_DEATH` | Entité morte après combat |

La liste complète est définie dans l'enum `CODE_ERROR` dans `include/define.hh`.

---

## À faire (ToDoList)

- [ ] Gestion des attaques super efficaces
- [ ] Tests unitaires pour toutes les commandes (`kill`, `attack`, `exchangeItem`, `getInfos`, `escape`, `getHabitants`, `getEquipage`, `getInventory`, `getHierarchy`, `promote`)
- [ ] Finalisation de la gestion des tokens (expiration, révocation)
- [ ] Tests de la migration CJSON → Boost.JSON
