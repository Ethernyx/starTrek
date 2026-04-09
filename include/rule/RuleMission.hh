/*
 * File: RuleMission.hh                                                        *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:58:59 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 9:56:23 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_MISSION_HH_
#define RULE_MISSION_HH_

#include    "../LifeDoor.hh"
#include    "../ReturnRequest.hh"

class       RuleMission : public virtual LifeDoor
{
public:
    bool    kill(map<int, shared_ptr<Mission>> &missions);
    void    fillResultRequestKill(ResultRequest *result, int id);
    void    fillResultRequestGetInfos(ResultRequest *result, int id);
    void    fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string);
    void    addToResultRequest(ResultRequest *result, int id);
};


#endif