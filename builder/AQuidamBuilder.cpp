/*
 * File: AQuidamBuilder.cpp                                                    *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 12:55:32 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 10:23:34 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/builder/AQuidamBuilder.hh"

AQuidamBuilder &AQuidamBuilder::ofType(OBJETS type) {
    _type = type;
    return *this; 
}

AQuidamBuilder &AQuidamBuilder::withName(const string &name) {
    _name = name;
    return *this;
}
    
AQuidamBuilder &AQuidamBuilder::onShip(int id) {
    _id_ship = id;
    return *this;
}
    
AQuidamBuilder &AQuidamBuilder::onPlanet(int id) {
    _id_planet = id;
    return *this;
}
   
AQuidamBuilder &AQuidamBuilder::fromPlanet(int id) {
    _id_planet_origin = id;
    return *this;
}
    
AQuidamBuilder &AQuidamBuilder::withGrade(int id) {
    _id_grade = id;
    return *this;
}

shared_ptr<AQuidam> AQuidamBuilder::build()
{
    validate();
    switch (_type) {
    case HEROS: return make_shared<Heros>(_name, _ap, _hp, _dp,
                                  _id_planet_origin, _id_ship, _id_planet, _id_grade);
    case PNJ: return make_shared<Pnj>(_name, _ap, _hp, _dp,
                                _id_planet_origin, _id_ship, _id_planet, _id_grade);
    case EVIL: return make_shared<Evil>(_name, _ap, _hp, _dp,
                                 _id_planet_origin, _id_ship, _id_planet, _id_grade);
    default: throw runtime_error("Type invalide pour AQuidamBuilder");
    }
}

void AQuidamBuilder::validate() {
    if (_type == NONE)          throw runtime_error("Type non défini");
    if (_name.empty())          throw runtime_error("Nom non défini");
    if (_id_ship < 0)          throw runtime_error("ID SHIP invalide");
    if (_id_planet < 0)        throw runtime_error("ID PLANET invalide");
    if (_id_planet_origin <= 0) throw runtime_error("ID PLANET ORIGIN invalide");
    if (_id_grade < 0)         throw runtime_error("ID GRADE invalide");
}

shared_ptr<AQuidam> AQuidamBuilder::fromJson(boost::json::object &item) {
    return AQuidamBuilder()
    .ofType((OBJETS)item.at("entity_type").as_int64())
    .withName(item.at("name").as_string().c_str())
    .withAp(item.at("ap").as_int64())
    .withHp(item.at("hp").as_int64())
    .withDp(item.at("dp").as_int64())
    .onPlanet(item.at("id_planet").as_int64())
    .onShip(item.at("id_ship").as_int64())
    .fromPlanet(item.at("id_planet_origin").as_int64())
    .withGrade(item.at("id_grade").as_int64())
    .build();
}