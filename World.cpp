/*
 * File: World.cpp                                                             *
 * Project: starTrek                                                           *
 * Created Date: Su Apr 2026, 3:38:27 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 3:38:05 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "include/World.hh"

map<int, shared_ptr<Spaceship>> &World::getFlotte()
{
    return this->_flotte;
}

map<int, shared_ptr<AQuidam>> &World::getPersos()
{
    return this->_quidams[HEROS];
}
map<int, shared_ptr<AQuidam>> &World::getPnjs()
{   
    return this->_quidams[PNJ];
}

map<int, shared_ptr<AQuidam>> &World::getEvils()
{   
    return this->_quidams[EVIL];
}

map<int, shared_ptr<Planete>> &World::getPlanetes()
{
    return this->_planetes;
}

map<int, shared_ptr<Mission>> &World::getMissions()
{
    return this->_missions;
}

map<int, unique_ptr<Item>> &World::getItems()
{
    return this->_items;
}

map<int, shared_ptr<Grade>> &World::getGrades()
{
    return this->_grades;
}

vector<string> World::getItems(bool isAffected)
{
    vector<string> items;

    if (!isAffected) for (auto c : this->_tableDeCorrespondance[NONE]) items.push_back(this->_items[c.first]->getName());
    if (isAffected) {
        for (auto c : this->_tableDeCorrespondance[HEROS]) items.push_back(this->_quidams[HEROS][c.second]->getInventory()[c.first]->getName());
        for (auto c : this->_tableDeCorrespondance[PNJ]) items.push_back(this->_quidams[PNJ][c.second]->getInventory()[c.first]->getName());
        for (auto c : this->_tableDeCorrespondance[SPACESHIP]) items.push_back(this->_flotte[c.second]->getInventory()[c.first]->getName());
    }
    return items;
}

shared_ptr<AQuidam> World::getPerso(const string name)
{
    for (auto p : this->_quidams[HEROS])
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    for (auto p : this->_quidams[PNJ])
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}
shared_ptr<Spaceship> World::getSpaceship(const string name)
{
    for (auto p : this->_flotte)
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}
shared_ptr<Mission> World::getMission(const string name)
{
    for (auto p : this->_missions)
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}
shared_ptr<Planete> World::getPlanete(const string name)
{
    for (auto p : this->_planetes)
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}

int World::getMaxId(OBJETS type) {
    int id = 0;
    switch (type)
    {
    case PLANETE:
        for (auto it = this->_planetes.begin(); it != this->_planetes.end(); it++) if (id < it->first) id = it->first;
        break;
    case SPACESHIP:
        for (auto it = this->_flotte.begin(); it != this->_flotte.end(); it++) if (id < it->first) id = it->first;
        break;
    case HEROS:
    case PNJ:
    case EVIL:
        for (auto it = this->_quidams[type].begin(); it != this->_quidams[type].end(); it++) if (id < it->first) id = it->first;
        break;
    case MISSION:
        for (auto it = this->_missions.begin(); it != this->_missions.end(); it++) if (id < it->first) id = it->first;
        break;
    case ITEM:
        for (auto i = this->_tableDeCorrespondance.begin(); i != this->_tableDeCorrespondance.end(); i++) for (auto it = i->second.begin(); it != i->second.end(); it++) if (id < it->first) id = it->first;
        break;
    case GRADE:
        for (auto it = this->_grades.begin(); it != this->_grades.end(); it++) if (id < it->first) id = it->first;
        break;
    default:
        break;
    }
    return id;
}

int World::getIdQuidam(shared_ptr<AQuidam> quidam) {
    for (auto p : this->_quidams[quidam->getType()]) if (p.second == quidam) return p.first;
    return 0;
}

bool    World::isQuidamExist(ResultRequest *result, OBJETS type, int id) {
    if (this->_quidams.find(type) == this->_quidams.end()) { result->_code = UNKNOWN_ENTITY ; return false; }
    if (id != 0 && this->_quidams[type].find(id) == this->_quidams[type].end()) { result->_code = (type == HEROS ? UNKNOWN_HEROS : (type == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)); return false; }
    return true;
}

bool    World::isGradeExist(ResultRequest *result, int id) {
    if (id != 0 && this->_grades.find(id) == this->_grades.end()) { result->_code = UNKNOWN_GRADE; return false; }
    return true;
}
    
bool    World::isSpaceshipExist(ResultRequest *result, int id) {
    if (id != 0 && this->_flotte.find(id) == this->_flotte.end()) { result->_code = UNKNOWN_SPACESHIP; return false; }
    return true;
}
    
bool    World::isPlaneteExist(ResultRequest *result, int id) {
    if (id != 0 && this->_planetes.find(id) == this->_planetes.end()) { result->_code = UNKNOWN_PLANET; return false; }
    return true;
}
    
bool    World::isMissionExist(ResultRequest *result, int id) {
    if (id != 0 && this->_missions.find(id) == this->_missions.end()) { result->_code = UNKNOWN_MISSION; return false; }
    return true;
}
    
bool    World::isItemExist(ResultRequest *result, int id) {
    for (auto type : this->_tableDeCorrespondance) {
        for (auto item : type.second) {
            switch (type.first)
            {
            case HEROS:
            case PNJ:
            case EVIL:
                if (!this->isQuidamExist(result, (OBJETS)type.first, item.second)) return false;
                break;
            case SPACESHIP:
                if (!this->isSpaceshipExist(result, item.second)) return false;
                break;
                
            default:
                break;
            }
            if (!this->isItemExist(result, (OBJETS)type.first, item.first)) return false;
        }
    }
    return true;
}

bool    World::isItemExist(ResultRequest *result, OBJETS type, int id) {
    if (this->_tableDeCorrespondance.find(type) == this->_tableDeCorrespondance.end()) { result->_code = UNKNOWN_ENTITY; return false; }
    if (id != 0 && this->_tableDeCorrespondance[type].find(id) == this->_tableDeCorrespondance[type].end()) { result->_code = UNKNOWN_ITEM; return false; }
    return true;
}