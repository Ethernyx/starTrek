/*
 * File: RuleMission.hh                                                        *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:58:59 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 6:41:55 pm                        *
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
    void    fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);
    void    addToResultRequest(ResultRequest *result, int id);
};


#endif