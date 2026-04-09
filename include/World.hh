/*
 * File: World.hh                                                              *
 * Project: include                                                            *
 * Created Date: Su Apr 2026, 3:33:10 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 2:11:19 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef WORLD_HH_
#define WORLD_HH_

#include    <memory>
#include    "define.hh"
#include    "object/Grade.hh"
#include    "object/AQuidam.hh"
#include    "object/Item.hh"
#include    "object/Spaceship.hh"
#include    "object/Planete.hh"
#include    "object/Mission.hh"
#include    "ReturnRequest.hh"

class World
{
protected:
    map<OBJETS, map<int, shared_ptr<AQuidam>>>  _quidams;
    map<int, shared_ptr<Grade>>                 _grades;
    map<int, shared_ptr<Spaceship>>             _flotte;
    map<int, shared_ptr<Planete>>               _planetes;
    map<int, shared_ptr<Mission>>               _missions;
    map<int, unique_ptr<Item>>                  _items;
    map<int, map<int, int>>                     _tableDeCorrespondance; // map[OBJECT][id item] = id perso
public:
    map<int, shared_ptr<Spaceship>>             &getFlotte();
    map<int, shared_ptr<AQuidam>>               &getPersos();
    map<int, shared_ptr<AQuidam>>               &getPnjs();
    map<int, shared_ptr<AQuidam>>               &getEvils();
    map<int, shared_ptr<Planete>>               &getPlanetes();
    map<int, shared_ptr<Mission>>               &getMissions();
    map<int, unique_ptr<Item>>                  &getItems();
    map<int, shared_ptr<Grade>>                 &getGrades();
    vector<string>                              getItems(bool); // trie false return pas affecté et true return les affecté

    shared_ptr<AQuidam>                         getPerso(const string name);
    shared_ptr<Spaceship>                       getSpaceship(const string name);
    shared_ptr<Mission>                         getMission(const string name);
    shared_ptr<Planete>                         getPlanete(const string name);
    shared_ptr<AQuidam>                         getPerso(const int id);
    shared_ptr<Spaceship>                       getSpaceship(const int id);
    shared_ptr<Mission>                         getMission(const int id);
    shared_ptr<Planete>                         getPlanete(const int id);
    unique_ptr<Item>                            getItem(const int id);
    int                                         getIdQuidam(shared_ptr<AQuidam> quidam);

    int                                         getMaxId(OBJETS type);

    bool                                        isQuidamExist(ResultRequest *result, OBJETS type, int id);
    bool                                        isGradeExist(ResultRequest *result, int id);
    bool                                        isSpaceshipExist(ResultRequest *result, int id);
    bool                                        isPlaneteExist(ResultRequest *result, int id);
    bool                                        isMissionExist(ResultRequest *result, int id);
    bool                                        isItemExist(ResultRequest *result, int id);
    bool                                        isItemExist(ResultRequest *result, OBJETS type, int id);
};


#endif