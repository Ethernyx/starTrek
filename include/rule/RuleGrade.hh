/*
 * File: RuleGrade.hh                                                          *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:57:49 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:25:14 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_GRADE_HH_
#define RULE_GRADE_HH_

#include    "../LifeDoor.hh"
#include    "../ReturnRequest.hh"

class RuleGrade : public virtual LifeDoor
{
private:
public:
    bool                                        kill(map<int, shared_ptr<Grade>> &grades);
    ResultRequest                               &fillResultRequestKill(int id);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif