/*
 * File: RuleSpaceship.cpp                                                     *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:14:42 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 10:07:29 am                        *
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

void   RuleSpaceship::fillResultRequestKill(ResultRequest *result, int id) {
    if (!this->isSpaceshipExist(result, id)) return;
    
    for (auto it = this->_flotte[id]->getEquipage().begin(); it != this->_flotte[id]->getEquipage().end(); it++) {
        if (it->lock()) {
            for (auto p = this->_quidams[it->lock()->getType()].begin(); p != this->_quidams[it->lock()->getType()].end(); p++) {
                if (p->second == it->lock())
                    RuleQuidam::addToResultRequest(result, p->second->getType(), p->first);
            }
        }
    }
    for (auto it = this->_flotte[id]->getInventory().begin(); it != this->_flotte[id]->getInventory().end(); it++)
        RuleItem::addToResultRequest(result, it->first);
    this->addToResultRequest(result, id);
}

void    RuleSpaceship::addToResultRequest(ResultRequest *result, int id) {
    result->_spaceships[id] = this->_flotte[id];
}

void   RuleSpaceship::fillResultGetEquipage(ResultRequest *result, int id) {
    if (!this->isSpaceshipExist(result, id)) return;
    
    for (auto h : this->_flotte[id]->getEquipage()) {
        if (!h.lock()) continue;
        for (auto p : this->_quidams[h.lock()->getType()]) if (p.second == h.lock()) {
            RuleQuidam::addToResultRequest(result, p.second->getType(), p.first);
        }
    }
    this->addToResultRequest(result, id);
}

void   RuleSpaceship::fillResultRequestGetInventory(ResultRequest *result, int id) {
    if (!this->isSpaceshipExist(result, id)) return;
    for (auto item : this->_tableDeCorrespondance[SPACESHIP]) {
        if(item.second != id) continue;
        RuleItem::addToResultRequest(result, item.first);
    }
    this->addToResultRequest(result, id);
}

void   RuleSpaceship::fillResultRequestGetInfos(ResultRequest *result, int id) {
    if (id != -1 && !this->isSpaceshipExist(result, id)) return;
    for (auto s : this->_flotte) if ((id != -1 && id == s.first) || id == -1) this->addToResultRequest(result, s.first);
}

void    RuleSpaceship::fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string) {
    if (attr_string.find("name") == attr_string.end()) { result->_code = MISSING_NAME_ATTRIBUT_SPACESHIP; return; }
    if (attr_string.find("description") == attr_string.end()) { result->_code = MISSING_DESC_ATTRIBUT_SPACESHIP; return; }
    if (attr_int.find("ap") == attr_int.end()) { result->_code = MISSING_AP_ATTRIBUT_SPACESHIP; return; }
    if (attr_int.find("dp") == attr_int.end()) { result->_code = MISSING_DP_ATTRIBUT_SPACESHIP; return; }
    if (attr_int.find("hp") == attr_int.end()) { result->_code = MISSING_HP_ATTRIBUT_SPACESHIP; return; }

    int id = this->addSpaceShip(attr_int, attr_string);
    this->addToResultRequest(result, id);
}

void RuleSpaceship::simpleAttack(ResultRequest *result, int id_def, int id_att) {
    auto a = this->_flotte[id_att];
    auto v = this->_flotte[id_def];

    if (a == nullptr || v == nullptr) { result->_code = UNKNOWN_DEFENSE_OR_ATTACK; return; }
    v->setAttributs(v->getDp(), v->getHp() - (a->getAp() - v->getDp()), v->getDp()); // HP vic - (attack AP - vi DP)
    this->addToResultRequest(result, id_def);
}