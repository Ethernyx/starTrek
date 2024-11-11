
#ifndef         AFFICHAGE_HH_
#define         AFFICHAGE_HH_

#include        <memory>
#include        <map>
#include        "../objects/Mission.hh"
#include        "../objects/Planete.hh"
#include        "../objects/Heros.hh"
#include        "../objects/Spaceship.hh"
using namespace std;

class           Affichage
{
public:
    static void displayMainMenu();
    static void displayMissions(map<int, shared_ptr<Mission>> &);
    static void displayPlanetes(map<int, shared_ptr<Planete>> &);
    static void displayHeros(map<int, shared_ptr<Heros>> &);
    static void displaySpaceShips(map<int, shared_ptr<Spaceship>> &);
    static void clear();

};


#endif
