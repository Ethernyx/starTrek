/*
 * File: RuleMission.hh                                                        *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:58:59 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 2:22:57 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_MISSION_HH_
#define RULE_MISSION_HH_

#include    "../LifeDoor.hh"
#include    "../ReturnRequest.hh"

class RuleMission : public virtual LifeDoor
{
private:
public:
    bool                                        kill(map<int, shared_ptr<Mission>> &missions);
    ResultRequest                               fillResultRequestKill(int id);
    ResultRequest                               fillResultRequestGetInfos(int id);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif