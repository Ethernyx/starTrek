/*
 * File: MissionBuilder.cpp                                                    *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 10:34:28 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 10:43:48 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/builder/MissionBuilder.hh"

MissionBuilder    &MissionBuilder::withName(string name) {
    _name = name;
    return *this;
}

MissionBuilder    &MissionBuilder::withDescription(string desc) {
    _description = desc;
    return *this;
}

MissionBuilder  &MissionBuilder::isComplete() {
    _isComplete = true;
    return *this;
}

shared_ptr<Mission>   MissionBuilder::build() {
    validate();
    return make_shared<Mission>(_name, _description, _isComplete);
}

void    MissionBuilder::validate() {
    if (_name.empty())  throw runtime_error("Nom non défini");
}

shared_ptr<Mission> MissionBuilder::fromJson(boost::json::object &item) {
    MissionBuilder obj = MissionBuilder()
                            .withDescription(item.at("description").as_string().c_str())
                            .withName(item.at("name").as_string().c_str());
                            
    if (item.at("is_complete").as_bool()) obj.isComplete();
    return obj.build();
}