/*
 * File: Itembuilder.cpp                                                       *
 * Project: builder                                                            *
 * Created Date: Su Apr 2026, 11:34:23 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 11:52:06 am                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/builder/ItemBuilder.hh"

ItemBuilder &ItemBuilder::withName(const string name) {
    _name = name;
    return *this;
}

ItemBuilder &ItemBuilder::withStat(const int stat) {
    _stat = stat;
    return *this;
}

ItemBuilder &ItemBuilder::withEffect(const EFFECT effect) {
    _effect = effect;
    return *this;
}

ItemBuilder &ItemBuilder::withOwner(const int id_owner) {
    _id_owner = id_owner;
    return *this;
}

ItemBuilder &ItemBuilder::withType(const OBJETS type) {
    _type = type;
    return *this;
}

unique_ptr<Item>    ItemBuilder::build() {
    validate();
    return make_unique<Item>(_name, _stat, _effect, _id_owner, _type);
}

unique_ptr<Item>    ItemBuilder::fromJson(boost::json::object &item) {
    return ItemBuilder()
        .withName(item.at("name").as_string().c_str())
        .withStat(item.at("stat").as_int64())
        .withEffect((EFFECT)item.at("effect").as_int64())
        .withOwner(item.at("id_owner").as_int64())
        .withType((OBJETS)item.at("type_owner").as_int64())
        .build();                 
}

void    ItemBuilder::validate() {
    if (_name.empty())                      throw runtime_error("Nom non défini");
    if (_stat == 0)                         throw runtime_error("Stat non défini");
    if (_effect == 0)                       throw runtime_error("Effect non défini");
    if (_id_owner == 0 && _type != NONE)    throw runtime_error("ID Owner non défini");
    if (_id_owner != 0 && _type == NONE)    throw runtime_error("Type Owner non défini");
}