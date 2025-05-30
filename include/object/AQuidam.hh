/**
 * File: AQuidam.hh
 * Project: objects
 * File Created: Saturday', 29th July 2023 10:26:15 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Saturday', 29th July 2023 10:26:15 pm
 * Modified by: LALIN Romain
 * -----
*/

#ifndef                         AQUIDAM_HH_
#define                         AQUIDAM_HH_

#include                        <string>
#include                        <memory>
#include                        <map>
#include                        "Item.hh"
#include                        "Attribut.hh"
#include                        "Inventory.hh"
#include                        "../define.hh"

using namespace                 std;

class                           AQuidam : public Attribut,  public Inventory
{
protected:
    int                         _id_ship;
    int                         _id_planet;
    int                         _id_planet_origin;
    int                         _id_grade;
    string                      _name;
    OBJETS                      _type; //type de perso -- Pnj || Personnage
public:
                                AQuidam(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin);
                                AQuidam(string const nom, int const forceAttaque, int const sante, const int dp, int id_planet_origin, int id_ship, int id_planet, int id_grade);
                                AQuidam(boost::json::object item);
    virtual                     ~AQuidam();

    int                         getIdShip() const;
    int                         getIdPlanet() const;
    int                         getIdPlanetOrigin() const;
    int                         getIdGrade() const;
    OBJETS                      getType() const;
    string                      getName() const;

    //setters
    void                        setName(string nom);
    void                        setIdShip(int id_ship);
    void                        setIdPlanet(int id_planet);
    void                        setIdPlanetOrigin(int id_planet_origin);
    void                        setIdGrade(int id_grade);
    void                        setType(OBJETS type);
    void                        addItem(unique_ptr<Item> &, int id);

    virtual boost::json::object generate(int id) = 0;

};

#endif