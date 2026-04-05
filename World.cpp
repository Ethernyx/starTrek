/*
 * File: World.cpp                                                             *
 * Project: starTrek                                                           *
 * Created Date: Su Apr 2026, 3:38:27 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 3:55:21 pm                           *
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