/*
 * File: RuleSpaceship.hh                                                      *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:00:46 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 2:23:57 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_SPACESHIP_HH_
#define RULE_SPACESHIP_HH_

#include    "RuleQuidam.hh"
#include    "../ReturnRequest.hh"

class RuleSpaceship : public virtual RuleQuidam
{
private:
public:
    bool                                        kill(map<int, shared_ptr<Spaceship>> &spaceships);
    ResultRequest                               fillResultRequestKill(int id);
    ResultRequest                               fillResultGetEquipage(int id);
    ResultRequest                               fillResultRequestGetInventory(int id);
    ResultRequest                               fillResultRequestGetInfos(int id);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif