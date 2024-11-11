/**
 * File: Evil.hh
 * Project: objects
 * File Created: Sunday', 30th July 2023 4:26:55 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Sunday', 30th July 2023 4:26:55 pm
 * Modified by: LALIN Romain
 * -----
*/

#ifndef                         EVIL_HH_
#define                         EVIL_HH_

#include                        "AQuidam.hh"

class                           Evil : public AQuidam
{
private:
public:
                                Evil(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin);
                                Evil(string const nom, int const forceAttaque, int const sante, const int dp, int id_planet_origin, int id_ship, int id_planet, int id_grade);
                                Evil(cJSON *node);

    virtual                     ~Evil();

    cJSON                       *generate(cJSON *node, int id);
};

#endif