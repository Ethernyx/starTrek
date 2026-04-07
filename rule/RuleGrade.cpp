/*
 * File: RuleGrade.cpp                                                         *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 10:45:25 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:15:36 am                         *
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

ResultRequest   &RuleGrade::fillResultRequestKill(int id) {
    ResultRequest result;

    if (this->_grades.find(id) == this->_grades.end()) { result._code = UNKNOWN_GRADE; return result; }
    this->addToResultRequest(&result, id);
    return result;
}

void    RuleGrade::addToResultRequest(ResultRequest *result, int id) {
    result->_grades[id] = _grades[id];
}