/*
 * File: RuleMission.hh                                                        *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:58:59 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:21:42 am                         *
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
    ResultRequest                               &fillResultRequestKill(int id);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif