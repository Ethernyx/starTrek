/**
* File: Planete.cpp
* Project: objects
* File Created: Tuesday, 18th July 2023 3:29:05 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:54:06 pm
* Modified By: LALIN Romain
* -----
*/

#include "../include/object/Planete.hh"

Planete::Planete(string nom, string description) {
    this->_name = nom;
    this->_description = description;

    #ifdef DEBUG
    cout << "La Planête " << this->_name << " est aparue dans cet univers" << endl;
    #endif
}

Planete::Planete(cJSON *node) {
    this->_name = cJSON_GetObjectItem(node, "name")->valuestring;
    this->_description = cJSON_GetObjectItem(node, "description")->valuestring;

    #ifdef DEBUG
    cout << "La Planête " << this->_name << " est aparue dans cet univers" << endl;
    #endif
}

Planete::~Planete() {
    #ifdef DEBUG
    cout << "La Planête " << this->_name << " a soudainement disparue des radars" << endl;
    #endif
}



bool Planete::deleteHabitant(const string name)
{
    long cpt = 0;
    for( auto &h : this->_habitants) {
        auto l = h.lock();
        if(!l && name == l->getName()) {
            l->setIdPlanet(0);
            this->_habitants.erase(this->_habitants.begin()+cpt);
            return true;
        }
        cpt++;
    }
    return false;
}

string Planete::getName() const {
    return this->_name;
}

string Planete::getDescription() const {
    return this->_description;
}


void Planete::setHabitant(shared_ptr<AQuidam> &habitant) {
    this->_habitants.push_back(habitant);
}

vector<weak_ptr<AQuidam>> &Planete::getHabitants() {
    return this->_habitants;
}

bool Planete::isExists(const std::string namePerso) {
    for(auto p:this->_habitants) {
        auto l = p.lock();
        if(!l) this->cleanHabitants();
        else if(namePerso == l->getName()) return true;
    }
    return false;
}
void Planete::cleanHabitants(){
    long cpt = 0;
    for( auto &h : this->_habitants) {
        auto l = h.lock();
        if(!l) this->_habitants.erase(this->_habitants.begin()+cpt);
        cpt++;
    }
}

boost::json::object Planete::generate(int id) {
    boost::json::object obj;

    obj["id"] = id;
    obj["name"] = this->_name.c_str();
    obj["description"] = this->_description.c_str();
    return obj;

}
