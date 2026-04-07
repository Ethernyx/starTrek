/*
 * File: RuleQuidam.hh                                                         *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:54:08 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:23:35 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_QUIDAM_HH_
#define RULE_QUIDAM_HH_

#include    "RuleItem.hh"
#include    "../ReturnRequest.hh"

class RuleQuidam : public virtual RuleItem
{
private:
public:
    bool                                        kill(map<OBJETS, map<int, shared_ptr<AQuidam>>> &quidams);
    ResultRequest                               &fillResultRequestKill(OBJETS type, int id);
    void                                        addToResultRequest(ResultRequest *result, OBJETS type, int id);
};


#endif