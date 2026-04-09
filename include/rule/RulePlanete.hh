/*
 * File: RulePlanete.hh                                                        *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:59:57 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 10:33:18 am                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_PLANETE_HH_
#define RULE_PLANETE_HH_

#include    "RuleQuidam.hh"
#include    "../ReturnRequest.hh"

class       RulePlanete : public virtual RuleQuidam
{
public:
    bool    kill(map<int, shared_ptr<Planete>> &planetes);
    void    fillResultRequestKill(ResultRequest *result, int id);
    void    fillResultRequestGetInfos(ResultRequest *result, int id);
    void    fillResultGetHabitant(ResultRequest *result, int id);
    void    fillResultRequestAddEntities(ResultRequest *result, const map<string, string> &attr_string);
    void    addToResultRequest(ResultRequest *result, int id);

};


#endif