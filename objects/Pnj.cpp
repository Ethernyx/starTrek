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

#include "Pnj.hh"

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

cJSON       *Pnj::generate(cJSON *node, int id) {
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