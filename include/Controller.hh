/*
 * File: Controller.hh                                                         *
 * Project: include                                                            *
 * Created Date: Tu May 2025, 11:12:03 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 6:47:03 pm                           *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef                                         CONTROLLER_HH_
#define                                         CONTROLLER_HH_

#include                                        <vector>
#include                                        <algorithm>
#include                                        <map>
#include                                        <list>
#include                                        <string>
#include                                        <fstream>
#include                                        "define.hh"
#include                                        "Rule.hh"
#include                                        "object/Token.hh"
#include                                        "../lib_func/List.hh"
#include                                        "server.hh"
#include                                        "router.hh"
 
using namespace                                 std;

class                                           Controller : public Rule {


public:
                                                Controller();
    virtual                                     ~Controller();

    Server                                     *getServeur();
    shared_ptr<Router>                          &getRouter() { return this->_router; }                                
    map<int, shared_ptr<Token>>                 &getToken() { return this->_tokens; }

    void                                        saveJSON();
    string                                      buildResponse(ResultRequest result);

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

    /*int                                          getMaxId(OBJETS type);*/

private:
    map<int, shared_ptr<Token>>                 _tokens;
    Server                                      *_serveur;
    shared_ptr<Router>                          _router;                                     
};

#endif //CPP_HEROSNNAGE_CONTROLLER_H
