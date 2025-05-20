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
            //if (List::size(node) < 8) return (type_obj == HEROS ? NOT_ENOUGHT_ATTRIBUT_HEROS : (type_obj == PNJ ? NOT_ENOUGHT_ATTRIBUT_PNJ : NOT_ENOUGHT_ATTRIBUT_EVIL));
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return (type_obj == HEROS ? MISSING_ID_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_ID_ATTRIBUT_PNJ : MISSING_ID_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "name") == NULL) return (type_obj == HEROS ? MISSING_NAME_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_NAME_ATTRIBUT_PNJ : MISSING_NAME_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "ap") == NULL) return (type_obj == HEROS ? MISSING_AP_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_AP_ATTRIBUT_PNJ : MISSING_AP_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "hp") == NULL) return (type_obj == HEROS ? MISSING_HP_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_HP_ATTRIBUT_PNJ : MISSING_HP_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "dp") == NULL) return (type_obj == HEROS ? MISSING_DP_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_DP_ATTRIBUT_PNJ : MISSING_DP_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "id_planet") == NULL) return (type_obj == HEROS ? MISSING_ID_PLANET_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_ID_PLANET_ATTRIBUT_PNJ : MISSING_ID_PLANET_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "id_ship") == NULL) return (type_obj == HEROS ? MISSING_ID_SHIP_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_ID_SHIP_ATTRIBUT_PNJ : MISSING_ID_SHIP_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "id_planet_origin") == NULL) return (type_obj == HEROS ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_PNJ : MISSING_ID_PLANET_ORIGIN_ATTRIBUT_EVIL));
            if (cJSON_GetObjectItem(node, "id_grade") == NULL) return (type_obj == HEROS ? MISSING_ID_GRADE_ATTRIBUT_HEROS : (type_obj == PNJ ? MISSING_ID_GRADE_ATTRIBUT_PNJ : MISSING_ID_GRADE_ATTRIBUT_EVIL));
            break;
        case SPACESHIP:
            //if (List::size(node) < 6) return UNKNOWN_MISSION;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return MISSING_ID_ATTRIBUT_SPACESHIP;
            if (cJSON_GetObjectItem(node, "name") == NULL) return MISSING_NAME_ATTRIBUT_SPACESHIP;
            if (cJSON_GetObjectItem(node, "description") == NULL) return MISSING_DESC_ATTRIBUT_SPACESHIP;
            if (cJSON_GetObjectItem(node, "ap") == NULL) return MISSING_AP_ATTRIBUT_SPACESHIP;
            if (cJSON_GetObjectItem(node, "dp") == NULL) return MISSING_DP_ATTRIBUT_SPACESHIP;
            if (cJSON_GetObjectItem(node, "hp") == NULL) return MISSING_HP_ATTRIBUT_SPACESHIP;
            break;
        case MISSION:
            //if (List::size(node) < 3) return NOT_ENOUGHT_ATTRIBUT_MISSION;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return MISSING_ID_ATTRIBUT_MISSION;
            if (cJSON_GetObjectItem(node, "name") == NULL) return MISSING_NAME_ATTRIBUT_MISSION;
            if (cJSON_GetObjectItem(node, "description") == NULL) return MISSING_DESC_ATTRIBUT_MISSION;
            if (cJSON_GetObjectItem(node, "is_complete") == NULL) return MISSING_IS_COMPLETE_ATTRIBUT_MISSION;
            break;
        case PLANETE:
            //if (List::size(node) < 3) return 1;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return MISSING_ID_ATTRIBUT_PLANET;
            if (cJSON_GetObjectItem(node, "name") == NULL) return MISSING_NAME_ATTRIBUT_PLANET;
            if (cJSON_GetObjectItem(node, "description") == NULL) return MISSING_DESC_ATTRIBUT_PLANET;
            break;
        case ITEM:
            //if (List::size(node) < 6) return UNKNOWN_GRADE;
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return MISSING_ID_ATTRIBUT_ITEM;
            if (cJSON_GetObjectItem(node, "name") == NULL) return MISSING_NAME_ATTRIBUT_ITEM;
            if (cJSON_GetObjectItem(node, "stat") == NULL) return MISSING_STAT_ATTRIBUT_ITEM;
            if (cJSON_GetObjectItem(node, "effect") == NULL) return MISSING_EFFECT_ATTRIBUT_ITEM;
            if (cJSON_GetObjectItem(node, "id_owner") == NULL) return MISSING_ID_OWNER_ATTRIBUT_ITEM;
            if (cJSON_GetObjectItem(node, "type_owner") == NULL) return MISSING_TYPE_OWNER_ATTRIBUT_ITEM;
            break;
        case GRADE:
            if (required && cJSON_GetObjectItem(node, "id") == NULL) return MISSING_ID_ATTRIBUT_GRADE;
            if (cJSON_GetObjectItem(node, "name") == NULL) return MISSING_NAME_ATTRIBUT_GRADE;
            if (cJSON_GetObjectItem(node, "level") == NULL) return MISSING_LEVEL_ATTRIBUT_GRADE;
        default:
            break;
    }
    return 0;
}

