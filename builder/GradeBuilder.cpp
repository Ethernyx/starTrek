/*
 * File: GradeBuilder.cpp                                                      *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 10:06:30 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 10:13:29 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/builder/GradeBuilder.hh"

GradeBuilder    &GradeBuilder::withName(string name) {
    _name = name;
    return *this;
}

GradeBuilder    &GradeBuilder::withLevel(int lvl) {
    _level = lvl;
    return *this;
}

shared_ptr<Grade>   GradeBuilder::build() {
    validate();
    return make_shared<Grade>(_name, _level);
}

void    GradeBuilder::validate() {
    if (_name.empty())  throw runtime_error("Nom non défini");
    if (_level < 0)     throw runtime_error("Level invalide");
}

shared_ptr<Grade>   GradeBuilder::fromJson(boost::json::object &item) {          
    return GradeBuilder()
    .withLevel(item.at("level").as_int64())
    .withName(item.at("name").as_string().c_str())
    .build();
}

