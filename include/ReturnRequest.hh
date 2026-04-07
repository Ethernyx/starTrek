/*
 * File: ReturnRequest.hh                                                      *
 * Project: include                                                            *
 * Created Date: Su Apr 2026, 4:39:47 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 10:36:07 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RETURN_REQUEST_HH_
#define RETURN_REQUEST_HH_

#include    "object/AQuidam.hh"
#include    "object/Item.hh"
#include    "object/Mission.hh"
#include    "object/Planete.hh"
#include    "object/Spaceship.hh"
#include    "object/Grade.hh"
#include    "define.hh"

typedef struct {
    map<OBJETS, map<int, shared_ptr<AQuidam>>>  _quidams;
    map<int, Item*>                             _items;
    map<int, shared_ptr<Mission>>               _missions;
    map<int, shared_ptr<Planete>>               _planetes;
    map<int, shared_ptr<Spaceship>>             _spaceships;
    map<int, shared_ptr<Grade>>                 _grades;
    CODE_ERROR                                  _code = OK;

}                                               ResultRequest;

#endif