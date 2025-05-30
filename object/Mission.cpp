/**
* File: Mission.cpp
* Project: objects
* File Created: Tuesday, 18th July 2023 3:29:05 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:41:12 pm
* Modified By: LALIN Romain
* -----
*/

#include "../include/object/Mission.hh"

Mission::Mission(string objectif, string description, bool is_complete) {
    this->_name = objectif;
    this->_description = description;
    this->_isComplete = is_complete;

    #ifdef DEBUG
    cout << "La Mission " << this->_name << "a été construite" << endl;
    #endif
}

Mission::Mission(boost::json::object item) {
    this->_name = item.at("name").as_string().c_str();
    this->_description = item.at("description").as_string().c_str();
    this->_isComplete = item.at("is_complete").as_bool();

    #ifdef DEBUG
    cout << "La Mission " << this->_name << "a été construite" << endl;
    #endif
}

Mission::~Mission() {
    #ifdef DEBUG
    cout << "La Mission " << this->_name << "a été detruite" << endl;
    #endif
}

string Mission::getName() const {
    return this->_name;
}

string Mission::getDescription() const {
    return this->_description;
}

bool Mission::getIsComplete() {
    return this->_isComplete;
}

void Mission::setIsCompleted(bool is) {
    this->_isComplete = is;
}

boost::json::object Mission::generate(int id) {
    boost::json::object obj;

    obj["id"] = id;
    obj["name"] = this->_name.c_str();
    obj["description"] = this->_description.c_str();
    obj["is_complete"] = this->_isComplete;
    return obj;
}

