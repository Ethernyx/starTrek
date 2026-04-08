/*
 * File: RuleItem.hh                                                           *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 2:08:07 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 12:24:12 pm                       *
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
    ResultRequest                               fillResultRequestKill(int id);
    ResultRequest                               fillResultRequestGetInfos(int id);
    void                                        fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif