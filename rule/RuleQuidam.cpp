/*
 * File: RuleQuidam.cpp                                                        *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:09:50 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 5:18:46 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RuleQuidam.hh"

bool    RuleQuidam::kill(map<OBJETS, map<int, shared_ptr<AQuidam>>> &quidams) {
    bool isOk = true;

    for(auto it = quidams.begin(); it != quidams.end(); it++) {
        isOk = this->deletePerso(it->first);
        if (!isOk) return isOk;
    }
    return isOk;
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

ResultRequest   RuleQuidam::fillResultRequestPromote(int id_grade, OBJETS type_quidam, int id_quidam) {
    ResultRequest   result;
    bool            isOk = true;

    if (!this->isQuidamExist(&result, type_quidam, id_quidam)) return result;
    if (!(isOk = this->_grades[this->_quidams[type_quidam][id_quidam]->getIdGrade()]->deleteMembre(this->_quidams[type_quidam][id_quidam]))) { result._code = ERROR_DELETE_MEMBER; return result; }
    this->_grades[id_grade]->addMembre(this->_quidams[type_quidam][id_quidam]);
    this->addToResultRequest(&result, type_quidam, id_quidam);
    return result;
}