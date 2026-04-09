/*
 * File: RuleSpaceship.hh                                                      *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:00:46 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 9:56:43 am                         *
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
    void    addToResultRequest(ResultRequest *result, int id);
    void    simpleAttack(ResultRequest *result, int id_def, int id_att);
};


#endif