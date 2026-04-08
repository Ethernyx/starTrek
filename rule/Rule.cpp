/*
 * File: Rule.cpp                                                              *
 * Project: rule                                                               *
 * Created Date: Su Apr 2026, 4:29:42 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 6:45:01 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/Rule.hh"
/*
int Rule::attaqueSimple(OBJETS type_attaquant, const int id_attaquant, OBJETS type_victime,const int id_victime)
{
    switch (type_attaquant)
    {
        case HEROS:
        case PNJ:
        {
            auto a = type_attaquant == HEROS ? this->_quidams[HEROS][id_attaquant] : this->_quidams[PNJ][id_attaquant];
            auto v = type_victime == HEROS ? this->_quidams[HEROS][id_victime] : this->_quidams[PNJ][id_victime];

            if (a == nullptr || v == nullptr)
                return -1;
            v->setAttributs(v->getDp(), v->getHp() - (a->getAp() - v->getDp()), v->getDp()); // HP vic - (attack AP - vi DP)
            if (v->getHp() <= 0)
                return 1;
        }
            break;
        case SPACESHIP:
        {
            auto a = this->_flotte[id_attaquant];
            auto v = this->_flotte[id_victime];

            if (a == nullptr || v == nullptr)
                return -1;
            v->setAttributs(v->getDp(), v->getHp() - (a->getAp() - v->getDp()), v->getDp()); // HP vic - (attack AP - vi DP)
            if (v->getHp() <= 0)
                return 1;
        }
            break;
        default:
            break;
    }
    return 0;
}

void    Rule::takeItem(const int item, const int owner, OBJETS type) {
    switch (type)
    {
        case HEROS:
            if (this->_items[item]) this->_quidams[HEROS][owner]->addItem(this->_items[item], item);
            this->_quidams[HEROS][owner]->getInventory()[item]->setOwner(owner, type);
            break;
        case PNJ:
            this->_quidams[PNJ][owner]->addItem(this->_items[item], item);
            this->_quidams[PNJ][owner]->getInventory()[item]->setOwner(owner, type);
            break;
        case SPACESHIP:
            this->_flotte[owner]->addItem(this->_items[item], item);
            this->_flotte[owner]->getInventory()[item]->setOwner(owner, type);
            break;
        default:
            break;
    }
    // j'erase l'ancienne corespondance
    this->_tableDeCorrespondance[NONE].erase(this->_tableDeCorrespondance[NONE].find(item));
    // j'ajoute la nouvelle
    this->_tableDeCorrespondance[type][item] = owner;
}

void    Rule::promote(int id_grade, int id_entity, OBJETS entity_type) {
    this->_quidams[entity_type][id_entity]->setIdGrade(id_grade);
    this->_grades[id_grade]->addMembre(this->_quidams[HEROS][id_entity]);
}

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

void  Rule::fillResultRequestKillEntities(ResultRequest *result, OBJETS entity_type, int entity_id) {
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

void    Rule::fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string) {

    if (attr_int.find("entity_type") == attr_int.end()) { result->_code = MISSING_ENTITY_TYPE_ATTRIBUT; return;}

    switch ((OBJETS) attr_int["entity_type"])
    {
    case PLANETE:
        RulePlanete::fillResultRequestAddEntities(result, attr_int, attr_string);
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