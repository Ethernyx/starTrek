/**
* File: Spaceship.cpp
* Project: objects
* File Created: Tuesday, 18th July 2023 3:29:05 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:56:06 pm
* Modified By: LALIN Romain
* -----
*/

#include "../include/object/Spaceship.hh"

Spaceship::Spaceship(string nom, string description, int ap, int hp, int dp): Attribut(ap, hp, dp), Inventory(5) {
    this->_name = nom;
    this->_description = description;

#ifdef DEBUG
    cout << "Le Vaisseau " << this->_name << " a été construit" << endl;
#endif
}
Spaceship::Spaceship(cJSON *node): Attribut(node), Inventory(5) {
    this->_name = cJSON_GetObjectItem(node, "name")->valuestring;
    this->_description = cJSON_GetObjectItem(node, "description")->valuestring;
#ifdef DEBUG
    cout << "Le Vaisseau " << this->_name << " a été construit" << endl;
#endif
}

Spaceship::~Spaceship() {
    #ifdef DEBUG
    cout << "Le Vaisseau " << this->_name << " a été complètement detruit" << endl;
    #endif
}

//ajout de l'adresse d'un Heros au vector pour
// acceder à la modification des elements du vector

void Spaceship::addEquipage(shared_ptr<AQuidam> &p) {
    this->_equipage.push_back(p);
}

bool Spaceship::deleteEquipage(const string name)
{
    long cpt = 0;
    for( auto &h : this->_equipage) {
        auto l = h.lock();
        if(!l && name == l->getName()) {
            l->setIdShip(0);
            this->_equipage.erase(this->_equipage.begin()+cpt);
            return true;
        }
        cpt++;
    }
    return false;
}

bool Spaceship::isExists(const std::string namePerso) {
    for(auto p:this->_equipage) {
        auto l = p.lock();
        if(!l) {
            this->cleanEquipage();
            continue;
        }
        if(namePerso == l->getName()) return true;
    }
    return false;
}
vector<weak_ptr<AQuidam>> &Spaceship::getEquipage() {
    return this->_equipage;
}

string Spaceship::getName() {
    return this->_name;
}
string Spaceship::getDescription() {
    return this->_description;
}

void Spaceship::set_name(string nom) {
    this->_name = nom;
}

void Spaceship::cleanEquipage(){
    long cpt = 0;
    for( auto &h : this->_equipage) {

        auto l = h.lock();
        if(!l) this->_equipage.erase(this->_equipage.begin() + cpt);
        cpt++;
    }
}

boost::json::object Spaceship::generate(int id) {
    boost::json::object obj;

    obj["id"] = id;
    obj["name"] = this->_name.c_str();
    obj["description"] = this->_description.c_str();
    obj["ap"] = this->_ap;
    obj["dp"] = this->_dp;
    obj["hp"] = this->_hp;
    return obj;

}


