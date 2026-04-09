/*
 * File: LifeDoor.hh                                                           *
 * Project: include                                                            *
 * Created Date: Su Apr 2026, 3:41:26 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 10:28:52 am                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef LIFE_DOOR_HH_
#define LIFE_DOOR_HH_

#include    "World.hh"
#include    "builder/GradeBuilder.hh"
#include    "builder/ItemBuilder.hh"
#include    "builder/MissionBuilder.hh"
#include    "builder/PlaneteBuilder.hh"
#include    "builder/AQuidamBuilder.hh"
#include    "builder/SpaceshipBuilder.hh"

class LifeDoor : public World
{
private:
    void                                        edgeEffectAddItem(int id);
    void                                        edgeEffectAddQuidam(OBJETS type, int id);
public:
    bool                                        deletePerso(string const name); // --> suppression du perso via son nom
    bool                                        deletePerso(int const id); // --> surcharge suppression du perso via son ID
    int                                         addQuidam(boost::json::object &item);
    int                                         addQuidam(const map<string, int> &attr_int, const map<string, string> &attr_string);
    int                                         addPnj(const string name, const int puissance, const int sante, const int dp, const int id_planet, const int id_ship, const int id_planete_origine, const int id_grade);
    
    bool                                        deletePlanete(string const name); // -> surcharge de la suppression d'une planete par son nom
    bool                                        deletePlanete(int const id_planet); // -> surcharge de la suppression d'une planete par son ID
    int                                         addPlanet(boost::json::object &item);
    int                                         addPlanet(const map<string, string> &attr_string);

    bool                                        deleteMission(string const name);
    bool                                        deleteMission(int const id);
    int                                         addMission(boost::json::object &item);
    int                                         addMission(const map<string, int> &attr_int, const map<string, string> &attr_string);

    bool                                        deleteSpaceship(string const name); // delete spaceShip par son nom
    bool                                        deleteSpaceship(int const id_ship); // delete spaceShip par son ID
    int                                         addSpaceShip(boost::json::object &item);
    int                                         addSpaceShip(const map<string, int> &attr_int, const map<string, string> &attr_string);

    int                                         addItem(boost::json::object &item);
    int                                         addItem(const map<string, int> &attr_int, const map<string, string> &attr_string);
    void                                        removeItem(int idItem, string name, OBJETS type);
    bool                                        deleteItem(int id);

    int                                         addGrade(boost::json::object &item);
    int                                         addGrade(const map<string, int> &attr_int, const map<string, string> &attr_string);
    bool                                        deleteGrade(const int id);

};

#endif