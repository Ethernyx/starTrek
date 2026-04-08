/*
 * File: Rule.hh                                                               *
 * Project: rule                                                               *
 * Created Date: Su Apr 2026, 4:26:02 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 12:16:56 pm                       *
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

class Rule : public RuleGrade, public RuleMission, public RulePlanete, public RuleSpaceship
{
public:
    int                                         attaqueSimple(OBJETS type_attaquant, const int id_attaquant, OBJETS type_victime,const int id_victime);
    void                                        takeItem(int item, int id, OBJETS type);
    void                                        promote(int id_grade, int id_entity, OBJETS entity_type);
    void                                        removeGrade(int id_entity, OBJETS entity_type);
    ResultRequest                               fillResultRequestKillEntities(OBJETS entity_type, int entity_id);
    ResultRequest                               fillResultRequestGetInventory(OBJETS entity_type, int entity_id);
    ResultRequest                               fillResultRequestGetInfos(OBJETS entity_type, int entity_id);
    void                                        fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);    
    bool                                        killEntities(ResultRequest &entities);
};

#endif