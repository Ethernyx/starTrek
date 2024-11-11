/**
 * File: List.cpp
 * Project: lib_func
 * File Created: Friday', 28th July 2023 2:33:51 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Friday', 28th July 2023 2:33:51 pm
 * Modified by: LALIN Romain
 * -----
*/

#include    "List.hh"

size_t  List::size(cJSON *node) {
    size_t cpt = 1;

    if (node->prev != NULL) node = List::firstElem(node);
    while (node != NULL) {
        cpt++;
        node = node->next;
    }
    return cpt;
}

cJSON   *List::firstElem(cJSON *node) {
    while (node->prev != NULL) node = node->prev;
    return node;
}

cJSON *List::defaultNode() {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root,"statut", "Success");
    cJSON_AddNumberToObject(root,"code", 0);
    cJSON_AddItemToObject(root, "return", cJSON_CreateObject());
    return root;
}


int    List::isCorectToObjPrototype(cJSON *node, OBJETS type_obj, bool required) {
    switch (type_obj)
    {
        case HEROS:
        case PNJ:
        case EVIL:
            //if (List::size(node) < 8) return HEROS * 100 + 1;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return type_obj * 100 + 2;
            if (cJSON_GetObjectItem(node, "name") == NULL) return type_obj * 100 + 3;
            if (cJSON_GetObjectItem(node, "ap") == NULL) return type_obj * 100 + 4;
            if (cJSON_GetObjectItem(node, "hp") == NULL) return type_obj * 100 + 5;
            if (cJSON_GetObjectItem(node, "dp") == NULL) return type_obj * 100 + 6;
            if (cJSON_GetObjectItem(node, "id_planet") == NULL) return type_obj * 100 + 7;
            if (cJSON_GetObjectItem(node, "id_ship") == NULL) return type_obj * 100 + 8;
            if (cJSON_GetObjectItem(node, "id_planet_origin") == NULL) return type_obj * 100 + 9;
            if (cJSON_GetObjectItem(node, "id_grade") == NULL) return type_obj * 100 + 10;
            break;
        case SPACESHIP:
            //if (List::size(node) < 6) return SPACESHIP * 100 + 1;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return SPACESHIP * 100 + 2;
            if (cJSON_GetObjectItem(node, "name") == NULL) return SPACESHIP * 100 + 3;
            if (cJSON_GetObjectItem(node, "description") == NULL) return SPACESHIP * 100 + 4;
            if (cJSON_GetObjectItem(node, "ap") == NULL) return SPACESHIP * 100 + 5;
            if (cJSON_GetObjectItem(node, "dp") == NULL) return SPACESHIP * 100 + 6;
            if (cJSON_GetObjectItem(node, "hp") == NULL) return SPACESHIP * 100 + 7;
            break;
        case MISSION:
            //if (List::size(node) < 3) return MISSION * 100 + 1;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return MISSION * 100 + 2;
            if (cJSON_GetObjectItem(node, "name") == NULL) return MISSION * 100 + 3;
            if (cJSON_GetObjectItem(node, "description") == NULL) return MISSION * 100 + 4;
            if (cJSON_GetObjectItem(node, "is_complete") == NULL) return MISSION * 100 + 5;
            break;
        case PLANETE:
            //if (List::size(node) < 3) return 1;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return PLANETE * 100 + 2;
            if (cJSON_GetObjectItem(node, "name") == NULL) return PLANETE * 100 + 3;
            if (cJSON_GetObjectItem(node, "description") == NULL) return PLANETE * 100 + 4;
            break;
        case ITEM:
            //if (List::size(node) < 6) return ITEM * 100 + 1;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return ITEM * 100 + 2;
            if (cJSON_GetObjectItem(node, "name") == NULL) return ITEM * 100 + 3;
            if (cJSON_GetObjectItem(node, "stat") == NULL) return ITEM * 100 + 4;
            if (cJSON_GetObjectItem(node, "effect") == NULL) return ITEM * 100 + 5;
            if (cJSON_GetObjectItem(node, "id_owner") == NULL) return ITEM * 100 + 6;
            if (cJSON_GetObjectItem(node, "type_owner") == NULL) return ITEM * 100 + 7;
            break;
        case GRADE:
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return GRADE * 100 + 2;
            if (cJSON_GetObjectItem(node, "name") == NULL) return GRADE * 100 + 3;
            if (cJSON_GetObjectItem(node, "level") == NULL) return GRADE * 100 + 4;
        default:
            break;
    }
    return 0;
}

