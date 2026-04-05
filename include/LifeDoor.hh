/*
 * File: LifeDoor.hh                                                           *
 * Project: include                                                            *
 * Created Date: Su Apr 2026, 3:41:26 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 3:53:10 pm                           *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef LIFE_DOOR_HH_
#define LIFE_DOOR_HH_

#include    "World.hh"
#include    "builder/AQuidamBuilder.hh"
#include    "builder/GradeBuilder.hh"
#include    "builder/ItemBuilder.hh"
#include    "builder/MissionBuilder.hh"
#include    "builder/PlaneteBuilder.hh"
#include    "builder/SpaceshipBuilder.hh"

class LifeDoor : public World
{
public:
    bool                                        deletePerso(string const name); // --> suppression du perso via son nom
    bool                                        deletePerso(int const id); // --> surcharge suppression du perso via son ID
    int                                         addQuidam(boost::json::object &item);
    int                                         addPnj(const string name, const int puissance, const int sante, const int dp, const int id_planet, const int id_ship, const int id_planete_origine, const int id_grade);
    
    bool                                        deletePlanete(string const name); // -> surcharge de la suppression d'une planete par son nom
    bool                                        deletePlanete(int const id_planet); // -> surcharge de la suppression d'une planete par son ID
    int                                         addPlanet(boost::json::object &item);

    bool                                        deleteMission(string const name);
    bool                                        deleteMission(int const id);
    int                                         addMission(boost::json::object &item);

    bool                                        deleteSpaceship(string const name); // delete spaceShip par son nom
    bool                                        deleteSpaceship(int const id_ship); // delete spaceShip par son ID
    int                                         addSpaceShip(boost::json::object &item);

    int                                         addItem(boost::json::object &item);
    void                                        removeItem(int idItem, string name, OBJETS type);
    void                                        deleteItem(int id);

    int                                         addGrade(boost::json::object &item);
    bool                                        deleteGrade(const int id);

};

#endif