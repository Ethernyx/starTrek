/**
 * File: AQuidam.cpp
 * Project: objects
 * File Created: Saturday', 29th July 2023 10:35:22 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Saturday', 29th July 2023 10:35:22 pm
 * Modified by: LALIN Romain
 * -----
*/

#include    "AQuidam.hh"

AQuidam::AQuidam(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin): Attribut(forceAttaque, sante, dp), Inventory(5) {
    this->_name = nom;
    this->_id_ship = 0;
    this->_id_planet = 0;
    this->_id_grade = 0;
    this->_id_planet_origin = id_planet_origin;
    this->_type = HEROS;

    #ifdef DEBUG
    cout << "Le Personnage " << this->_name << " est arrivé dans cet univers" << endl;
    #endif
}

AQuidam::AQuidam(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin, int id_ship, int id_planet, int const id_grade): Attribut(forceAttaque, sante, dp), Inventory(5) {
    this->_name = nom;
    this->_id_planet_origin = id_planet_origin;
    this->_id_ship = id_ship;
    this->_id_planet = id_planet;
    this->_id_grade = id_grade;
    this->_type = HEROS;
    
    #ifdef DEBUG
    cout << "Le Personnage " << this->_name << u8" est arrivé dans cet univers" << endl;
    #endif
}

AQuidam::AQuidam(cJSON *node) : Attribut(node), Inventory(5) {
    this->_name = cJSON_GetObjectItem(node, "name")->valuestring;
    this->_id_planet_origin = cJSON_GetObjectItem(node, "id_planet_origin")->valueint;
    this->_id_ship = cJSON_GetObjectItem(node, "id_ship")->valueint;
    this->_id_planet = cJSON_GetObjectItem(node, "id_planet")->valueint;
    this->_id_grade = cJSON_GetObjectItem(node, "id_grade")->valueint;
    this->_type = HEROS;
        #ifdef DEBUG
    cout << "Le Personnage " << this->_name << u8" est arrivé dans cet univers" << endl;
    #endif
}

AQuidam::~AQuidam() {
#ifdef DEBUG
    cout << "Le personnage " << this->_name << " est mort. Tant pis pour lui." << endl;
#endif
}

//SETTERS
void AQuidam::setName(string const nom)  {
    this->_name = nom;
}

// GETTERS
string AQuidam::getName() const {
    return this->_name;
}

int AQuidam::getIdShip() const {
    return this->_id_ship;
}

int AQuidam::getIdPlanet() const {
    return this->_id_planet;
}

int AQuidam::getIdPlanetOrigin() const {
    return this->_id_planet_origin;
}

int AQuidam::getIdGrade() const {
    return this->_id_grade;
}

//retourne HEROS ||PNJ
int AQuidam::getType() const {
    return this->_type;
}


void AQuidam::setIdShip(int id_ship) {
    this->_id_ship = id_ship;
}

void AQuidam::setIdPlanet(int id_planet) {
    this->_id_planet = id_planet;
}

void AQuidam::setIdPlanetOrigin(int id_planet_origin) {
    this->_id_planet_origin = id_planet_origin;
}

void AQuidam::setIdGrade(int id_grade) {
    this->_id_grade = id_grade;
}

void AQuidam::setType(int type) {
    this->_type = type;
}

void    AQuidam::addItem(unique_ptr<Item> &item, int id) {
    if (this->_inventory.size() <= this->_maxItem && item) this->_inventory.insert(make_pair(id, std::move(item)));
}