int    List::isRequiredRootStructure(cJSON *root) {
    //if (List::size(root) < 3) return -1;
    if (cJSON_GetObjectItem(root, "security") == NULL) return MISSING_SECURITY_ATTRIBUT;
    if (strcmp(cJSON_GetObjectItem(root, "security")->valuestring, MDP) != 0) return INCORRECT_PASSWORD;
    if (cJSON_GetObjectItem(root, "command") == NULL) return MISSING_COMMAND_ATTRIBUT;
    if (cJSON_GetObjectItem(root, "startrek") == NULL) return MISSING_STARTREK_ATTRIBUT;
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
        case NOT_ENOUGHT_ATTRIBUT /*-1*/:
            str = "[ERROR] Il manque des attributs à la racine du JSON";
            break;
        case MISSING_SECURITY_ATTRIBUT:
            str = "[ERROR] Attribut security à la racine du JSON non renseigné";
            break;
        case MISSING_COMMAND_ATTRIBUT:
            str = "[ERROR] Attribut command à la racine du JSON non renseigné";
            break;
        case MISSING_STARTREK_ATTRIBUT:
            str = "[ERROR] Attribut startrek à la racine du JSON non renseigné";
            break;
        case JSON_SYNTAXE_ERROR:
            str = "[ERROR] Syntaxe du JSON incorrecte";
            break;
        case UNKNOWN_COMMAND:
            str = "[ERROR] Commande inconnue";
            break;
        case INCORRECT_PASSWORD:
            str = "[ERROR] Mot de passe incorrect";
            break;
        case NOT_ENOUGHT_ATTRIBUT_PLANET:
            str = "[ERROR] Il manque des attributs à l'obj planète";
            break;
        case MISSING_ID_ATTRIBUT_PLANET:
            str = "[ERROR] Attribut id pour l'obj planète non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_PLANET:
            str = "[ERROR] Attribut name pour l'obj planète non renseigné";
            break;
        case MISSING_DESC_ATTRIBUT_PLANET:
            str = "[ERROR] Attribut description pour l'obj planète non renseigné";
            break;
        case UNKNOWN_PLANET:
            str = "[ERROR] Planète non trouvée";
            break;
        case NOT_ENOUGHT_ATTRIBUT_SPACESHIP:
            str = "[ERROR] Il manque des attributs à l'obj spaceship";
            break;
        case MISSING_ID_ATTRIBUT_SPACESHIP:
            str = "[ERROR] Attribut id pour l'obj spaceship non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_SPACESHIP:
            str = "[ERROR] Attribut name pour l'obj spaceship non renseigné";
            break;
        case MISSING_DESC_ATTRIBUT_SPACESHIP:
            str = "[ERROR] Attribut description pour l'obj spaceship non renseigné";
            break;
        case MISSING_AP_ATTRIBUT_SPACESHIP:
            str = "[ERROR] Attribut ap pour l'obj spaceship non renseigné";
            break;
        case MISSING_DP_ATTRIBUT_SPACESHIP:
            str = "[ERROR] Attribut dp pour l'obj spaceship non renseigné";
            break;
        case MISSING_HP_ATTRIBUT_SPACESHIP:
            str = "[ERROR] Attribut hp pour l'obj spaceship non renseigné";
            break;
        case MAX_ITEM_OVERFLOW_SPACESHIP:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case UNKNOWN_SPACESHIP:
           str = "[ERROR] Spaceship non trouvé";
            break;
        case UNKNOWN_ITEM_SPACECHIP:
            str = "[ERROR] le Spaceship ne possède pas cet item";
            break;
        case NOT_ENOUGHT_ATTRIBUT_HEROS:
            str = "[ERROR] Il manque des attributs à l'obj heros";
            break;
        case MISSING_ID_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut id pour l'obj heros non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut name pour l'obj heros non renseigné";
            break;
        case MISSING_AP_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut ap pour l'obj heros non renseigné";
            break;
        case MISSING_HP_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut hp pour l'obj heros non renseigné";
            break;
        case MISSING_DP_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut dp pour l'obj heros non renseigné";
            break;
        case MISSING_ID_PLANET_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut id_planet pour l'obj heros non renseigné";
            break;
        case MISSING_ID_SHIP_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut id_ship pour l'obj heros non renseigné";
            break;
        case MISSING_ID_PLANET_ORIGIN_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut id_planet_origin pour l'obj heros non renseigné";
            break;
        case MISSING_ID_GRADE_ATTRIBUT_HEROS:
            str = "[ERROR] Attribut id_grade pour l'obj heros non renseigné";
            break;
        case MAX_ITEM_OVERFLOW_HEROS:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case UNKNOWN_HEROS:
            str = "[ERROR] Heros non trouvé";
            break;
        case UNKNOWN_ITEM_HEROS:
            str = "[ERROR] le Heros ne possède pas cet item";
            break;
        case NOT_ENOUGHT_ATTRIBUT_EVIL:
            str = "[ERROR] Il manque des attributs à l'obj evil";
            break;
        case MISSING_ID_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut id pour l'obj evil non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut name pour l'obj evil non renseigné";
            break;
        case MISSING_AP_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut ap pour l'obj evil non renseigné";
            break;
        case MISSING_HP_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut hp pour l'obj evil non renseigné";
            break;
        case MISSING_DP_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut dp pour l'obj evil non renseigné";
            break;
        case MISSING_ID_PLANET_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut id_planet pour l'obj evil non renseigné";
            break;
        case MISSING_ID_SHIP_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut id_ship pour l'obj evil non renseigné";
            break;
        case MISSING_ID_PLANET_ORIGIN_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut id_planet_origin pour l'obj evil non renseigné";
            break;
        case MISSING_ID_GRADE_ATTRIBUT_EVIL:
            str = "[ERROR] Attribut id_grade pour l'obj evil non renseigné";
            break;
        case MAX_ITEM_OVERFLOW_EVIL:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case UNKNOWN_EVIL:
            str = "[ERROR] Evil non trouvé";
            break;
        case UNKNOWN_ITEM_EVIL:
            str = "[ERROR] le Mechant ne possède pas cet item";
            break;
        case NOT_ENOUGHT_ATTRIBUT_MISSION:
            str = "[ERROR] Il manque des attributs à l'obj mission";
            break;
        case MISSING_ID_ATTRIBUT_MISSION:
            str = "[ERROR] Attribut id pour l'obj mission non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_MISSION:
            str = "[ERROR] Attribut name pour l'obj mission non renseigné";
            break;
        case MISSING_DESC_ATTRIBUT_MISSION:
            str = "[ERROR] Attribut description pour l'obj mission non renseigné";
            break;
        case MISSING_IS_COMPLETE_ATTRIBUT_MISSION:
            str = "[ERROR] Attribut is_complete pour l'obj mission non renseigné";
            break;
        case UNKNOWN_MISSION:
            str = "[ERROR] Mission non trouvé";
            break;
        case NOT_ENOUGHT_ATTRIBUT_PNJ:
            str = "[ERROR] Il manque des attributs à l'obj pnj";
            break;
        case MISSING_ID_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut id pour l'obj pnj non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut name pour l'obj pnj non renseigné";
            break;
        case MISSING_AP_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut ap pour l'obj pnj non renseigné";
            break;
        case MISSING_HP_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut hp pour l'obj pnj non renseigné";
            break;
        case MISSING_DP_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut dp pour l'obj pnj non renseigné";
            break;
        case MISSING_ID_PLANET_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut id_planet pour l'obj pnj non renseigné";
            break;
        case MISSING_ID_SHIP_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut id_ship pour l'obj pnj non renseigné";
            break;
        case MISSING_ID_PLANET_ORIGIN_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut id_planet_origin pour l'obj pnj non renseigné";
            break;
        case MISSING_ID_GRADE_ATTRIBUT_PNJ:
            str = "[ERROR] Attribut id_grade pour l'obj pnj non renseigné";
            break;
        case MAX_ITEM_OVERFLOW_PNJ:
            str = "[ERROR] Nombre max d'item dans l'inventaire ateint";
            break;
        case UNKNOWN_PNJ:
            str = "[ERROR] Pnj non trouvé";
            break;
        case UNKNOWN_ITEM_PNJ:
            str = "[ERROR] le Pnj ne possède pas cet item";
            break;
        case NOT_ENOUGHT_ATTRIBUT_ITEM:
            str = "[ERROR] Il manque des attributs à l'obj item";
            break;
        case MISSING_ID_ATTRIBUT_ITEM:
            str = "[ERROR] Attribut id pour l'obj item non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_ITEM:
            str = "[ERROR] Attribut name pour l'obj item non renseigné";
            break;
        case MISSING_STAT_ATTRIBUT_ITEM:
            str = "[ERROR] Attribut stat pour l'obj item non renseigné";
            break;
        case MISSING_EFFECT_ATTRIBUT_ITEM:
            str = "[ERROR] Attribut effect pour l'obj item non renseigné";
            break;
        case MISSING_ID_OWNER_ATTRIBUT_ITEM:
            str = "[ERROR] Attribut id_owner pour l'obj item non renseigné";
            break;
        case MISSING_TYPE_OWNER_ATTRIBUT_ITEM:
            str = "[ERROR] Attribut type_owner pour l'obj item non renseigné";
            break;
        case UNKNOWN_ITEM:
            str = "[ERROR] Item non trouvé";
            break;
        case MISSING_ID_ATTRIBUT_GRADE:
            str = "[ERROR] Attribut id pour l'obj grade non renseigné";
            break;
        case MISSING_NAME_ATTRIBUT_GRADE:
            str = "[ERROR] Attribut name pour l'obj grade non renseigné";
            break;
        case MISSING_LEVEL_ATTRIBUT_GRADE:
            str = "[ERROR] Attribut level pour l'obj grade non renseigné";
            break;
        case UNKNOWN_GRADE:
            str = "[ERROR] Grade non trouvé";
            break;
        case MISSING_ENTITY_TYPE_ATTRIBUT:
            str = "[ERROR] Attribut entity_type non renseigné";
            break;
        case MISSING_DEFENSE_ATTRIBUT:
            str = "[ERROR] Attribut defenseur non renseigné";
            break;
        case MISSING_ATTACK_ATTRIBUT:
            str = "[ERROR] Attribut attaquant non renseigné";
            break;
        case MISSING_ENTITY_ID_ATTRIBUT:
            str = "[ERROR] Attribut entity_id non renseigné";
            break;
        case MISSING_ACTION_ATTRIBUT:
            str = "[ERROR] Attribut action non renseigné";
            break;
        case MISSING_ITEMS_ATTRIBUT:
            str = "[ERROR] Attribut items non renseigné";
            break;
        case MISSING_DEFENSE_TYPE_ATTRIBUT:
            str = "[ERROR] Attribut type du defenseur non renseigné";
            break;
        case MISSING_DEFENSE_ID_ATTRIBUT:
            str = "[ERROR] Attribut id du defenseur non renseigné";
            break;
        case MISSING_ATTACK_TYPE_ATTRIBUT:
            str = "[ERROR] Attribut type de l'attaquant non renseigné";
            break;
        case MISSING_ATTACK_ID_ATTRIBUT:
            str = "[ERROR] Attribut id de l'attaquant non renseigné";
            break;
        case UNKNOWN_DEFENSE_OR_ATTACK:
            str = "[ERROR] L'attaquant et/ou le defenseur n'existe pas";
            break;
        case UNKNOWN_ID_GRADE:
            str = "[ERROR] Attribut id_grade n'existe pas";
            break;
        case ENTITY_OUT_RANGE:
            str = "[ERROR] Les Entité ne peuvent pas s'attaquer directement";
            break;
        case UNKNOWN_ENTITY:
            str = "[ERROR] type d'entité inconnue";
            break;
        case UNKNOWN_ACTION:
            str = "[ERROR] type d'action inconnue";
            break;
        case ITEM_OCCUPY:
            str = "[ERROR] L'objet n'est pas disponible";
            break;
        case MISSING_INVENTORY:
            str = "[ERROR] L'objet ne possède pas d'inventaire";
            break;
        case MISSING_GRADE:
            str = "[ERROR] Ce type d'entité ne possède pas de grade";
            break;
        case UNKNOWN_ATTACK_ACTION:
            str = "[ERROR] Ce type d'entité ne peux pas attaquer";
            break;
        case UNAUTHORIZED:
            str = "[ERROR] Bad TOKEN";
            break;
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
    if (cJSON_GetObjectItem(startrek, "defenseur") == NULL) return MISSING_DEFENSE_ATTRIBUT;
    if (cJSON_GetObjectItem(startrek, "attaquant") == NULL) return MISSING_ATTACK_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "type") == NULL) return MISSING_DEFENSE_TYPE_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "id") == NULL) return MISSING_DEFENSE_ID_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "type") == NULL) return MISSING_ATTACK_TYPE_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "id") == NULL) return MISSING_ATTACK_ID_ATTRIBUT;

    return 0;
}

int List::isCorrectToExhangeItemPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");

    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto item = cJSON_GetArrayItem(startrek, i);
        if (cJSON_GetObjectItem(item, "entity_type") == NULL) return MISSING_ENTITY_TYPE_ATTRIBUT;
        if (cJSON_GetObjectItem(item, "entity_id") == NULL) return MISSING_ENTITY_ID_ATTRIBUT;
        if (cJSON_GetObjectItem(item, "action") == NULL) return MISSING_ACTION_ATTRIBUT;
        if (cJSON_GetObjectItem(item, "items") == NULL) return MISSING_ITEMS_ATTRIBUT;
    }
    return 0;
}

int List::isCorrectToGetInfosPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "entity_type") == NULL) return MISSING_ENTITY_TYPE_ATTRIBUT;
    // if (cJSON_GetObjectItem(startrek, "entity_id") == NULL) return MISSING_LEVEL_ATTRIBUT_GRADE;
    return 0;
}

int List::isCorrectToKillPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "entity_type") == NULL) return MISSING_ENTITY_TYPE_ATTRIBUT;
    if (cJSON_GetObjectItem(startrek, "entity_id") == NULL) return MISSING_ENTITY_ID_ATTRIBUT;
    return 0;
}

int List::isCorrectToGetAddEntitiesPrototype(cJSON *root) {
   auto startrek = cJSON_GetObjectItem(root, "startrek");
   int code = 0;
   for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto item = cJSON_GetArrayItem(startrek, i);
        if (cJSON_GetObjectItem(item, "entity_type") == NULL) return MISSING_ENTITY_TYPE_ATTRIBUT;
        if ((code = isCorectToObjPrototype(item, (OBJETS)cJSON_GetObjectItem(item, "entity_type")->valueint, false)) != 0) return code;
    }
    return 0;
}

