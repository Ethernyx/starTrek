/**
* File: Grade.cpp
* Project: objects
* File Created: Friday, 23rd June 2023 6:58:39 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 10:42:59 pm
* Modified By: LALIN Romain
* -----
*/

#include    "../include/object/Grade.hh"

Grade::Grade(const string nom, const int level) : _name(nom), _level(level) {
    #ifdef DEBUG
        cout << "Le grade " << this->_name << " avec un niveau d'accès de " << this->_level << "a été construit" << endl;
     #endif
}

Grade::Grade(cJSON *node) {
    this->_name = cJSON_GetObjectItem(node, "name")->valuestring;
    this->_level = cJSON_GetObjectItem(node, "level")->valueint;
    
    #ifdef DEBUG
        cout << "Le grade " << this->_name << " avec un niveau d'accès de " << this->_level << "a été construit" << endl;
    #endif
}

Grade::~Grade() {
    #ifdef DEBUG
        cout << "Suite à des coupes budgetaires, le grade de " << this->_name << " a été supprimé" << endl;
    #endif
}

string Grade::getNom() const {
    return this->_name;
}

int         Grade::getLevel() const {
    return this->_level;
}

vector<weak_ptr<AQuidam>>   &Grade::getMembre() {
    return this->_membre;
}

void                        Grade::addMembre(shared_ptr<AQuidam> &membre) {
    this->_membre.push_back(membre);

    #ifdef DEBUG
        cout << "Félicitation " << membre->getName() << " pour votre promotion vers le rang de " << this->_name << endl;
    #endif
}

bool                        Grade::deleteMembre(const string name) {
    long cpt = 0;
    for( auto &h : this->_membre) {
        auto l = h.lock();
        if(!l && name == l->getName()) {
            l->setIdGrade(0);
            this->_membre.erase(this->_membre.begin()+cpt);
            return true;
        }
        cpt++;
    }
    return false;
}

boost::json::object Grade::generate(int id) {
    boost::json::object obj;

    obj["id"] = id;
    obj["name"] = this->_name.c_str();
    obj["level"] = this->_level;
    return obj;
}

void    Grade::cleanMembres() {
    long cpt = 0;
        for( auto &h : this->_membre) {

            auto l = h.lock();
            if(!l) this->_membre.erase(this->_membre.begin() + cpt);
            cpt++;
        }
}