int    List::isRequiredRootStructure(cJSON *root) {
    //if (List::size(root) < 3) return -1;
    if (cJSON_GetObjectItem(root, "security") == NULL) return -2;
    if (strcmp(cJSON_GetObjectItem(root, "security")->valuestring, MDP) != 0) return -7;
    if (cJSON_GetObjectItem(root, "command") == NULL) return -3;
    if (cJSON_GetObjectItem(root, "startrek") == NULL) return -4;
    return 0;
}

int    List::isCorectToInitPrototype(cJSON *root) {
    int code = 0;
    if ((code = List::isRequiredRootStructure(root)) != 0) return code;
    auto items = cJSON_GetObjectItem(root, "startrek")->child;

    while (items != NULL) {
        for (int i = 0; i < cJSON_GetArraySize(items); i++) if ((code = List::isCorectToObjPrototype(cJSON_GetArrayItem(items, i), (OBJETS)atoi(items->string), true)) != 0) return code;
        items = items->next;
    }
    return code;
}

string  List::codeError(int code) {
    string str = "";
    switch (code)
    {
        case -1:
            str = "[ERROR] Il manque des attributs à la racine du JSON";
            break;
        case -2:
            str = "[ERROR] Attribut security à la racine du JSON non renseigné";
            break;
        case -3:
            str = "[ERROR] Attribut command à la racine du JSON non renseigné";
            break;
        case -4:
            str = "[ERROR] Attribut startrek à la racine du JSON non renseigné";
            break;
        case -5:
            str = "[ERROR] Syntaxe du JSON incorrecte";
            break;
        case -6:
            str = "[ERROR] Commande inconnue";
            break;
        case -7:
            str = "[ERROR] Mot de passe incorrect";
            break;
        case PLANETE * 100 + 1:
            str = "[ERROR] Il manque des attributs à l'obj planète";
            break;
        case PLANETE * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj planète non renseigné";
            break;
        case PLANETE * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj planète non renseigné";
            break;
        case PLANETE * 100 + 4:
            str = "[ERROR] Attribut description pour l'obj planète non renseigné";
            break;
        case PLANETE * 100 + 5:
            str = "[ERROR] Planète non trouvée";
            break;
        case SPACESHIP * 100 + 1:
            str = "[ERROR] Il manque des attributs à l'obj spaceship";
            break;
        case SPACESHIP * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj spaceship non renseigné";
            break;
        case SPACESHIP * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj spaceship non renseigné";
            break;
        case SPACESHIP * 100 + 4:
            str = "[ERROR] Attribut description pour l'obj spaceship non renseigné";
            break;
        case SPACESHIP * 100 + 5:
            str = "[ERROR] Attribut ap pour l'obj spaceship non renseigné";
            break;
        case SPACESHIP * 100 + 6:
            str = "[ERROR] Attribut dp pour l'obj spaceship non renseigné";
            break;
        case SPACESHIP * 100 + 7:
            str = "[ERROR] Attribut hp pour l'obj spaceship non renseigné";
            break;
        case SPACESHIP * 100 + 8:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case SPACESHIP * 100 + 9:
           str = "[ERROR] Spaceship non trouvé";
            break;
        case SPACESHIP * 100 + 10:
            str = "[ERROR] le Spaceship ne possède pas cet item";
            break;
        case HEROS * 100 + 1:
            str = "[ERROR] Il manque des attributs à l'obj heros";
            break;
        case HEROS * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 4:
            str = "[ERROR] Attribut ap pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 5:
            str = "[ERROR] Attribut hp pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 6:
            str = "[ERROR] Attribut dp pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 7:
            str = "[ERROR] Attribut id_planet pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 8:
            str = "[ERROR] Attribut id_ship pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 9:
            str = "[ERROR] Attribut id_planet_origin pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 10:
            str = "[ERROR] Attribut id_grade pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 11:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case HEROS * 100 + 40:
            str = "[ERROR] Attribut id_planet_origin pour l'obj heros non renseigné";
            break;
        case HEROS * 100 + 12:
            str = "[ERROR] Heros non trouvé";
            break;
        case HEROS * 100 + 13:
            str = "[ERROR] le Heros ne possède pas cet item";
            break;
        case EVIL * 100 + 1:
            str = "[ERROR] Il manque des attributs à l'obj evil";
            break;
        case EVIL * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 4:
            str = "[ERROR] Attribut ap pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 5:
            str = "[ERROR] Attribut hp pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 6:
            str = "[ERROR] Attribut dp pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 7:
            str = "[ERROR] Attribut id_planet pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 8:
            str = "[ERROR] Attribut id_ship pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 9:
            str = "[ERROR] Attribut id_planet_origin pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 10:
            str = "[ERROR] Attribut id_grade pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 11:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case EVIL * 100 + 40:
            str = "[ERROR] Attribut id_planet_origin pour l'obj evil non renseigné";
            break;
        case EVIL * 100 + 12:
            str = "[ERROR] Evil non trouvé";
            break;
        case EVIL * 100 + 13:
            str = "[ERROR] le Mechant ne possède pas cet item";
            break;
        case MISSION * 100 + 1:
            str = "[ERROR] Il manque des attributs à l'obj mission";
            break;
        case MISSION * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj mission non renseigné";
            break;
        case MISSION * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj mission non renseigné";
            break;
        case MISSION * 100 + 4:
            str = "[ERROR] Attribut description pour l'obj mission non renseigné";
            break;
        case MISSION * 100 + 5:
            str = "[ERROR] Attribut is_complete pour l'obj mission non renseigné";
            break;
        case MISSION * 100 + 6:
            str = "[ERROR] Mission non trouvé";
            break;
        case PNJ * 100 + 1:
            str = "[ERROR] Il manque des attributs à l'obj pnj";
            break;
        case PNJ * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 4:
            str = "[ERROR] Attribut ap pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 5:
            str = "[ERROR] Attribut hp pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 6:
            str = "[ERROR] Attribut dp pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 7:
            str = "[ERROR] Attribut id_planet pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 8:
            str = "[ERROR] Attribut id_ship pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 9:
            str = "[ERROR] Attribut id_planet_origin pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 10:
            str = "[ERROR] Attribut id_grade pour l'obj pnj non renseigné";
            break;
        case PNJ * 100 + 11:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case PNJ * 100 + 12:
            str = "[ERROR] Pnj non trouvé";
            break;
        case PNJ * 100 + 13:
            str = "[ERROR] le Pnj ne possède pas cet item";
            break;
        case ITEM * 100 + 1:
            str = "[ERROR] Il manque des attributs à l'obj item";
            break;
        case ITEM * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj item non renseigné";
            break;
        case ITEM * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj item non renseigné";
            break;
        case ITEM * 100 + 4:
            str = "[ERROR] Attribut stat pour l'obj item non renseigné";
            break;
        case ITEM * 100 + 5:
            str = "[ERROR] Attribut effect pour l'obj item non renseigné";
            break;
        case ITEM * 100 + 6:
            str = "[ERROR] Attribut id_owner pour l'obj item non renseigné";
            break;
        case ITEM * 100 + 7:
            str = "[ERROR] Attribut type_owner pour l'obj item non renseigné";
            break;
        case ITEM * 100 + 8:
            str = "[ERROR] Item non trouvé";
            break;
        case GRADE * 100 + 2:
            str = "[ERROR] Attribut id pour l'obj grade non renseigné";
            break;
        case GRADE * 100 + 3:
            str = "[ERROR] Attribut name pour l'obj grade non renseigné";
            break;
        case GRADE * 100 + 4:
            str = "[ERROR] Attribut level pour l'obj grade non renseigné";
            break;
        case GRADE * 100 + 5:
            str = "[ERROR] Grade non trouvé";
            break;
        case NONE * 100 + 1:
            str = "[ERROR] Attribut entity_type non renseigné";
            break;
        case NONE * 100 + 2:
            str = "[ERROR] Attribut defenseur non renseigné";
            break;
        case NONE * 100 + 3:
            str = "[ERROR] Attribut attaquant non renseigné";
            break;
        case NONE * 100 + 4:
            str = "[ERROR] Attribut entity_id non renseigné";
            break;
        case NONE * 100 + 5:
            str = "[ERROR] Attribut action non renseigné";
            break;
        case NONE * 100 + 6:
            str = "[ERROR] Attribut items non renseigné";
            break;
        case NONE * 100 + 7:
            str = "[ERROR] Attribut type du defenseur non renseigné";
            break;
        case NONE * 100 + 8:
            str = "[ERROR] Attribut id du defenseur non renseigné";
            break;
        case NONE * 100 + 9:
            str = "[ERROR] Attribut type de l'attaquant non renseigné";
            break;
        case NONE * 100 + 10:
            str = "[ERROR] Attribut id de l'attaquant non renseigné";
            break;
        case NONE * 100 + 11:
            str = "[ERROR] L'attaquant et/ou le defenseur n'existe pas";
            break;
        case NONE * 100 + 12:
            str = "[ERROR] Attribut id_grade n'existe pas";
            break;
        case NONE * 100 + 13:
            str = "[ERROR] Les Entité ne peuvent pas s'attaquer directement";
            break;
        case NONE * 100 + 14:
            str = "[ERROR] type d'entité inconnue";
            break;
        case NONE * 100 + 15:
            str = "[ERROR] type d'action inconnue";
            break;
        case NONE * 100 + 16:
            str = "[ERROR] L'objet n'est pas disponible";
            break;
        case NONE * 100 + 17:
            str = "[ERROR] L'objet ne possède pas d'inventaire";
            break;
        case NONE * 100 + 18:
            str = "[ERROR] Ce type d'entité ne possède pas de grade";
        default:
            str = "[ERROR] Erreur inconnue";
            break;
    }
    return str;
}

