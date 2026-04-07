/*
 * File: RuleSpaceship.cpp                                                     *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:14:42 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:25:33 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RuleSpaceship.hh"

bool    RuleSpaceship::kill(map<int, shared_ptr<Spaceship>> &spaceships) {
    bool isOk = true;

    for(auto it = spaceships.begin(); it != spaceships.end(); it++) {
        if (!(isOk = this->deleteSpaceship(it->first))) return isOk;
    }
    return isOk;
}

ResultRequest   &RuleSpaceship::fillResultRequestKill(int id) {
    ResultRequest result;

    if (this->_flotte.find(id) == this->_flotte.end()) {
        result._code = UNKNOWN_SPACESHIP;
        return result;
    }
    for (auto it = this->_flotte[id]->getEquipage().begin(); it != this->_flotte[id]->getEquipage().end(); it++) {
        if (it->lock()) {
            for (auto p = this->_quidams[it->lock()->getType()].begin(); p != this->_quidams[it->lock()->getType()].end(); p++) {
                if (p->second == it->lock())
                    RuleQuidam::addToResultRequest(&result, p->second->getType(), p->first);
            }
        }
    }
    for (auto it = this->_flotte[id]->getInventory().begin(); it != this->_flotte[id]->getInventory().end(); it++)
        RuleItem::addToResultRequest(&result, it->first);
    this->addToResultRequest(&result, id);
    return result;
}

void    RuleSpaceship::addToResultRequest(ResultRequest *result, int id) {
    result->_spaceships[id] = this->_flotte[id];
}