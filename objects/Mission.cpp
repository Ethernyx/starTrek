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

#include "Mission.hh"

Mission::Mission(string objectif, string description, bool is_complete) {
    this->_name = objectif;
    this->_description = description;
    this->_isComplete = is_complete;

    #ifdef DEBUG
    cout << "La Mission " << this->_name << "a été construite" << endl;
    #endif
}

Mission::Mission(cJSON *node) {
    this->_name = cJSON_GetObjectItem(node, "name")->valuestring;
    this->_description = cJSON_GetObjectItem(node, "description")->valuestring;
    this->_isComplete = cJSON_GetObjectItem(node, "is_complete")->valueint;

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

cJSON   *Mission::generate(cJSON *node, int id) {
    cJSON_AddNumberToObject(node, "id", id);
    cJSON_AddStringToObject(node, "name", this->_name.c_str());
    cJSON_AddStringToObject(node, "description", this->_description.c_str());
    cJSON_AddNumberToObject(node, "is_complete", this->_isComplete);
    return node;
}

