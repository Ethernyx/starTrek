/*
 * File: RuleQuidam.hh                                                         *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:54:08 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 12:24:30 pm                       *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_QUIDAM_HH_
#define RULE_QUIDAM_HH_

#include    "RuleItem.hh"
#include    "RuleGrade.hh"
#include    "../ReturnRequest.hh"

class RuleQuidam : public virtual RuleItem
{
private:
public:
    bool                                        kill(map<OBJETS, map<int, shared_ptr<AQuidam>>> &quidams);
    ResultRequest                               fillResultRequestKill(OBJETS type, int id);
    ResultRequest                               fillResultRequestGetInventory(OBJETS type, int id);
    ResultRequest                               fillResultRequestGetInfos(OBJETS type, int id);
    ResultRequest                               fillResultRequestPromote(int id_grade, OBJETS type, int id_quidam);
    void                                        fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);
    void                                        addToResultRequest(ResultRequest *result, OBJETS type, int id);

};


#endif