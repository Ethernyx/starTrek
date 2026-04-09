/*
 * File: Rule.cpp                                                              *
 * Project: rule                                                               *
 * Created Date: Su Apr 2026, 4:29:42 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 2:21:24 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/Rule.hh"

/*
void    Rule::removeGrade(int id_entity, OBJETS entity_type) {
    switch (entity_type)
    {
    case HEROS:
        this->_grades[this->_quidams[HEROS][id_entity]->getIdGrade()]->deleteMembre(this->_quidams[HEROS][id_entity]->getName());
        break;
    case PNJ:
        this->_grades[this->_quidams[PNJ][id_entity]->getIdGrade()]->deleteMembre(this->_quidams[PNJ][id_entity]->getName());
    default:
        break;
    }
}*/

bool    Rule::killEntities(ResultRequest &entities) {
    bool isOk = true;

    /* ATTENTION : L'ordre de suppression est important  */
    if (!(isOk = RuleGrade::kill(entities._grades))) return isOk;
    if (!(isOk = RuleMission::kill(entities._missions))) return isOk;
    if (!(isOk = RuleItem::kill(entities._items))) return isOk;
    if (!(isOk = RuleQuidam::kill(entities._quidams))) return isOk;
    if (!(isOk = RuleSpaceship::kill(entities._spaceships))) return isOk;
    if (!(isOk = RulePlanete::kill(entities._planetes))) return isOk;

    return isOk;
}

void Rule::fillResultRequestKillEntities(ResultRequest *result, OBJETS entity_type, int entity_id)
{
    switch (entity_type)
    {
    case PLANETE:
        RulePlanete::fillResultRequestKill(result, entity_id);
        break;
    case HEROS:
    case PNJ:
    case EVIL:
        RuleQuidam::fillResultRequestKill(result, entity_type, entity_id);
        break;
    case MISSION:
        RuleMission::fillResultRequestKill(result, entity_id);
        break;
    case SPACESHIP:
        RuleSpaceship::fillResultRequestKill(result, entity_id);
        break;
    case GRADE:
        RuleGrade::fillResultRequestKill(result, entity_id);
        break;
    case ITEM:
        RuleItem::fillResultRequestKill(result, entity_id);
        break;
    default:
        result->_code = UNKNOWN_ENTITY;
        break;
    }
}

void   Rule::fillResultRequestGetInventory(ResultRequest *result, OBJETS entity_type, int entity_id) {;
    switch (entity_type)
    {
    case SPACESHIP:
        RuleSpaceship::fillResultRequestGetInventory(result, entity_id);
        break;
    case HEROS:
    case PNJ:
    case EVIL:
        RuleQuidam::fillResultRequestGetInventory(result, entity_type, entity_id);
        break;
    case MISSION:
    case ITEM:
    case PLANETE:
    case GRADE:
        result->_code = MISSING_INVENTORY;
        break;
    default:
        result->_code = UNKNOWN_ENTITY;
        break;
    }
}

void   Rule::fillResultRequestGetInfos(ResultRequest *result, OBJETS entity_type, int entity_id) {

    switch (entity_type)
    {
    case PLANETE:
        RulePlanete::fillResultRequestGetInfos(result, entity_id);
        break;
    case LIVING:
    case HEROS:
    case EVIL:
    case PNJ:
        RuleQuidam::fillResultRequestGetInfos(result, entity_type, entity_id);
        break;
    case MISSION:
        RuleMission::fillResultRequestGetInfos(result, entity_id);
        break;
    case SPACESHIP:
        RuleSpaceship::fillResultRequestGetInfos(result, entity_id);
        break;
    case ITEM:
        RuleItem::fillResultRequestGetInfos(result, entity_id);
        break;
    case GRADE:
        RuleGrade::fillResultRequestGetInfos(result, entity_id);
        break;
    default:
        result->_code = UNKNOWN_ENTITY;
        break;
    }
}

void    Rule::fillResultRequestAddEntities(ResultRequest *result, const map<string, int> &attr_int, const map<string, string> &attr_string) {

    if (attr_int.find("entity_type") == attr_int.end()) { result->_code = MISSING_ENTITY_TYPE_ATTRIBUT; return;}

    switch ((OBJETS) attr_int.at("entity_type"))
    {
    case PLANETE:
        RulePlanete::fillResultRequestAddEntities(result, attr_string);
        break;
    case HEROS:
    case EVIL:
    case PNJ:
        RuleQuidam::fillResultRequestAddEntities(result, attr_int, attr_string);
        break;
    case MISSION:
        RuleMission::fillResultRequestAddEntities(result, attr_int, attr_string);
        break;
    case SPACESHIP:
        RuleSpaceship::fillResultRequestAddEntities(result, attr_int, attr_string);
        break;
    case ITEM:
        RuleItem::fillResultRequestAddEntities(result, attr_int, attr_string);
        break;
    case GRADE:
        RuleGrade::fillResultRequestAddEntities(result, attr_int, attr_string);
        break;
    default:
        result->_code = UNKNOWN_ENTITY;
        break;
    }
}

void    Rule::fillResultRequestAttack(ResultRequest *result, OBJETS type_def, int id_def, OBJETS type_att, int id_att) {
    if (type_att != type_def && 
        (find(QUIDAMS.begin(), QUIDAMS.end(), type_def) != QUIDAMS.end() 
            || find(QUIDAMS.begin(), QUIDAMS.end(), type_att) != QUIDAMS.end())) { result->_code = ENTITY_OUT_RANGE; return; }

    switch (type_def) {
            case HEROS:
            case EVIL:
            case PNJ:
                RuleQuidam::simpleAttack(result, type_def, id_def, type_att, id_att);
                break;
            case SPACESHIP:
                RuleSpaceship::simpleAttack(result, id_def, id_att);
                break;
            case MISSION:
            case GRADE:
            case PLANETE:
            case ITEM:
                result->_code = UNKNOWN_ENTITY;
                break;
            default:
                result->_code = UNKNOWN_ENTITY;
                break;
        }
}

void Rule::fillResultExchangeItem(ResultRequest *result, vector<int> &id_items, OBJETS type_entity, int id_entity, string action) {
    switch (type_entity)
    {
    case SPACESHIP:
        RuleSpaceship::fillResultRequestExchangeItem(result, id_items, id_entity, action);
        break;
    case HEROS:
    case PNJ:
    case EVIL:
        RuleQuidam::fillResultRequestExchangeItem(result, id_items, type_entity, id_entity, action);
        break;
    case MISSION:
    case GRADE:
    case PLANETE:
    case ITEM:
        result->_code = MISSING_INVENTORY;
        break;
    default:
        result->_code = UNKNOWN_ENTITY;
        break;
    }
}