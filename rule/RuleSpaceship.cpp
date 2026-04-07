/*
 * File: RuleSpaceship.cpp                                                     *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:14:42 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 5:32:48 pm                          *
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

ResultRequest   RuleSpaceship::fillResultRequestKill(int id) {
    ResultRequest result;

    if (!this->isSpaceshipExist(&result, id)) return result;
    
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

ResultRequest   RuleSpaceship::fillResultGetEquipage(int id) {
    ResultRequest   result;

    if (!this->isSpaceshipExist(&result, id)) return result;
    
    for (auto h : this->_flotte[id]->getEquipage()) {
        if (!h.lock()) continue;
        for (auto p : this->_quidams[h.lock()->getType()]) if (p.second == h.lock()) {
            RuleQuidam::addToResultRequest(&result, p.second->getType(), p.first);
        }
    }
    this->addToResultRequest(&result, id);
    return result;
}

ResultRequest   RuleSpaceship::fillResultRequestGetInventory(int id) {
    ResultRequest   result;

    if (!this->isSpaceshipExist(&result, id)) return result;
    for (auto item : this->_tableDeCorrespondance[SPACESHIP]) {
        if(item.second != id) continue;
        RuleItem::addToResultRequest(&result, item.first);
    }
    this->addToResultRequest(&result, id);
    return result;
}

ResultRequest   RuleSpaceship::fillResultRequestGetInfos(int id) {
    ResultRequest   result;

    if (id != -1 && !this->isSpaceshipExist(&result, id)) return result;
    for (auto s : this->_flotte) if ((id != -1 && id == s.first) || id == -1) this->addToResultRequest(&result, s.first);
    return result;
}