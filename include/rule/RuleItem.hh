/*
 * File: RuleItem.hh                                                           *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:08:07 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 6:39:08 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_ITEM_HH_
#define RULE_ITEM_HH_

#include    "../LifeDoor.hh"
#include    "../ReturnRequest.hh"

class       RuleItem : public virtual LifeDoor
{
public:
    bool    kill(map<int, Item*> &items);
    void    fillResultRequestKill(ResultRequest *result, int id);
    void    fillResultRequestGetInfos(ResultRequest *result, int id);
    void    fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);
    void    addToResultRequest(ResultRequest *result, int id);
};


#endif