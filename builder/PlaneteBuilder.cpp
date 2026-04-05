/*
 * File: PlaneteBuilder.cpp                                                    *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 10:20:57 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 10:22:48 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/builder/PlaneteBuilder.hh"

PlaneteBuilder    &PlaneteBuilder::withName(string name) {
    _name = name;
    return *this;
}

PlaneteBuilder    &PlaneteBuilder::withDescription(string desc) {
    _description = desc;
    return *this;
}

shared_ptr<Planete>   PlaneteBuilder::build() {
    validate();
    return make_shared<Planete>(_name, _description);
}

void    PlaneteBuilder::validate() {
    if (_name.empty())  throw runtime_error("Nom non défini");
}

shared_ptr<Planete>   PlaneteBuilder::fromJson(boost::json::object &item) {          
    return PlaneteBuilder()
    .withDescription(item.at("description").as_string().c_str())
    .withName(item.at("name").as_string().c_str())
    .build();
}