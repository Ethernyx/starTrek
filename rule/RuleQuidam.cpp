/*
 * File: RuleQuidam.cpp                                                        *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:09:50 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 7:05:06 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RuleQuidam.hh"

bool    RuleQuidam::kill(map<OBJETS, map<int, shared_ptr<AQuidam>>> &quidams) {
    for(auto type = quidams.begin(); type != quidams.end(); type++) {
        for (auto q = type->second.begin(); q != type->second.end(); q++) {
            if (!this->deletePerso(q->first)) return false;
        }
    }
    return true;
}

void   RuleQuidam::fillResultRequestKill(ResultRequest *result, OBJETS type, int id) {
    // recuperation des ID de l'inventaire
    if (!this->isQuidamExist(result, type, id)) return;

    for (auto it = this->_quidams[type][id]->getInventory().begin(); it != this->_quidams[type][id]->getInventory().end(); it++)
        RuleItem::addToResultRequest(result, it->first);
    this->addToResultRequest(result, type, id);
}

void   RuleQuidam::fillResultRequestGetInventory(ResultRequest *result, OBJETS type, int id) {
    if (!this->isQuidamExist(result, type, id)) return;
    for (auto item : this->_tableDeCorrespondance[type]) {
        if(item.second != id) continue;
        RuleItem::addToResultRequest(result, item.first);
    }
    this->addToResultRequest(result, type, id);
}

void    RuleQuidam::addToResultRequest(ResultRequest *result, OBJETS type, int id) {
    result->_quidams[type][id] = this->_quidams[type][id];
}

void   RuleQuidam::fillResultRequestGetInfos(ResultRequest *result, OBJETS type, int id) {
    vector<OBJETS>  types;

    if (id != -1 && type != LIVING && !this->isQuidamExist(result, type, id)) return;

    if (type == LIVING) types = { HEROS, PNJ, EVIL };
    else types = { type };

    for (auto t : types) for (auto q : this->_quidams[t]) if ((id != -1 && id == q.first) || id == -1) this->addToResultRequest(result, t, q.first);
}

void   RuleQuidam::fillResultRequestPromote(ResultRequest *result, int id_grade, OBJETS type_quidam, int id_quidam) {
    bool            isOk = true;

    if (find(QUIDAMS.begin(), QUIDAMS.end(), type_quidam) == QUIDAMS.end()) { result->_code = MISSING_GRADE; return; }
    if (!this->isQuidamExist(result, type_quidam, id_quidam)) return;
    if (!(isOk = this->_grades[this->_quidams[type_quidam][id_quidam]->getIdGrade()]->deleteMembre(this->_quidams[type_quidam][id_quidam]))) { result->_code = ERROR_DELETE_MEMBER; return; }
    if (this->_quidams[type_quidam][id_quidam]->getIdGrade() != 0) this->_grades[this->_quidams[type_quidam][id_quidam]->getIdGrade()]->deleteMembre(this->_quidams[type_quidam][id_quidam]);
    this->_grades[id_grade]->addMembre(this->_quidams[type_quidam][id_quidam]);
    this->addToResultRequest(result, type_quidam, id_quidam);
}

void    RuleQuidam::fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string) {
    if (attr_int.find("entity_type") == attr_int.end()) { result->_code = MISSING_ENTITY_TYPE_ATTRIBUT; return; }
    if (attr_string.find("name") == attr_string.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_NAME_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_NAME_ATTRIBUT_PNJ : MISSING_NAME_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("ap") == attr_int.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_AP_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_AP_ATTRIBUT_PNJ : MISSING_AP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("dp") == attr_int.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_DP_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_DP_ATTRIBUT_PNJ : MISSING_DP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("hp") == attr_int.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_HP_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_HP_ATTRIBUT_PNJ : MISSING_HP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_planet") == attr_int.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_ID_PLANET_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_ID_PLANET_ATTRIBUT_PNJ : MISSING_ID_PLANET_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_ship") == attr_int.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_ID_SHIP_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_ID_SHIP_ATTRIBUT_PNJ : MISSING_ID_SHIP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_planet_origin") == attr_int.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_PNJ : MISSING_ID_PLANET_ORIGIN_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_grade") == attr_int.end()) { result->_code = (attr_int.at("entity_type") == HEROS ? MISSING_ID_GRADE_ATTRIBUT_HEROS : (attr_int.at("entity_type") == PNJ ? MISSING_ID_GRADE_ATTRIBUT_PNJ : MISSING_ID_GRADE_ATTRIBUT_EVIL)); return; }

    if (!this->isPlaneteExist(result, attr_int.at("id_planet_origin"))) return;
    if (!this->isPlaneteExist(result, attr_int.at("id_planet"))) return;
    if (!this->isSpaceshipExist(result, attr_int.at("id_ship"))) return;
    if (!this->isGradeExist(result, attr_int.at("id_grade"))) return;

    int id = this->addQuidam(attr_int, attr_string);
    this->addToResultRequest(result, (OBJETS)attr_int.at("entity_type"), id);
}

void RuleQuidam::simpleAttack(ResultRequest *result, OBJETS type_def, int id_def, OBJETS type_att, int id_att) {
    auto a = this->_quidams[type_att][id_att];
    auto v = this->_quidams[type_def][id_def];

    if (a == nullptr || v == nullptr) { result->_code = UNKNOWN_DEFENSE_OR_ATTACK; return; }
    v->setAttributs(v->getDp(), v->getHp() - (a->getAp() - v->getDp()), v->getDp()); // HP vic - (attack AP - vi DP)
    if (v->getHp() <= 0) result->_code = ENTITY_IS_DEATH;
    this->addToResultRequest(result, type_def, id_def);
}

void    RuleQuidam::fillResultRequestExchangeItem(ResultRequest *result, vector<int> &items, OBJETS type, int id, string action) {
    for (auto item : items) {
        if(strcmp(action.c_str(),"pull") == 0) this->takeItem(result, item, type, id);
        else if (strcmp(action.c_str(), "push") == 0) this->giveItem(result, item, type, id);
        else result->_code = UNKNOWN_ACTION;
        if (result->_code != OK) return;
    }
}

void    RuleQuidam::takeItem(ResultRequest *result, int item, OBJETS type, int quidam) {
    /* je verifie si l'item exist et est libre et si le quidam exist et si son inventaire n'est pas déjà remplit */
    if (!this->isItemExist(result, item)) return;
    if (!this->isQuidamExist(result, type, quidam)) return;
    if (this->_tableDeCorrespondance[NONE].find(item) == this->_tableDeCorrespondance[NONE].end()) { result->_code = ITEM_OCCUPY; return; }
    if (this->_quidams[type][quidam]->getInventory().size() >= this->_quidams[type][quidam]->getMaxItem()) { result->_code = (type == HEROS ? MAX_ITEM_OVERFLOW_HEROS : (type == PNJ ? MAX_ITEM_OVERFLOW_PNJ : MAX_ITEM_OVERFLOW_EVIL)); return; }

    this->_quidams[type][quidam]->addItem(this->_items[item], item);
    this->_quidams[type][quidam]->getInventory()[item]->setOwner(quidam, type);

    /* j'erase l'ancienne corespondance et j'ajoute la nouvelle */
    this->_tableDeCorrespondance[NONE].erase(this->_tableDeCorrespondance[NONE].find(item));
    this->_tableDeCorrespondance[type][item] = quidam;
}

void    RuleQuidam::giveItem(ResultRequest *result, int item, OBJETS type, int quidam) {
    /* je verifie si l'item existe et apartient bien à un quidam qui existe aussi */
    if (!this->isItemExist(result, item)) return;
    if (!this->isQuidamExist(result, type, quidam)) return;
    if (this->_tableDeCorrespondance[type].find(item) == this->_tableDeCorrespondance[type].end() || this->_tableDeCorrespondance[type][item] != quidam) { result->_code = (type == HEROS ? UNKNOWN_ITEM_HEROS: (type == PNJ ? UNKNOWN_ITEM_PNJ : UNKNOWN_ITEM_EVIL)); return; }
    
    this->_items[item].swap(this->getPerso(quidam)->getInventory()[item]);
    this->_quidams[type][quidam]->getInventory().find(item)->second->setOwner(0, NONE);

    /* j'erase l'ancienne corespondance et j'ajoute la nouvelle */
    this->_tableDeCorrespondance[type].erase(this->_tableDeCorrespondance[type].find(item));
    this->_tableDeCorrespondance[NONE][item] = 0;
}