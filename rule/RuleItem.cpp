/*
 * File: RuleItem.cpp                                                          *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:04:30 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 9:59:00 am                         *
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

void   RuleItem::fillResultRequestKill(ResultRequest *result, int id) {
    if (!this->isItemExist(result, id)) return;
    this->addToResultRequest(result, id);
}

void   RuleItem::fillResultRequestGetInfos(ResultRequest *result, int id) {
    if (id != -1 && !this->isItemExist(result, id)) return;
    for (auto type : this->_tableDeCorrespondance) { // comme fonctionnement par unique_ptr on prend la table des corespondances
        for (auto item : type.second) {
            if (id != -1 && item.first == id || id == -1) this->addToResultRequest(result, item.first); 
        }
    }
}

void    RuleItem::fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string) {
    if (attr_int.find("stat") == attr_int.end()) { result->_code = MISSING_STAT_ATTRIBUT_ITEM; return; }
    if (attr_string.find("name") == attr_string.end()) { result->_code = MISSING_NAME_ATTRIBUT_ITEM; return; }
    if (attr_int.find("effect") == attr_int.end()) { result->_code = MISSING_EFFECT_ATTRIBUT_ITEM; return; }
    if (attr_int.find("id_owner") == attr_int.end()) { result->_code = MISSING_ID_OWNER_ATTRIBUT_ITEM; return; }
    if (attr_int.find("type_owner") == attr_int.end()) { result->_code = MISSING_TYPE_OWNER_ATTRIBUT_ITEM; return; }

    if ((OBJETS)attr_int.at("type_owner") != NONE) {
        switch (attr_int.at("type_owner"))
        {
        case HEROS:
        case EVIL:
        case PNJ:
            if (!this->isQuidamExist(result, (OBJETS)attr_int.at("type_owner"), attr_int.at("id_owner"))) return;
            break;
        case SPACESHIP:
            if (!this->isSpaceshipExist(result, attr_int.at("id_owner"))) return;
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