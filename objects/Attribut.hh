/**
* File: Attribut.hh
* Project: objects
* File Created: Thursday, 13th July 2023 11:49:25 am
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:51:00 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef         ATTRIBUT_HH_
#define         ATTRIBUT_HH_

#include        <vector>
#include        "../lib_func/cJSON.hh"

using namespace std;

class           Attribut {
public:
                Attribut(int ap, int hp, int dp);
                Attribut(cJSON *node);
    virtual     ~Attribut();

    int         getAp();
    int         getHp();
    int         getDp();
    vector<int> get_attributs();

    void        setAp(int ap);
    void        setHp(int hp);
    void        setDp(int dp);
    void        setAttributs(int ap, int hp, int dp);

protected:
    int         _hp; //Health points
    int         _dp; //Defense points
    int         _ap; //Attack points
};


#endif //CPP_STAR_TREK_ATTRIBUT_HH_
