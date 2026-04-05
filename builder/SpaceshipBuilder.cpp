/*
 * File: SpaceshipBuilder.cpp                                                  *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 4:15:34 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 5:30:00 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/builder/SpaceshipBuilder.hh"

SpaceshipBuilder    &SpaceshipBuilder::withName(string name) {
    _name = name;
    return *this;
}

SpaceshipBuilder    &SpaceshipBuilder::withDescription(string desc) {
    _description = desc;
    return *this;
}

shared_ptr<Spaceship>   SpaceshipBuilder::build() {
    validate();
    return make_shared<Spaceship>(_name, _description, _ap, _hp, _dp);
}

shared_ptr<Spaceship>   SpaceshipBuilder::fromJson(boost::json::object &item) {
    return SpaceshipBuilder()
    .withName(item.at("name").as_string().c_str())
    .withDescription(item.at("description").as_string().c_str())
    .withAp(item.at("ap").as_int64())
    .withHp(item.at("hp").as_int64())
    .withDp(item.at("dp").as_int64())
    .build();
}

void    SpaceshipBuilder::validate() {
    Super::validate();
    if (_name.empty())          throw runtime_error("Nom non défini");

}