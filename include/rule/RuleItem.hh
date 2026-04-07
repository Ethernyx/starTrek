/*
 * File: RuleItem.hh                                                           *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:08:07 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 11:21:23 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_ITEM_HH_
#define RULE_ITEM_HH_

#include    "../LifeDoor.hh"
#include    "../ReturnRequest.hh"

class RuleItem : public virtual LifeDoor
{
private:
public:
    bool                                        kill(map<int, Item*> &items);
    ResultRequest                               &fillResultRequestKill(int id);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif