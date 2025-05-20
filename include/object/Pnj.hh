/**
 * File: Pnj.hh
 * Project: objects
 * File Created: Friday', 28th July 2023 2:33:51 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Friday', 28th July 2023 2:33:51 pm
 * Modified by: LALIN Romain
 * -----
*/

#ifndef     PNJ_HH_
#define     PNJ_HH_

#include    "AQuidam.hh"

class       Pnj: public AQuidam {
public:
            Pnj(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin);
            Pnj(string const nom, int const forceAttaque, int const sante, int const dp, int const id_planet_origin, int const id_ship, int const id_planet, int const id_grade);
            Pnj(cJSON *node);
    virtual ~Pnj();

    boost::json::object generate(int id);
};


#endif //CPP_STAR_TREK_PNJ_H
