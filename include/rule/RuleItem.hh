/*
 * File: RuleItem.hh                                                           *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:08:07 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 9:56:18 am                         *
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
    void    fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string);
    void    addToResultRequest(ResultRequest *result, int id);
};


#endif