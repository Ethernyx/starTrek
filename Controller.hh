/**
* File: Controller.hh
* Project: star_strek
* File Created: Monday, 24th July 2023 11:31:29 am
* Author: LALIN Romain 
* -----
* Last Modified: Thursday, 27th July 2023 9:56:28 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef                                         CONTROLLER_HH_
#define                                         CONTROLLER_HH_

#include                                        <vector>
#include                                        <algorithm>
#include                                        <map>
#include                                        <string>
#include                                        <fstream>
#include                                        "define.hh"
#include                                        "objects/Mission.hh"
#include                                        "objects/Heros.hh"
#include                                        "objects/Pnj.hh"
#include                                        "objects/Evil.hh"
#include                                        "objects/Planete.hh"
#include                                        "objects/Spaceship.hh"
#include                                        "objects/Item.hh"
#include                                        "objects/Grade.hh"
#include                                        "lib_func/List.hh"
#include                                        "Serveur.hh"

using namespace                                 std;

class                                           Controller {


public:
                                                Controller();
    virtual                                     ~Controller();

    map<int, shared_ptr<Spaceship>>             &getFlotte();
    map<int, shared_ptr<AQuidam>>               &getPersos();
    map<int, shared_ptr<AQuidam>>               &getPnjs();
    map<int, shared_ptr<AQuidam>>               &getEvils();
    map<int, shared_ptr<Planete>>               &getPlanetes();
    map<int, shared_ptr<Mission>>               &getMissions();
    map<int, unique_ptr<Item>>                  &getItems();
    map<int, shared_ptr<Grade>>                 &getGrades();
    vector<string>                              getItems(bool); // trie false return pas affecté et true return les affecté
    Serveur                                     *getServeur();

    void                                        init(cJSON *node);
    bool                                        deletePerso(string const name); // --> suppression du perso via son nom
    bool                                        deletePerso(int const id); // --> surcharge suppression du perso via son ID
    int                                         addQuidam(const string name, const int puissance, const int sante, const int dp, const int id_planet, const int id_ship, const int id_planete_origine, const int id_grade, OBJETS type);
    int                                         addPnj(const string name, const int puissance, const int sante, const int dp, const int id_planet, const int id_ship, const int id_planete_origine, const int id_grade);

    shared_ptr<AQuidam>                         getPerso(const string name);
    shared_ptr<Spaceship>                       getSpaceship(const string name);
    shared_ptr<Mission>                         getMission(const string name);
    shared_ptr<Planete>                         getPlanete(const string name);
    unique_ptr<Item>                            getItem(const int id);

    bool                                        deletePlanete(string const name); // -> surcharge de la suppression d'une planete par son nom
    bool                                        deletePlanete(int const id_planet); // -> surcharge de la suppression d'une planete par son ID
    int                                         addPlanet(const string name, const string description);

    bool                                        deleteMission(string const name);
    bool                                        deleteMission(int const id);
    int                                         addMission(const string name, const string description);

    bool                                        deleteSpaceship(string const name); // delete spaceShip par son nom
    bool                                        deleteSpaceship(int const id_ship); // delete spaceShip par son ID
    int                                         addSpaceShip(const string name, const string description, int ap, int hp, int dp);

    int                                         attaqueSimple(OBJETS type_attaquant, const int id_attaquant, OBJETS type_victime,const int id_victime);
    void                                        takeItem(int item, int id, OBJETS type);
    void                                        removeItem(int idItem, string name, OBJETS type);
    int                                         addItem(const string name, const int stat, const EFFECT effect, const int id, const OBJETS type);
    void                                        deleteItem(int id);
    void                                        saveJSON();

    void                                        promote(int id_grade, int id_entity, OBJETS entity_type);
    void                                        removeGrade(int id_entity, OBJETS entity_type);
    int                                         addGrade(const string, const int level);
    bool                                        deleteGrade(const int id);

    char                                        *j_attack(cJSON *startrek);
    char                                        *j_exchangeItem(cJSON *startrek);
    char                                        *j_getInfos(cJSON *startrek);
    char                                        *j_kill(cJSON *startrek);
    char                                        *j_add_entities(cJSON *startrek);
    char                                        *j_escape(cJSON *startrek);
    char                                        *j_getHabitants(cJSON *starttrek);
    char                                        *j_getEquipage(cJSON *starttrek);
    char                                        *j_getInventory(cJSON *starttrek);
    char                                        *j_getHierarchy(cJSON *strattrek);
    char                                        *j_promote(cJSON *strattrek);

    int                                          getMaxId(OBJETS type);

private:
    map<OBJETS, map<int, shared_ptr<AQuidam>>>  _quidams;
    map<int, shared_ptr<Grade>>                 _grades;
    map<int, shared_ptr<Spaceship>>             _flotte;
    map<int, shared_ptr<Planete>>               _planetes;
    map<int, shared_ptr<Mission>>               _missions;
    map<int, unique_ptr<Item>>                  _items;
    map<int, map<int, int>>                     _tableDeCorrespondance; // map[OBJECT][id item] = id perso
    Serveur                                     *_serveur;
};

#endif //CPP_HEROSNNAGE_CONTROLLER_H
