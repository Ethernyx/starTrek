/*
 * File: RuleQuidam.hh                                                         *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:54:08 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 9:56:36 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_QUIDAM_HH_
#define RULE_QUIDAM_HH_

#include    "RuleItem.hh"
#include    "RuleGrade.hh"
#include    "../ReturnRequest.hh"

class       RuleQuidam : public virtual RuleItem
{
public:
    bool    kill(map<OBJETS, map<int, shared_ptr<AQuidam>>> &quidams);
    void    fillResultRequestKill(ResultRequest *result, OBJETS type, int id);
    void    fillResultRequestGetInventory(ResultRequest *result, OBJETS type, int id);
    void    fillResultRequestGetInfos(ResultRequest *result, OBJETS type, int id);
    void    fillResultRequestPromote(ResultRequest *result, int id_grade, OBJETS type, int id_quidam);
    void    fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string);
    void    addToResultRequest(ResultRequest *result, OBJETS type, int id);
    void    simpleAttack(ResultRequest *result, OBJETS type_def, int id_def, OBJETS type_att, int id_att);

};


#endif