/*
 * File: RuleQuidam.cpp                                                        *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:09:50 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 3:53:31 pm                        *
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

ResultRequest   RuleQuidam::fillResultRequestKill(OBJETS type, int id) {
    ResultRequest result;
    // recuperation des ID de l'inventaire
    if (!this->isQuidamExist(&result, type, id)) return result;

    for (auto it = this->_quidams[type][id]->getInventory().begin(); it != this->_quidams[type][id]->getInventory().end(); it++)
        RuleItem::addToResultRequest(&result, it->first);
    this->addToResultRequest(&result, type, id);
    return result;
}

ResultRequest   RuleQuidam::fillResultRequestGetInventory(OBJETS type, int id) {
    ResultRequest   result;

    if (!this->isQuidamExist(&result, type, id)) return result;
    for (auto item : this->_tableDeCorrespondance[type]) {
        if(item.second != id) continue;
        RuleItem::addToResultRequest(&result, item.first);
    }
    this->addToResultRequest(&result, type, id);
    return result;
}

void    RuleQuidam::addToResultRequest(ResultRequest *result, OBJETS type, int id) {
    result->_quidams[type][id] = this->_quidams[type][id];
}

ResultRequest   RuleQuidam::fillResultRequestGetInfos(OBJETS type, int id) {
    ResultRequest   result;
    vector<OBJETS>  types;

    if (id != -1 && type != LIVING && !this->isQuidamExist(&result, type, id)) return result;

    if (type == LIVING) types = { HEROS, PNJ, EVIL };
    else types = { type };

    for (auto t : types) for (auto q : this->_quidams[t]) if ((id != -1 && id == q.first) || id == -1) this->addToResultRequest(&result, t, q.first);
    return result;
}

void   RuleQuidam::fillResultRequestPromote(ResultRequest *result, int id_grade, OBJETS type_quidam, int id_quidam) {
    bool            isOk = true;

    if (find(QUIDAMS.begin(), QUIDAMS.end(), type_quidam) == QUIDAMS.end()) { result->_code = MISSING_GRADE; return; }
    if (!this->isQuidamExist(result, type_quidam, id_quidam)) return;
    if (!(isOk = this->_grades[this->_quidams[type_quidam][id_quidam]->getIdGrade()]->deleteMembre(this->_quidams[type_quidam][id_quidam]))) { result->_code = ERROR_DELETE_MEMBER; return; }
    this->_grades[id_grade]->addMembre(this->_quidams[type_quidam][id_quidam]);
    this->addToResultRequest(result, type_quidam, id_quidam);
}

void    RuleQuidam::fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string) {
    if (attr_int.find("entity_type") == attr_int.end()) { result->_code = MISSING_ENTITY_TYPE_ATTRIBUT; return; }
    if (attr_string.find("name") == attr_string.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_NAME_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_NAME_ATTRIBUT_PNJ : MISSING_NAME_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("ap") == attr_int.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_AP_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_AP_ATTRIBUT_PNJ : MISSING_AP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("dp") == attr_int.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_DP_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_DP_ATTRIBUT_PNJ : MISSING_DP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("hp") == attr_int.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_HP_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_HP_ATTRIBUT_PNJ : MISSING_HP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_planet") == attr_int.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_ID_PLANET_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_ID_PLANET_ATTRIBUT_PNJ : MISSING_ID_PLANET_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_ship") == attr_int.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_ID_SHIP_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_ID_SHIP_ATTRIBUT_PNJ : MISSING_ID_SHIP_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_planet_origin") == attr_int.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_ID_PLANET_ORIGIN_ATTRIBUT_PNJ : MISSING_ID_PLANET_ORIGIN_ATTRIBUT_EVIL)); return; }
    if (attr_int.find("id_grade") == attr_int.end()) { result->_code = (attr_int["entity_type"] == HEROS ? MISSING_ID_GRADE_ATTRIBUT_HEROS : (attr_int["entity_type"] == PNJ ? MISSING_ID_GRADE_ATTRIBUT_PNJ : MISSING_ID_GRADE_ATTRIBUT_EVIL)); return; }

    if (!this->isPlaneteExist(result, attr_int["id_planete_origin"])) return;
    if (!this->isPlaneteExist(result, attr_int["id_planete"])) return;
    if (!this->isSpaceshipExist(result, attr_int["is_ship"])) return;
    if (!this->isGradeExist(result, attr_int["id_grade"])) return;

    int id = this->addQuidam(attr_int, attr_string);
    this->addToResultRequest(result, (OBJETS)attr_int["entity_type"], id);


    
    
}