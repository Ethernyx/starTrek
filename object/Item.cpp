/**
* File: Item.cpp
* Project: objects
* File Created: Tuesday, 18th July 2023 3:29:05 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:52:05 pm
* Modified By: LALIN Romain
* -----
*/

#include    "../include/object/Item.hh"

Item::Item(const string name, const int stat, const EFFECT effect) :
_name(name),
_stat(stat),
_effect(effect) {
    this->_id_owner = 0;

    #ifdef DEBUG
    cout << "L'object' " << this->_name << "a été fabriqué avec succès" << endl;
    #endif
}

Item::Item(const string name, const int stat, const EFFECT effect, const int id, const OBJETS type) :
_name(name),
_stat(stat),
_effect(effect),
_id_owner(id),
_type(type) {
    #ifdef DEBUG
    cout << "L'object' " << this->_name << "a été fabriqué avec succès" << endl;
    #endif
}

Item::Item(boost::json::object item)
{
    this->_name = item.at("name").as_string().c_str();
    this->_stat = item.at("stat").as_int64();
    this->_effect = (EFFECT)item.at("effect").as_int64();
    this->_id_owner = item.at("id_owner").as_int64();
    this->_type = (OBJETS)item.at("type_owner").as_int64();

    #ifdef DEBUG
    cout << "L'object' " << this->_name << "a été fabriqué avec succès" << endl;
    #endif
}

Item::~Item()
{
    #ifdef DEBUG
    cout << "L'object' " << this->_name << "a été mis à la corbeille" << endl;
    #endif
}

EFFECT Item::getEffect() const
{
    return this->_effect;
}

string Item::getName() const
{
    return this->_name;
}

int Item::getStat() const
{
    return this->_stat;
}

int Item::getIdOwner() const
{
    return this->_id_owner;
}

OBJETS Item::getTypeOwner() const
{
    return this->_type;
}

void Item::setOwner(const int id, OBJETS type)
{
    this->_id_owner = id;
    this->_type = type;
}

void Item::setStat(const int stat)
{
    this->_stat = stat;
}

void Item::setEffect(const EFFECT effect)
{
    this->_effect = effect;
}

void Item::setName(const string name)
{
    this->_name = name;
}

void Item::setAttr(const string name, const int stat, const EFFECT effect, const int id, const OBJETS type)
{
    this->_name = name;
    this->_stat = stat;
    this->_effect = effect;
    this->_id_owner = id;
    this->_type = type;
}

boost::json::object Item::generate(int id)
{
    boost::json::object obj;
    
    obj["id"] = id;
    obj["name"] = this->_name.c_str();
    obj["stat"] = this->_stat;
    obj["effect"] = this->_effect;
    obj["id_owner"] = this->_id_owner;
    obj["type_owner"] = this->_type;

    return obj;
}
