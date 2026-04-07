/*
 * File: RuleQuidam.cpp                                                        *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:09:50 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:09:26 am                         *
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

ResultRequest   &RuleQuidam::fillResultRequestKill(OBJETS type, int id) {
    ResultRequest result;
    // recuperation des ID de l'inventaire
    if (this->_quidams[type].find(id) == this->_quidams[type].end()) {
        result._code = (type == HEROS ? UNKNOWN_HEROS : (type == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL));
        return result;
    }
    for (auto it = this->_quidams[type][id]->getInventory().begin(); it != this->_quidams[type][id]->getInventory().end(); it++)
        RuleItem::addToResultRequest(&result, it->first);
    this->addToResultRequest(&result, type, id);
    return result;
}

void    RuleQuidam::addToResultRequest(ResultRequest *result, OBJETS type, int id) {
    result->_quidams[type][id] = this->_quidams[type][id];
}