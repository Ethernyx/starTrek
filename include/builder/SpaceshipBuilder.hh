/*
 * File: SpaceshipBuilder.hh                                                   *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 4:15:52 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 5:34:34 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef SPACESHIP_BUILDER_HH
#define SPACESHIP_BUILDER_HH

#include                            <string>
#include                            <memory>
#include                            "../object/Spaceship.hh"
#include                            "AttributBuilder.hh"
#include                            "../define.hh"

class SpaceshipBuilder : public AttributBuilder<SpaceshipBuilder> {
private:
    using                           Super = AttributBuilder<SpaceshipBuilder>;
    string                          _name;
    string                          _description;
    void                            validate();
public:
    SpaceshipBuilder                &withName(string name);
    SpaceshipBuilder                &withDescription(string desc);
    shared_ptr<Spaceship>           build();
    static shared_ptr<Spaceship>    fromJson(boost::json::object &item);
};

#endif
