/**
 * File: Heros.hh
 * Project: objects
 * File Created: Friday', 28th July 2023 2:33:51 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Friday', 28th July 2023 2:33:51 pm
 * Modified by: LALIN Romain
 * -----
*/

#ifndef                         HEROS_HH_
#define                         HEROS_HH_

#include                        "AQuidam.hh"

using namespace                 std;

class                           Heros: public AQuidam {
public:
                                Heros(string const nom, int const forceAttaque, int const sante, int const dp, int id_planet_origin);
                                Heros(string const nom, int const forceAttaque, int const sante, const int dp, int id_planet_origin, int id_ship, int id_planet, int id_grade);
                                Heros(cJSON *node);

    virtual                     ~Heros();

    boost::json::object         generate(int id);
};


#endif //CPP_LAMPE_HEROSNNAGE_H
