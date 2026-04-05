/*
 * File: AttributBuilder.hh                                                    *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 4:20:00 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 5:34:12 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef ATTRIBUT_BUILDER_HH
#define ATTRIBUT_BUILDER_HH

using namespace std;

#include    <stdexcept>

template    <typename Derived>
class       AttributBuilder
{
protected:
    int     _ap = 0;
    int     _hp = 0;
    int     _dp = 0;
    void    validate() {
        if (_ap <= 0) throw runtime_error("AP invalide");
        if (_hp <= 0) throw runtime_error("HP invalide");
        if (_dp <= 0) throw runtime_error("DP invalide");
    }

public:
    Derived &withAp(int ap) { _ap = ap; return static_cast<Derived&>(*this); }
    Derived &withHp(int hp) { _hp = hp; return static_cast<Derived&>(*this); }
    Derived &withDp(int dp) { _dp = dp; return static_cast<Derived&>(*this); }
};

#endif