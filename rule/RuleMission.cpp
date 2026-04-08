/*
 * File: RuleMission.cpp                                                       *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 10:53:48 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 6:48:37 pm                        *
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

void   RuleMission::fillResultRequestKill(ResultRequest *result, int id) {
    if (!this->isMissionExist(result, id)) return;
    this->addToResultRequest(result, id);
}

void    RuleMission::addToResultRequest(ResultRequest *result, int id) {
    result->_missions[id] = this->_missions[id];
}

void   RuleMission::fillResultRequestGetInfos(ResultRequest *result, int id) {
    if (id != -1 && !this->isMissionExist(result, id)) return;
    for (auto m : this->_missions) if ((id != -1 && id == m.first) || id == -1) this->addToResultRequest(result, m.first);
}

void    RuleMission::fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string) {
    if (attr_int.find("is_complete") == attr_int.end()) { result->_code = MISSING_IS_COMPLETE_ATTRIBUT_MISSION; return; }
    if (attr_string.find("name") == attr_string.end()) { result->_code = MISSING_NAME_ATTRIBUT_MISSION; return; }
    if (attr_string.find("description") == attr_string.end()) { result->_code = MISSING_DESC_ATTRIBUT_MISSION; return; }

    int id = this->addMission(attr_int, attr_string);
    this->addToResultRequest(result, id);
}