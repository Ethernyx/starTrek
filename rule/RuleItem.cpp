/*
 * File: RuleItem.cpp                                                          *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:04:30 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 3:42:45 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RuleItem.hh"

bool    RuleItem::kill(map<int, Item*> &items) {
    bool isOk = true;

    for(auto it = items.begin(); it != items.end(); it++) {
        isOk = this->deleteItem(it->first);
        if (!isOk) return isOk;
    }
    return isOk;
}

void    RuleItem::addToResultRequest(ResultRequest *result, int id) {
    result->_items[id] = this->_items[id].get();
}

ResultRequest   RuleItem::fillResultRequestKill(int id) {
    ResultRequest result;

    if (!this->isItemExist(&result, id)) return result;

    this->addToResultRequest(&result, id);
    return result;
}

ResultRequest   RuleItem::fillResultRequestGetInfos(int id) {
    ResultRequest   result;

    if (id != -1 && !this->isItemExist(&result, id)) return result;
    for (auto type : this->_tableDeCorrespondance) { // comme fonctionnement par unique_ptr on prend la table des corespondances
        for (auto item : type.second) {
            if (id != -1 && item.first == id || id == -1) this->addToResultRequest(&result, item.first); 
        }
    }
    return result;
}

void    RuleItem::fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string) {
    if (attr_int.find("stat") == attr_int.end()) { result->_code = MISSING_STAT_ATTRIBUT_ITEM; return; }
    if (attr_string.find("name") == attr_string.end()) { result->_code = MISSING_NAME_ATTRIBUT_ITEM; return; }
    if (attr_int.find("effect") == attr_int.end()) { result->_code = MISSING_EFFECT_ATTRIBUT_ITEM; return; }
    if (attr_int.find("id_owner") == attr_int.end()) { result->_code = MISSING_ID_OWNER_ATTRIBUT_ITEM; return; }
    if (attr_int.find("type_owner") == attr_int.end()) { result->_code = MISSING_TYPE_OWNER_ATTRIBUT_ITEM; return; }

    if ((OBJETS)attr_int["type_owner"] != NONE) {
        switch (attr_int["type_owner"])
        {
        case HEROS:
        case EVIL:
        case PNJ:
            if (!this->isQuidamExist(result, (OBJETS)attr_int["type_owner"], attr_int["id_owner"])) return;
            break;
        case SPACESHIP:
            if (!this->isSpaceshipExist(result, attr_int["id_owner"])) return;
            break;
        case PLANETE:
        case MISSION:
        case GRADE:
        case ITEM:
            result->_code = MISSING_INVENTORY;
            return;
            break;
        default:
            result->_code = UNKNOWN_ENTITY;
            return;
            break;
        }
    }

    int id = this->addItem(attr_int, attr_string);
    this->addToResultRequest(result, id);
}