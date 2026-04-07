/*
 * File: Rule.cpp                                                              *
 * Project: rule                                                               *
 * Created Date: Su Apr 2026, 4:29:42 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 2:28:26 pm                          *
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

ResultRequest  Rule::fillResultRequestKillEntities(OBJETS entity_type, int entity_id) {
    ResultRequest   result;
    switch (entity_type)
    {
    case PLANETE:
        return RulePlanete::fillResultRequestKill(entity_id);
        break;
    case HEROS:
    case PNJ:
    case EVIL:
        return RuleQuidam::fillResultRequestKill(entity_type, entity_id);
        break;
    case MISSION:
        return RuleMission::fillResultRequestKill(entity_id);
        break;
    case SPACESHIP:
        return RuleSpaceship::fillResultRequestKill(entity_id);
        break;
    case GRADE:
        return RuleGrade::fillResultRequestKill(entity_id);
        break;
    case ITEM:
        return RuleItem::fillResultRequestKill(entity_id);
        break;
    default:
        result._code = UNKNOWN_ENTITY;
        return result;
        break;
    }
    result._code = UNKNOWN_ENTITY;
    return result;
}

ResultRequest   Rule::fillResultRequestGetInventory(OBJETS entity_type, int entity_id) {
    ResultRequest   result;

    switch (entity_type)
    {
    case SPACESHIP:
        result = RuleSpaceship::fillResultRequestGetInventory(entity_id);
        break;
    case HEROS:
    case PNJ:
    case EVIL:
        result = RuleQuidam::fillResultRequestGetInventory(entity_type, entity_id);
        break;
    case MISSION:
    case ITEM:
    case PLANETE:
    case GRADE:
        result._code = MISSING_INVENTORY;
        break;
    default:
        result._code = UNKNOWN_ENTITY;
        break;
    }
    return result;
}

ResultRequest   Rule::fillResultRequestGetInfos(OBJETS entity_type, int entity_id) {
    ResultRequest   result;

    switch (entity_type)
    {
    case PLANETE:
        result = RulePlanete::fillResultRequestGetInfos(entity_id);
        break;
    case LIVING:
    case HEROS:
    case EVIL:
    case PNJ:
        result = RuleQuidam::fillResultRequestGetInfos(entity_type, entity_id);
        break;
    case MISSION:
        result = RuleMission::fillResultRequestGetInfos(entity_id);
        break;
    case SPACESHIP:
        result = RuleSpaceship::fillResultRequestGetInfos(entity_id);
        break;
    case ITEM:
        result = RuleItem::fillResultRequestGetInfos(entity_id);
        break;
    case GRADE:
        result = RuleGrade::fillResultRequestGetInfos(entity_id);
        break;
    default:
        result._code = UNKNOWN_ENTITY;
        break;
    }
    return result;
}