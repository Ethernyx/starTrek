/**
 * File: Evil.cpp
 * Project: objects
 * File Created: Sunday', 30th July 2023 4:29:04 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Sunday', 30th July 2023 4:29:04 pm
 * Modified by: LALIN Romain
 * -----
*/

#include    "../include/object/Evil.hh"

Evil::Evil(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin) : AQuidam(nom, forceAttaque, sante, dp, id_planet_origin) {
    this->_type = EVIL;

    #ifdef DEBUG
    cout << "Le Méchant " << this->_name << " est arrivé dans cet univers" << endl;
    #endif
}

Evil::Evil(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin, int id_ship, int id_planet, int const id_grade) : AQuidam(nom, forceAttaque, sante, dp, id_planet_origin, id_ship, id_planet, id_grade) {
    this->_type = EVIL;
    
    #ifdef DEBUG
    cout << "Le Méchant " << this->_name << u8" est arrivé dans cet univers" << endl;
    #endif
}

Evil::Evil(boost::json::object item) : AQuidam(item) {
    this->_type = EVIL;
        #ifdef DEBUG
    cout << "Le Méchant " << this->_name << u8" est arrivé dans cet univers" << endl;
    #endif
}

Evil::~Evil() {
#ifdef DEBUG
    cout << "Le Méchant " << this->_name << " est mort. Tant pis pour lui." << endl;
#endif
}

boost::json::object Evil::generate(int id) {
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
