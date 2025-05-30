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
#include                                        <vector>
#include                                        <string>
#include                                        <fstream>
#include                                        "define.hh"
#include                                        "object/Mission.hh"
#include                                        "object/Heros.hh"
#include                                        "object/Pnj.hh"
#include                                        "object/Evil.hh"
#include                                        "object/Planete.hh"
#include                                        "object/Spaceship.hh"
#include                                        "object/Item.hh"
#include                                        "object/Grade.hh"
#include                                        "object/Token.hh"
#include                                        "../lib_func/List.hh"
#include                                        "server.hh"
#include                                        "router.hh"
 
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
    Server                                     *getServeur();
    shared_ptr<Router>                          &getRouter() { return this->_router; }                                
    map<int, shared_ptr<Token>>                 &getToken() { return this->_tokens; }
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

    string                                      init();
    string                                      init(string json);
    string                                      j_attack(Context &ctx);
    string                                      j_exchangeItem(Context &ctx);
    string                                      j_getInfos(Context &ctx);
    string                                      j_kill(Context &ctx);
    string                                      j_add_entities(Context &ctx);
    string                                      j_getHabitants(Context &ctx);
    string                                      j_getEquipage(Context &ctx);
    string                                      j_getInventory(Context &ctx);
    string                                      j_getHierarchy(Context &ctx);
    string                                      j_promote(Context &ctx);
    string                                      j_getToken(Context &ctx);

    int                                          getMaxId(OBJETS type);

private:
    map<OBJETS, map<int, shared_ptr<AQuidam>>>  _quidams;
    map<int, shared_ptr<Grade>>                 _grades;
    map<int, shared_ptr<Spaceship>>             _flotte;
    map<int, shared_ptr<Planete>>               _planetes;
    map<int, shared_ptr<Mission>>               _missions;
    map<int, unique_ptr<Item>>                  _items;
    map<int, map<int, int>>                     _tableDeCorrespondance; // map[OBJECT][id item] = id perso
    map<int, shared_ptr<Token>>                 _tokens;
    Server                                      *_serveur;
    shared_ptr<Router>                          _router;                                     
};

#endif //CPP_HEROSNNAGE_CONTROLLER_H
