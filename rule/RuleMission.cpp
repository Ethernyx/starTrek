/*
 * File: RuleMission.cpp                                                       *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 10:53:48 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:03:43 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RuleMission.hh"

bool    RuleMission::kill(map<int, shared_ptr<Mission>> &missions) {
    bool isOk = true;

    for(auto it = missions.begin(); it != missions.end(); it++) {
        if (!(isOk = this->deleteMission(it->first))) return isOk;
    }
    return isOk;
}

ResultRequest   &RuleMission::fillResultRequestKill(int id) {
    ResultRequest result;

    if (this->_missions.find(id) == this->_missions.end()) { result._code = UNKNOWN_MISSION; return result; }
    this->addToResultRequest(&result, id);
    return result;
}

void    RuleMission::addToResultRequest(ResultRequest *result, int id) {
    result->_missions[id] = this->_missions[id];
}