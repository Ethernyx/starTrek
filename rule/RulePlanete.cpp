/*
 * File: RulePlanete.cpp                                                       *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:19:29 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:06:38 am                         *
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

ResultRequest   &RulePlanete::fillResultRequestKill(int id) {
    ResultRequest result;

    if (this->_planetes.find(id) == this->_planetes.end()) {
        result._code = UNKNOWN_PLANET;
        return result;
    }
    for (auto h = this->_planetes[id]->getHabitants().begin(); h != this->_planetes[id]->getHabitants().end(); h++)
    {
        if (h->lock()) {
            // je remplis mon array de perso ou pnj qui vont mourir avec la planete
            for (auto p = this->_quidams[h->lock()->getType()].begin(); p != this->_quidams[h->lock()->getType()].end(); p++) {
                if (p->second == h->lock())
                    RuleQuidam::addToResultRequest(&result, p->second->getType(), p->first);
            }
        }

        // recuperation des ID de l'inventaire
        for (auto i = h->lock()->getInventory().begin(); i != h->lock()->getInventory().end(); i++)
            RuleItem::addToResultRequest(&result, i->first);
    }
    this->addToResultRequest(&result, id);
    return result;
}

void    RulePlanete::addToResultRequest(ResultRequest *result, int id) {
    result->_planetes[id] = this->_planetes[id];
}