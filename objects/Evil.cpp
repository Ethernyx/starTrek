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

#include    "Evil.hh"

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

Evil::Evil(cJSON *node) : AQuidam(node) {
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

cJSON       *Evil::generate(cJSON *node, int id) {
    cJSON_AddNumberToObject(node, "id", id);
    cJSON_AddStringToObject(node, "name", this->_name.c_str());
    cJSON_AddNumberToObject(node, "ap", this->_ap);
    cJSON_AddNumberToObject(node, "hp", this->_hp);
    cJSON_AddNumberToObject(node, "dp", this->_dp);
    cJSON_AddNumberToObject(node, "id_planet", this->_id_planet);
    cJSON_AddNumberToObject(node, "id_ship", this->_id_ship);
    cJSON_AddNumberToObject(node, "id_planet_origin", this->_id_planet_origin);
    cJSON_AddNumberToObject(node, "id_grade", this->_id_grade);
    return node;
}
