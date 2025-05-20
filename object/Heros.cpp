/**
* File: Heros.cpp
* Project: objects
* File Created: Tuesday, 18th July 2023 3:29:05 pm
* Author: LALIN Romain 
* -----
* Last Modified: Thursday, 27th July 2023 10:48:05 pm
* Modified By: LALIN Romain
* -----
*/

#include    "../include/object/Heros.hh"

Heros::Heros(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin) : AQuidam(nom, forceAttaque, sante, dp, id_planet_origin) {
    this->_type = HEROS;

    #ifdef DEBUG
    cout << "Le Heros " << this->_name << " est arrivé dans cet univers" << endl;
    #endif
}

Heros::Heros(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin, int id_ship, int id_planet, int const id_grade) : AQuidam(nom, forceAttaque, sante, dp, id_planet_origin, id_ship, id_planet, id_grade) {
    this->_type = HEROS;
    
    #ifdef DEBUG
    cout << "Le Heros " << this->_name << u8" est arrivé dans cet univers" << endl;
    #endif
}

Heros::Heros(cJSON *node) : AQuidam(node) {
    this->_type = HEROS;
        #ifdef DEBUG
    cout << "Le Heros " << this->_name << u8" est arrivé dans cet univers" << endl;
    #endif
}

Heros::~Heros() {
#ifdef DEBUG
    cout << "Le Heros " << this->_name << " est mort. Tant pis pour lui." << endl;
#endif
}

boost::json::object Heros::generate(int id) {
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

