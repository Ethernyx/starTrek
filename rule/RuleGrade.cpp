/*
 * File: RuleGrade.cpp                                                         *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 10:45:25 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 5:22:18 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RuleGrade.hh"

bool    RuleGrade::kill(map<int, shared_ptr<Grade>> &grades) {
    bool isOk = true;

    for(auto it = grades.begin(); it != grades.end(); it++) {
        isOk = this->deleteGrade(it->first);
        if (!isOk) return isOk;
    }
    return isOk;
}

ResultRequest   RuleGrade::fillResultRequestKill(int id) {
    ResultRequest result;

    if (!this->isGradeExist(&result, id)) return result;
    this->addToResultRequest(&result, id);
    return result;
}

void    RuleGrade::addToResultRequest(ResultRequest *result, int id) {
    result->_grades[id] = _grades[id];
}

ResultRequest   RuleGrade::fillResultRequestGetHierarchy(int id) {
    ResultRequest   result;

    if (!this->isGradeExist(&result, id)) return result;
    for (auto h : this->_grades[id]->getMembre()) {
        if (!h.lock()) continue;
        RuleQuidam::addToResultRequest(&result, h.lock()->getType(), this->getIdQuidam(h.lock()));
    }
    this->addToResultRequest(&result, id);
    return result;
}

ResultRequest   RuleGrade::fillResultRequestGetInfos(int id) {
    ResultRequest   result;

    if (id != -1 && !this->isGradeExist(&result, id)) return result;
    for (auto g : this->_grades) if ((id != -1 && id == g.first) || id == -1) this->addToResultRequest(&result, g.first);
    return result;
}