char  *List::returnJson(int code) {
    char *retour;
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "statut", code == 0 ? "Success" : "Error");
    cJSON_AddNumberToObject(json, "code", code);
    cJSON_AddStringToObject(json, "description", code == 0 ? "" : List::codeError(code).c_str());
    retour = cJSON_Print(json);
    cJSON_Delete(json);
    return retour;
}

int List::isCorrectToAttackPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
   // if (cJSON_GetObjectItem(startrek, "entity_type") == NULL) return GRADE * 100 + 1;
    if (cJSON_GetObjectItem(startrek, "defenseur") == NULL) return NONE * 100 + 2;
    if (cJSON_GetObjectItem(startrek, "attaquant") == NULL) return NONE * 100 + 3;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "type") == NULL) return NONE * 100 + 7;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "id") == NULL) return NONE * 100 + 8;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "type") == NULL) return NONE * 100 + 9;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "id") == NULL) return NONE * 100 + 10;

    return 0;
}

int List::isCorrectToExhangeItemPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");

    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto item = cJSON_GetArrayItem(startrek, i);
        if (cJSON_GetObjectItem(item, "entity_type") == NULL) return NONE * 100 + 1;
        if (cJSON_GetObjectItem(item, "entity_id") == NULL) return NONE * 100 + 4;
        if (cJSON_GetObjectItem(item, "action") == NULL) return NONE * 100 + 5;
        if (cJSON_GetObjectItem(item, "items") == NULL) return NONE * 100 + 6;
    }
    return 0;
}

