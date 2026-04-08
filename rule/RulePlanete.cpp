/*
 * File: RulePlanete.cpp                                                       *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:19:29 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 6:49:58 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RulePlanete.hh"

bool    RulePlanete::kill(map<int, shared_ptr<Planete>> &planetes) {
    bool isOk = true;

    for(auto it = planetes.begin(); it != planetes.end(); it++) {
        if (!(isOk = this->deletePlanete(it->first))) return isOk;
    }
    return isOk;
}

void   RulePlanete::fillResultRequestKill(ResultRequest *result, int id) {
    if (!this->isPlaneteExist(result, id)) return;
    
    for (auto h = this->_planetes[id]->getHabitants().begin(); h != this->_planetes[id]->getHabitants().end(); h++)
    {
        if (h->lock()) {
            // je remplis mon array de perso ou pnj qui vont mourir avec la planete
            for (auto p = this->_quidams[h->lock()->getType()].begin(); p != this->_quidams[h->lock()->getType()].end(); p++) {
                if (p->second == h->lock())
                    RuleQuidam::addToResultRequest(result, p->second->getType(), p->first);
            }
        }

        // recuperation des ID de l'inventaire
        for (auto i = h->lock()->getInventory().begin(); i != h->lock()->getInventory().end(); i++)
            RuleItem::addToResultRequest(result, i->first);
    }
    this->addToResultRequest(result, id);
}

void    RulePlanete::addToResultRequest(ResultRequest *result, int id) {
    result->_planetes[id] = this->_planetes[id];
}

void   RulePlanete::fillResultGetHabitant(ResultRequest *result, int id) {
    if (!this->isPlaneteExist(result, id)) return;

    for (auto h : this->_planetes[id]->getHabitants()) {
        if (!h.lock()) continue;
        for (auto p : this->_quidams[h.lock()->getType()]) if (p.second == h.lock()) {
            RuleQuidam::addToResultRequest(result, p.second->getType(), p.first);
        }
    }
    this->addToResultRequest(result, id);
}

void   RulePlanete::fillResultRequestGetInfos(ResultRequest *result, int id) {
    ResultRequest   result;

    if (id != -1 && !this->isPlaneteExist(result, id)) return;
    for (auto p : this->_planetes) if ((id != -1 && id == p.first) || id == -1) this->addToResultRequest(result, p.first);
}

void    RulePlanete::fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string) {
    if (attr_string.find("name") == attr_string.end()) { result->_code = MISSING_NAME_ATTRIBUT_PLANET; return; }
    if (attr_string.find("description") == attr_string.end()) { result->_code = MISSING_DESC_ATTRIBUT_PLANET; return; }

    int id = this->addPlanet(attr_int, attr_string);
    this->addToResultRequest(result, id);
}