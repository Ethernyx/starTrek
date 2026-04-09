/*
 * File: Rule.hh                                                               *
 * Project: rule                                                               *
 * Created Date: Su Apr 2026, 4:26:02 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 2:22:41 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_HH_
#define RULE_HH_

#include    "RuleGrade.hh"
#include    "RuleMission.hh"
#include    "RulePlanete.hh"
#include    "RuleQuidam.hh"
#include    "RuleSpaceship.hh"
#include    "RuleItem.hh"

class       Rule : public RuleGrade, public RuleMission, public RulePlanete, public RuleSpaceship
{
public:
    void                                        removeGrade(int id_entity, OBJETS entity_type);
    void    fillResultRequestKillEntities(ResultRequest *result, OBJETS entity_type, int entity_id);
    void    fillResultRequestGetInventory(ResultRequest *result,OBJETS entity_type, int entity_id);
    void    fillResultRequestGetInfos(ResultRequest *result,OBJETS entity_type, int entity_id);
    void    fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string);    
    void    fillResultRequestAttack(ResultRequest *result, OBJETS type_def, int id_def, OBJETS type_att, int id_att);
    bool    killEntities(ResultRequest &entities);
    void    fillResultExchangeItem(ResultRequest *result, vector<int> &id_items, OBJETS type_entity, int id_entity, string action);
    
};

#endif