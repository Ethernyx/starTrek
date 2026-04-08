/*
 * File: RulePlanete.hh                                                        *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:59:57 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 12:24:24 pm                       *
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
    ResultRequest                               fillResultRequestKill(int id);
    ResultRequest                               fillResultRequestGetInfos(int id);
    void                                        addToResultRequest(ResultRequest *result, int id);
    ResultRequest                               fillResultGetHabitant(int id);
    void                                        fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);
};


#endif