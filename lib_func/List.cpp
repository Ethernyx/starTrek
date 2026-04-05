/*
 * File: List.cpp                                                              *
 * Project: lib_func                                                           *
 * Created Date: Tu May 2025, 11:14:09 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 2:39:08 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "List.hh"

// ---------------------------------------------------------------------------
// Helpers internes
// ---------------------------------------------------------------------------

static bool hasKey(boost::json::object const &obj, string const &key)
{
    return obj.contains(key);
}

// ---------------------------------------------------------------------------
// Validation des prototypes objets
// ---------------------------------------------------------------------------

int List::isCorectToObjPrototype(boost::json::object const &node, OBJETS type_obj, bool required)
{
    switch (type_obj)
    {
        case HEROS:
        case PNJ:
        case EVIL:
            if (required && !hasKey(node, "id"))
                return (type_obj == HEROS ? MISSING_ID_ATTRIBUT_HEROS   :
                        type_obj == PNJ  ? MISSING_ID_ATTRIBUT_PNJ      : MISSING_ID_ATTRIBUT_EVIL);
            if (!hasKey(node, "name"))
                return (type_obj == HEROS ? MISSING_NAME_ATTRIBUT_HEROS  :
                        type_obj == PNJ  ? MISSING_NAME_ATTRIBUT_PNJ     : MISSING_NAME_ATTRIBUT_EVIL);
            if (!hasKey(node, "ap"))
                return (type_obj == HEROS ? MISSING_AP_ATTRIBUT_HEROS    :
                        type_obj == PNJ  ? MISSING_AP_ATTRIBUT_PNJ       : MISSING_AP_ATTRIBUT_EVIL);
            if (!hasKey(node, "hp"))
                return (type_obj == HEROS ? MISSING_HP_ATTRIBUT_HEROS    :
                        type_obj == PNJ  ? MISSING_HP_ATTRIBUT_PNJ       : MISSING_HP_ATTRIBUT_EVIL);
            if (!hasKey(node, "dp"))
                return (type_obj == HEROS ? MISSING_DP_ATTRIBUT_HEROS    :
                        type_obj == PNJ  ? MISSING_DP_ATTRIBUT_PNJ       : MISSING_DP_ATTRIBUT_EVIL);
            if (!hasKey(node, "id_planet"))
                return (type_obj == HEROS ? MISSING_ID_PLANET_ATTRIBUT_HEROS :
                        type_obj == PNJ  ? MISSING_ID_PLANET_ATTRIBUT_PNJ    : MISSING_ID_PLANET_ATTRIBUT_EVIL);
            if (!hasKey(node, "id_ship"))
                return (type_obj == HEROS ? MISSING_ID_SHIP_ATTRIBUT_HEROS   :
                        type_obj == PNJ  ? MISSING_ID_SHIP_ATTRIBUT_PNJ      : MISSING_ID_SHIP_ATTRIBUT_EVIL);
            if (!hasKey(node, "id_planet_origin"))
                return (type_obj == HEROS ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_HEROS :
                        type_obj == PNJ  ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_PNJ    : MISSING_ID_PLANET_ORIGIN_ATTRIBUT_EVIL);
            if (!hasKey(node, "id_grade"))
                return (type_obj == HEROS ? MISSING_ID_GRADE_ATTRIBUT_HEROS  :
                        type_obj == PNJ  ? MISSING_ID_GRADE_ATTRIBUT_PNJ     : MISSING_ID_GRADE_ATTRIBUT_EVIL);
            break;

        case SPACESHIP:
            if (required && !hasKey(node, "id"))          return MISSING_ID_ATTRIBUT_SPACESHIP;
            if (!hasKey(node, "name"))                    return MISSING_NAME_ATTRIBUT_SPACESHIP;
            if (!hasKey(node, "description"))             return MISSING_DESC_ATTRIBUT_SPACESHIP;
            if (!hasKey(node, "ap"))                      return MISSING_AP_ATTRIBUT_SPACESHIP;
            if (!hasKey(node, "dp"))                      return MISSING_DP_ATTRIBUT_SPACESHIP;
            if (!hasKey(node, "hp"))                      return MISSING_HP_ATTRIBUT_SPACESHIP;
            break;

        case MISSION:
            if (required && !hasKey(node, "id"))          return MISSING_ID_ATTRIBUT_MISSION;
            if (!hasKey(node, "name"))                    return MISSING_NAME_ATTRIBUT_MISSION;
            if (!hasKey(node, "description"))             return MISSING_DESC_ATTRIBUT_MISSION;
            if (!hasKey(node, "is_complete"))             return MISSING_IS_COMPLETE_ATTRIBUT_MISSION;
            break;

        case PLANETE:
            if (required && !hasKey(node, "id"))          return MISSING_ID_ATTRIBUT_PLANET;
            if (!hasKey(node, "name"))                    return MISSING_NAME_ATTRIBUT_PLANET;
            if (!hasKey(node, "description"))             return MISSING_DESC_ATTRIBUT_PLANET;
            break;

        case ITEM:
            if (required && !hasKey(node, "id"))          return MISSING_ID_ATTRIBUT_ITEM;
            if (!hasKey(node, "name"))                    return MISSING_NAME_ATTRIBUT_ITEM;
            if (!hasKey(node, "stat"))                    return MISSING_STAT_ATTRIBUT_ITEM;
            if (!hasKey(node, "effect"))                  return MISSING_EFFECT_ATTRIBUT_ITEM;
            if (!hasKey(node, "id_owner"))                return MISSING_ID_OWNER_ATTRIBUT_ITEM;
            if (!hasKey(node, "type_owner"))              return MISSING_TYPE_OWNER_ATTRIBUT_ITEM;
            break;

        case GRADE:
            if (required && !hasKey(node, "id"))          return MISSING_ID_ATTRIBUT_GRADE;
            if (!hasKey(node, "name"))                    return MISSING_NAME_ATTRIBUT_GRADE;
            if (!hasKey(node, "level"))                   return MISSING_LEVEL_ATTRIBUT_GRADE;
            break;

        default:
            break;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Validation structure racine
// ---------------------------------------------------------------------------

int List::isRequiredRootStructure(boost::json::object const &root)
{
    if (!hasKey(root, "security"))                          return MISSING_SECURITY_ATTRIBUT;
    if (root.at("security").as_string() != MDP)            return INCORRECT_PASSWORD;
    if (!hasKey(root, "command"))                          return MISSING_COMMAND_ATTRIBUT;
    if (!hasKey(root, "startrek"))                         return MISSING_STARTREK_ATTRIBUT;
    return 0;
}

int List::isCorectToInitPrototype(boost::json::object const &root)
{
    int code = 0;
    if ((code = List::isRequiredRootStructure(root)) != 0) return code;

    auto const &startrek = root.at("startrek").as_object();
    for (auto const &entry : startrek)
    {
        auto const &arr = entry.value().as_array();
        for (auto const &item : arr)
        {
            code = List::isCorectToObjPrototype(
                item.as_object(),
                (OBJETS)stoi(string(entry.key())),
                true);
            if (code != 0) return code;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Validation des prototypes de commandes
// ---------------------------------------------------------------------------

int List::isCorrectToAttackPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_object();
    if (!hasKey(startrek, "defenseur"))                              return MISSING_DEFENSE_ATTRIBUT;
    if (!hasKey(startrek, "attaquant"))                              return MISSING_ATTACK_ATTRIBUT;
    auto const &def = startrek.at("defenseur").as_object();
    auto const &att = startrek.at("attaquant").as_object();
    if (!hasKey(def, "type"))                                        return MISSING_DEFENSE_TYPE_ATTRIBUT;
    if (!hasKey(def, "id"))                                          return MISSING_DEFENSE_ID_ATTRIBUT;
    if (!hasKey(att, "type"))                                        return MISSING_ATTACK_TYPE_ATTRIBUT;
    if (!hasKey(att, "id"))                                          return MISSING_ATTACK_ID_ATTRIBUT;
    return 0;
}

int List::isCorrectToExhangeItemPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_array();
    for (auto const &elem : startrek)
    {
        auto const &item = elem.as_object();
        if (!hasKey(item, "entity_type"))   return MISSING_ENTITY_TYPE_ATTRIBUT;
        if (!hasKey(item, "entity_id"))     return MISSING_ENTITY_ID_ATTRIBUT;
        if (!hasKey(item, "action"))        return MISSING_ACTION_ATTRIBUT;
        if (!hasKey(item, "items"))         return MISSING_ITEMS_ATTRIBUT;
    }
    return 0;
}

int List::isCorrectToGetInfosPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_object();
    if (!hasKey(startrek, "entity_type"))   return MISSING_ENTITY_TYPE_ATTRIBUT;
    return 0;
}

int List::isCorrectToKillPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_object();
    if (!hasKey(startrek, "entity_type"))   return MISSING_ENTITY_TYPE_ATTRIBUT;
    if (!hasKey(startrek, "entity_id"))     return MISSING_ENTITY_ID_ATTRIBUT;
    return 0;
}

int List::isCorrectToGetAddEntitiesPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_array();
    int code = 0;
    for (auto const &elem : startrek)
    {
        auto const &item = elem.as_object();
        if (!hasKey(item, "entity_type"))   return MISSING_ENTITY_TYPE_ATTRIBUT;
        code = isCorectToObjPrototype(item, (OBJETS)item.at("entity_type").as_int64(), false);
        if (code != 0) return code;
    }
    return 0;
}

int List::isCorrectToEscapePrototype(boost::json::object const &root)
{
    // même structure que attack
    return List::isCorrectToAttackPrototype(root);
}

int List::isCorrectToGetHabitantsPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_object();
    if (!hasKey(startrek, "id_planet"))     return MISSING_ID_ATTRIBUT_PLANET;
    return 0;
}

int List::isCorrectToGetEquipagePrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_object();
    if (!hasKey(startrek, "id_ship"))       return MISSING_ID_ATTRIBUT_SPACESHIP;
    return 0;
}

int List::isCorrectToGetInventoryPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_object();
    if (!hasKey(startrek, "entity_type"))   return MISSING_ENTITY_TYPE_ATTRIBUT;
    if (!hasKey(startrek, "entity_id"))     return MISSING_ENTITY_ID_ATTRIBUT;
    return 0;
}

int List::isCorrectToGetHierarchyPrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_object();
    if (!hasKey(startrek, "id_grade"))      return UNKNOWN_ID_GRADE;
    return 0;
}

int List::isCorrectToPromotePrototype(boost::json::object const &root)
{
    auto const &startrek = root.at("startrek").as_array();
    for (auto const &elem : startrek)
    {
        auto const &item = elem.as_object();
        if (!hasKey(item, "entity_type"))   return MISSING_ENTITY_TYPE_ATTRIBUT;
        if (!hasKey(item, "entity_id"))     return MISSING_ENTITY_ID_ATTRIBUT;
        if (!hasKey(item, "id_grade"))      return UNKNOWN_ID_GRADE;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Retour JSON et messages d'erreur
// ---------------------------------------------------------------------------

string List::returnJson(int code)
{
    boost::json::object json;
    json["statut"]      = (code == 0 ? "Success" : "Error");
    json["code"]        = code;
    json["description"] = (code == 0 ? "" : List::codeError(code));
    return boost::json::serialize(json);
}

string List::codeError(int code)
{
    switch (code)
    {
        case NOT_ENOUGHT_ATTRIBUT:                      return "[ERROR] Il manque des attributs à la racine du JSON";
        case MISSING_SECURITY_ATTRIBUT:                 return "[ERROR] Attribut security à la racine du JSON non renseigné";
        case MISSING_COMMAND_ATTRIBUT:                  return "[ERROR] Attribut command à la racine du JSON non renseigné";
        case MISSING_STARTREK_ATTRIBUT:                 return "[ERROR] Attribut startrek à la racine du JSON non renseigné";
        case JSON_SYNTAXE_ERROR:                        return "[ERROR] Syntaxe du JSON incorrecte";
        case UNKNOWN_COMMAND:                           return "[ERROR] Commande inconnue";
        case INCORRECT_PASSWORD:                        return "[ERROR] Mot de passe incorrect";

        case NOT_ENOUGHT_ATTRIBUT_PLANET:               return "[ERROR] Il manque des attributs à l'obj planète";
        case MISSING_ID_ATTRIBUT_PLANET:                return "[ERROR] Attribut id pour l'obj planète non renseigné";
        case MISSING_NAME_ATTRIBUT_PLANET:              return "[ERROR] Attribut name pour l'obj planète non renseigné";
        case MISSING_DESC_ATTRIBUT_PLANET:              return "[ERROR] Attribut description pour l'obj planète non renseigné";
        case UNKNOWN_PLANET:                            return "[ERROR] Planète non trouvée";

        case NOT_ENOUGHT_ATTRIBUT_SPACESHIP:            return "[ERROR] Il manque des attributs à l'obj spaceship";
        case MISSING_ID_ATTRIBUT_SPACESHIP:             return "[ERROR] Attribut id pour l'obj spaceship non renseigné";
        case MISSING_NAME_ATTRIBUT_SPACESHIP:           return "[ERROR] Attribut name pour l'obj spaceship non renseigné";
        case MISSING_DESC_ATTRIBUT_SPACESHIP:           return "[ERROR] Attribut description pour l'obj spaceship non renseigné";
        case MISSING_AP_ATTRIBUT_SPACESHIP:             return "[ERROR] Attribut ap pour l'obj spaceship non renseigné";
        case MISSING_DP_ATTRIBUT_SPACESHIP:             return "[ERROR] Attribut dp pour l'obj spaceship non renseigné";
        case MISSING_HP_ATTRIBUT_SPACESHIP:             return "[ERROR] Attribut hp pour l'obj spaceship non renseigné";
        case MAX_ITEM_OVERFLOW_SPACESHIP:               return "[ERROR] Nombre max d'item dans l'inventaire atteint";
        case UNKNOWN_SPACESHIP:                         return "[ERROR] Spaceship non trouvé";
        case UNKNOWN_ITEM_SPACECHIP:                    return "[ERROR] le Spaceship ne possède pas cet item";

        case NOT_ENOUGHT_ATTRIBUT_HEROS:                return "[ERROR] Il manque des attributs à l'obj heros";
        case MISSING_ID_ATTRIBUT_HEROS:                 return "[ERROR] Attribut id pour l'obj heros non renseigné";
        case MISSING_NAME_ATTRIBUT_HEROS:               return "[ERROR] Attribut name pour l'obj heros non renseigné";
        case MISSING_AP_ATTRIBUT_HEROS:                 return "[ERROR] Attribut ap pour l'obj heros non renseigné";
        case MISSING_HP_ATTRIBUT_HEROS:                 return "[ERROR] Attribut hp pour l'obj heros non renseigné";
        case MISSING_DP_ATTRIBUT_HEROS:                 return "[ERROR] Attribut dp pour l'obj heros non renseigné";
        case MISSING_ID_PLANET_ATTRIBUT_HEROS:          return "[ERROR] Attribut id_planet pour l'obj heros non renseigné";
        case MISSING_ID_SHIP_ATTRIBUT_HEROS:            return "[ERROR] Attribut id_ship pour l'obj heros non renseigné";
        case MISSING_ID_PLANET_ORIGIN_ATTRIBUT_HEROS:   return "[ERROR] Attribut id_planet_origin pour l'obj heros non renseigné";
        case MISSING_ID_GRADE_ATTRIBUT_HEROS:           return "[ERROR] Attribut id_grade pour l'obj heros non renseigné";
        case MAX_ITEM_OVERFLOW_HEROS:                   return "[ERROR] Nombre max d'item dans l'inventaire atteint";
        case UNKNOWN_HEROS:                             return "[ERROR] Heros non trouvé";
        case UNKNOWN_ITEM_HEROS:                        return "[ERROR] le Heros ne possède pas cet item";

        case NOT_ENOUGHT_ATTRIBUT_EVIL:                 return "[ERROR] Il manque des attributs à l'obj evil";
        case MISSING_ID_ATTRIBUT_EVIL:                  return "[ERROR] Attribut id pour l'obj evil non renseigné";
        case MISSING_NAME_ATTRIBUT_EVIL:                return "[ERROR] Attribut name pour l'obj evil non renseigné";
        case MISSING_AP_ATTRIBUT_EVIL:                  return "[ERROR] Attribut ap pour l'obj evil non renseigné";
        case MISSING_HP_ATTRIBUT_EVIL:                  return "[ERROR] Attribut hp pour l'obj evil non renseigné";
        case MISSING_DP_ATTRIBUT_EVIL:                  return "[ERROR] Attribut dp pour l'obj evil non renseigné";
        case MISSING_ID_PLANET_ATTRIBUT_EVIL:           return "[ERROR] Attribut id_planet pour l'obj evil non renseigné";
        case MISSING_ID_SHIP_ATTRIBUT_EVIL:             return "[ERROR] Attribut id_ship pour l'obj evil non renseigné";
        case MISSING_ID_PLANET_ORIGIN_ATTRIBUT_EVIL:    return "[ERROR] Attribut id_planet_origin pour l'obj evil non renseigné";
        case MISSING_ID_GRADE_ATTRIBUT_EVIL:            return "[ERROR] Attribut id_grade pour l'obj evil non renseigné";
        case MAX_ITEM_OVERFLOW_EVIL:                    return "[ERROR] Nombre max d'item dans l'inventaire atteint";
        case UNKNOWN_EVIL:                              return "[ERROR] Evil non trouvé";
        case UNKNOWN_ITEM_EVIL:                         return "[ERROR] le Mechant ne possède pas cet item";

        case NOT_ENOUGHT_ATTRIBUT_PNJ:                  return "[ERROR] Il manque des attributs à l'obj pnj";
        case MISSING_ID_ATTRIBUT_PNJ:                   return "[ERROR] Attribut id pour l'obj pnj non renseigné";
        case MISSING_NAME_ATTRIBUT_PNJ:                 return "[ERROR] Attribut name pour l'obj pnj non renseigné";
        case MISSING_AP_ATTRIBUT_PNJ:                   return "[ERROR] Attribut ap pour l'obj pnj non renseigné";
        case MISSING_HP_ATTRIBUT_PNJ:                   return "[ERROR] Attribut hp pour l'obj pnj non renseigné";
        case MISSING_DP_ATTRIBUT_PNJ:                   return "[ERROR] Attribut dp pour l'obj pnj non renseigné";
        case MISSING_ID_PLANET_ATTRIBUT_PNJ:            return "[ERROR] Attribut id_planet pour l'obj pnj non renseigné";
        case MISSING_ID_SHIP_ATTRIBUT_PNJ:              return "[ERROR] Attribut id_ship pour l'obj pnj non renseigné";
        case MISSING_ID_PLANET_ORIGIN_ATTRIBUT_PNJ:     return "[ERROR] Attribut id_planet_origin pour l'obj pnj non renseigné";
        case MISSING_ID_GRADE_ATTRIBUT_PNJ:             return "[ERROR] Attribut id_grade pour l'obj pnj non renseigné";
        case MAX_ITEM_OVERFLOW_PNJ:                     return "[ERROR] Nombre max d'item dans l'inventaire atteint";
        case UNKNOWN_PNJ:                               return "[ERROR] Pnj non trouvé";
        case UNKNOWN_ITEM_PNJ:                          return "[ERROR] le Pnj ne possède pas cet item";

        case NOT_ENOUGHT_ATTRIBUT_ITEM:                 return "[ERROR] Il manque des attributs à l'obj item";
        case MISSING_ID_ATTRIBUT_ITEM:                  return "[ERROR] Attribut id pour l'obj item non renseigné";
        case MISSING_NAME_ATTRIBUT_ITEM:                return "[ERROR] Attribut name pour l'obj item non renseigné";
        case MISSING_STAT_ATTRIBUT_ITEM:                return "[ERROR] Attribut stat pour l'obj item non renseigné";
        case MISSING_EFFECT_ATTRIBUT_ITEM:              return "[ERROR] Attribut effect pour l'obj item non renseigné";
        case MISSING_ID_OWNER_ATTRIBUT_ITEM:            return "[ERROR] Attribut id_owner pour l'obj item non renseigné";
        case MISSING_TYPE_OWNER_ATTRIBUT_ITEM:          return "[ERROR] Attribut type_owner pour l'obj item non renseigné";
        case UNKNOWN_ITEM:                              return "[ERROR] Item non trouvé";

        case MISSING_ID_ATTRIBUT_GRADE:                 return "[ERROR] Attribut id pour l'obj grade non renseigné";
        case MISSING_NAME_ATTRIBUT_GRADE:               return "[ERROR] Attribut name pour l'obj grade non renseigné";
        case MISSING_LEVEL_ATTRIBUT_GRADE:              return "[ERROR] Attribut level pour l'obj grade non renseigné";
        case UNKNOWN_GRADE:                             return "[ERROR] Grade non trouvé";

        case MISSING_ENTITY_TYPE_ATTRIBUT:              return "[ERROR] Attribut entity_type non renseigné";
        case MISSING_DEFENSE_ATTRIBUT:                  return "[ERROR] Attribut defenseur non renseigné";
        case MISSING_ATTACK_ATTRIBUT:                   return "[ERROR] Attribut attaquant non renseigné";
        case MISSING_ENTITY_ID_ATTRIBUT:                return "[ERROR] Attribut entity_id non renseigné";
        case MISSING_ACTION_ATTRIBUT:                   return "[ERROR] Attribut action non renseigné";
        case MISSING_ITEMS_ATTRIBUT:                    return "[ERROR] Attribut items non renseigné";
        case MISSING_DEFENSE_TYPE_ATTRIBUT:             return "[ERROR] Attribut type du defenseur non renseigné";
        case MISSING_DEFENSE_ID_ATTRIBUT:               return "[ERROR] Attribut id du defenseur non renseigné";
        case MISSING_ATTACK_TYPE_ATTRIBUT:              return "[ERROR] Attribut type de l'attaquant non renseigné";
        case MISSING_ATTACK_ID_ATTRIBUT:                return "[ERROR] Attribut id de l'attaquant non renseigné";
        case UNKNOWN_DEFENSE_OR_ATTACK:                 return "[ERROR] L'attaquant et/ou le defenseur n'existe pas";
        case UNKNOWN_ID_GRADE:                          return "[ERROR] Attribut id_grade n'existe pas";
        case ENTITY_OUT_RANGE:                          return "[ERROR] Les Entités ne peuvent pas s'attaquer directement";
        case UNKNOWN_ENTITY:                            return "[ERROR] type d'entité inconnue";
        case UNKNOWN_ACTION:                            return "[ERROR] type d'action inconnue";
        case ITEM_OCCUPY:                               return "[ERROR] L'objet n'est pas disponible";
        case MISSING_INVENTORY:                         return "[ERROR] L'objet ne possède pas d'inventaire";
        case MISSING_GRADE:                             return "[ERROR] Ce type d'entité ne possède pas de grade";
        case UNKNOWN_ATTACK_ACTION:                     return "[ERROR] Ce type d'entité ne peut pas attaquer";
        case UNAUTHORIZED:                              return "[ERROR] Bad TOKEN";
        default:                                        return "[ERROR] Erreur inconnue";
    }
}

// ---------------------------------------------------------------------------
// Utilitaires
// ---------------------------------------------------------------------------

bool List::checkJson(string const &json)
{
    int cpt = 0;
    for (char c : json)
    {
        if (c == '{') cpt++;
        if (c == '}') cpt--;
    }
    return cpt == 0;
}

vector<string> List::split(string str, string delimiter)
{
    vector<string> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
            size_t idx = str.find(delimiter, start);
            if (idx == string::npos) break;
            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }
    return v;
}
