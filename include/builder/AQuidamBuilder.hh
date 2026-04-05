/*
 * File: AQuidamBuilder.hh                                                     *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 12:11:34 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 4:43:33 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef AQUIDAM_BUILDER_HH_
#define AQUIDAM_BUILDER_HH_

#include                <string>
#include                "AttributBuilder.hh"
#include                "../object/AQuidam.hh"
#include                "../object/Heros.hh"
#include                "../object/Evil.hh"
#include                "../object/Pnj.hh"
#include                "../define.hh"

class                   AQuidamBuilder : public AttributBuilder<AQuidamBuilder> {
    private:
    OBJETS              _type = NONE;
    string              _name = "";
    int                 _id_ship = 0;
    int                 _id_planet = 0;
    int                 _id_planet_origin = 0;
    int                 _id_grade = 0;

    void                validate();

    public:
    AQuidamBuilder      &ofType(OBJETS type);
    AQuidamBuilder      &withName(const string &name);
    AQuidamBuilder      &onShip(int id);
    AQuidamBuilder      &onPlanet(int id);
    AQuidamBuilder      &fromPlanet(int id);
    AQuidamBuilder      &withGrade(int id);
    shared_ptr<AQuidam> build();
    static shared_ptr<AQuidam> fromJson(boost::json::object &item);

};

#endif
