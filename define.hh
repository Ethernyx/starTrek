/**
* File: define.hh
* Project: star_strek
* File Created: Monday, 10th July 2023 11:18:59 am
* Author: LALIN Romain 
* -----
* Last Modified: Thursday, 27th July 2023 9:18:08 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef DEFINE_HH_
#define DEFINE_HH_

#define BDDFILE "bdd.json"
#define SEP "|"
#define CLEAR "cls"
#define MDP "je préfère le Faucon Millenium"
#define QUIDAMS vector<OBJETS> {HEROS, PNJ, EVIL}

typedef enum {
    NONE = -1,
    PLANETE,
    SPACESHIP,
    HEROS,
    PNJ,
    EVIL,
    MISSION,
    ITEM,
    GRADE,
    LIVING
} OBJETS; 

typedef  enum {
    AP = 1,
    HP,
    DP,
} EFFECT;

#endif //CPP_STAR_TREK_DEFINE_H
