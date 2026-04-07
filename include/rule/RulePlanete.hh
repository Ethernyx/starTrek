/*
 * File: RulePlanete.hh                                                        *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:59:57 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:23:24 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_PLANETE_HH_
#define RULE_PLANETE_HH_

#include    "RuleQuidam.hh"
#include    "../ReturnRequest.hh"

class RulePlanete : public virtual RuleQuidam
{
private:
public:
    bool                                        kill(map<int, shared_ptr<Planete>> &planetes);
    ResultRequest                               &fillResultRequestKill(int id);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif