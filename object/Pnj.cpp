/**
* File: Pnj.cpp
* Project: objects
* File Created: Tuesday, 18th July 2023 3:29:05 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 10:25:38 pm
* Modified By: LALIN Romain
* -----
*/

#include "../include/object/Pnj.hh"

Pnj::Pnj(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin) : AQuidam(nom, forceAttaque, sante, dp, id_planet_origin) {
    this->_type = PNJ;
    #ifdef DEBUG
    cout << "Le Pnj " << this->_name << " est arrivé dans cet univers" << endl;
    #endif
}

Pnj::Pnj(string const nom, int const forceAttaque, int const sante, int const dp, const int id_planet_origin, const int id_ship, const int id_planet, const int id_grade) : AQuidam(nom, forceAttaque, sante, dp, id_planet_origin, id_ship, id_planet, id_grade) {
    this->_type = PNJ;

    #ifdef DEBUG
    cout << "Le Pnj " << this->_name << " est arrivé dans cet univers" << endl;
    #endif
}

Pnj::Pnj(cJSON *node) : AQuidam(node) {
    this->_type = PNJ;

    #ifdef DEBUG
    cout << "Le Pnj " << this->_name << " est arrivé dans cet univers" << endl;
    #endif
}

Pnj::~Pnj() {
    #ifdef DEBUG
    cout << "Le Pnj " << this->_name << " est mort. Tant pis pour lui." << endl;
    #endif
}

boost::json::object Pnj::generate(int id) {
    boost::json::object obj;
    
    obj["id"] = id;
    obj["name"] = this->_name.c_str();
    obj["ap"] = this->_ap;
    obj["hp"] = this->_hp;
    obj["dp"] = this->_dp;
    obj["id_planet"] = this->_id_planet;
    obj["id_ship"] = this->_id_ship;
    obj["id_planet_origin"] = this->_id_planet_origin;
    obj["id_grade"] = this->_id_grade;
    return obj;
}