int List::isCorrectToEscapePrototype(cJSON *root) {
   auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "defenseur") == NULL) return MISSING_DEFENSE_ATTRIBUT;
    if (cJSON_GetObjectItem(startrek, "attaquant") == NULL) return MISSING_ATTACK_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "type") == NULL) return MISSING_DEFENSE_TYPE_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "defenseur"), "id") == NULL) return MISSING_DEFENSE_ID_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "type") == NULL) return MISSING_ATTACK_TYPE_ATTRIBUT;
    if (cJSON_GetObjectItem(cJSON_GetObjectItem(startrek, "attaquant"), "id") == NULL) return MISSING_ATTACK_ID_ATTRIBUT;
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
    if (cJSON_GetObjectItem(startrek, "id_planet") == NULL) return MISSING_ID_ATTRIBUT_PLANET;
    return 0;
}
int     List::isCorrectToGetEquipagePrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "id_ship") == NULL) return MISSING_ID_ATTRIBUT_SPACESHIP;
    return 0;
}
int     List::isCorrectToGetInventoryPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "entity_type") == NULL) return MISSING_ENTITY_TYPE_ATTRIBUT;
    if (cJSON_GetObjectItem(startrek, "entity_id") == NULL) return MISSING_ENTITY_ID_ATTRIBUT;
    return 0;
}

int     List::isCorrectToGetHierarchyPrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    if (cJSON_GetObjectItem(startrek, "id_grade") == NULL) return UNKNOWN_ID_GRADE;
    return 0;
}

int     List::isCorrectToPromotePrototype(cJSON *root) {
    auto startrek = cJSON_GetObjectItem(root, "startrek");
    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto item = cJSON_GetArrayItem(startrek, i);
        if (cJSON_GetObjectItem(item, "entity_type") == NULL) return MISSING_ENTITY_TYPE_ATTRIBUT;
        if (cJSON_GetObjectItem(item, "entity_id") == NULL) return MISSING_ENTITY_ID_ATTRIBUT;
        if (cJSON_GetObjectItem(item, "id_grade") == NULL) return UNKNOWN_ID_GRADE;
    }
    return 0;
}

vector<string> List::split(string str, string delimiter)
{
    vector<string> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
            // Find the index of occurrence
            size_t idx = str.find(delimiter, start);
            if (idx == string::npos)
            {
                break;
            }

            // If found add the substring till that
            // occurrence in the vector
            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }

    return v;
}