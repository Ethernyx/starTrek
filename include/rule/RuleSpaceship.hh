/*
 * File: RuleSpaceship.hh                                                      *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:00:46 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 12:18:10 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_SPACESHIP_HH_
#define RULE_SPACESHIP_HH_

#include    "RuleQuidam.hh"
#include    "../ReturnRequest.hh"

class RuleSpaceship : public virtual RuleQuidam
{
public:
    bool    kill(map<int, shared_ptr<Spaceship>> &spaceships);
    void    fillResultRequestKill(ResultRequest *result, int id);
    void    fillResultGetEquipage(ResultRequest *result, int id);
    void    fillResultRequestGetInventory(ResultRequest *result, int id);
    void    fillResultRequestGetInfos(ResultRequest *result, int id);
    void    fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string);
    void    fillResultRequestExchangeItem(ResultRequest *result, vector<int> &items, int id_ship, string action);
    void    addToResultRequest(ResultRequest *result, int id);
    void    simpleAttack(ResultRequest *result, int id_def, int id_att);
    void    takeItem(ResultRequest *result, int id_item, int id_ship);
    void    giveItem(ResultRequest *result, int id_item, int id_ship);

};


#endif