int List::isCorrectToGetInfosPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "entity_type") == NULL) return NONE * 100 + 1;
    // if (cJSON_GetObjectItem(startrek, "entity_id") == NULL) return GRADE * 100 + 4;
    return 0;
}

int List::isCorrectToKillPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "entity_type") == NULL) return NONE * 100 + 1;
    if (cJSON_GetObjectItem(startrek, "entity_id") == NULL) return NONE * 100 + 4;
    return 0;
}

int List::isCorrectToGetAddEntitiesPrototype(cJSON *root) {
   auto startrek = cJSON_GetObjectItem(root, "startrek");
   int code = 0;
   for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto item = cJSON_GetArrayItem(startrek, i);
        if (cJSON_GetObjectItem(item, "entity_type") == NULL) return NONE * 100 + 1;
        if ((code = isCorectToObjPrototype(item, (OBJETS)cJSON_GetObjectItem(item, "entity_type")->valueint, false)) != 0) return code;
    }
    return 0;
}

int List::isCorrectToEscapePrototype(cJSON *root) {
   auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "defenseur") == NULL) return NONE * 100 + 2;
    if (cJSON_GetObjectItem(startrek, "attaquant") == NULL) return NONE * 100 + 3;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "type") == NULL) return NONE * 100 + 7;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "id") == NULL) return NONE * 100 + 8;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "type") == NULL) return NONE * 100 + 9;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "id") == NULL) return NONE * 100 + 10;
    return 0;
}

bool    List::checkJson(string json) {
    int cpt = 0;
    for (size_t i = 0; i < json.size(); i++) {
        if (json.at(i) == '{') cpt++;
        if (json.at(i) == '}') cpt--;
    }
    return (cpt == 0 ? true : false);
}

int     List::isCorrectToGetHabitantsPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "id_planet") == NULL) return PLANETE * 100 + 2;
    return 0;
}
int     List::isCorrectToGetEquipagePrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "id_ship") == NULL) return SPACESHIP * 100 + 2;
    return 0;
}
int     List::isCorrectToGetInventoryPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "entity_type") == NULL) return NONE * 100 + 1;
    if (cJSON_GetObjectItem(startrek, "entity_id") == NULL) return NONE * 100 + 4;
    return 0;
}

int     List::isCorrectToGetHierarchyPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "id_grade") == NULL) return NONE * 100 + 12;
    return 0;
}

int     List::isCorrectToPromotePrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto item = cJSON_GetArrayItem(startrek, i);
        if (cJSON_GetObjectItem(item, "entity_type") == NULL) return NONE * 100 + 1;
        if (cJSON_GetObjectItem(item, "entity_id") == NULL) return NONE * 100 + 4;
        if (cJSON_GetObjectItem(item, "id_grade") == NULL) return NONE * 100 + 12;
    }
    return 0;
}