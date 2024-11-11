/**
 * File: test.cpp
 * Project: test
 * File Created: Tuesday', 8th August 2023 4:33:41 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Tuesday', 8th August 2023 4:33:41 pm
 * Modified by: LALIN Romain
 * -----
*/

#define             CATCH_CONFIG_MAIN 
#include            "catch.hpp"
#include            "../Controller.hh"
#include            "../lib_func/cJSON.hh"

string    getMyJson(string path) {

    ifstream flux(path);
    string json = "", tmp;
    if (flux) {
        while (getline(flux, tmp)) {
            json += ((json == "" ? "" : "\n") + tmp);
        }
    } else json = "erreur d'ouverture";
    return json;
}

TEST_CASE("AJOUT D'UN PNJ") {
    SECTION("AJOUT D'UN PNJ") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "pnjs");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_planet") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_planet_origin") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_ship") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_grade") != NULL);
        CHECK(cJSON_GetObjectItem(node, "ap") != NULL);
        CHECK(cJSON_GetObjectItem(node, "dp") != NULL);
        CHECK(cJSON_GetObjectItem(node, "hp") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("test pnj 1", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(cJSON_GetObjectItem(node, "id_planet")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_planet_origin")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_ship")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_grade")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "ap")->valueint == 80);
        CHECK(cJSON_GetObjectItem(node, "dp")->valueint == 98);
        CHECK(cJSON_GetObjectItem(node, "hp")->valueint == 100);
        CHECK(dieu->getPnjs().size() == 1);
        CHECK(dieu->getPnjs().find(cJSON_GetObjectItem(node, "id")->valueint) != dieu->getPnjs().end());
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ENTITY TYPE NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == -99);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 3);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: AP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj4.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 4);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: AD NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj5.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 6);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: HP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj6.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 5);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID PLANET NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj7.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 7);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID SHIP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj8.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 8);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID GRADE NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj9.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 10);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID PLANET ORIGIN NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj10.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PNJ * 100 + 9);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID PLANET UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj11.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 5);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID SHIP UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj12.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint ==  SPACESHIP * 100 + 9);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID GRADE UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj13.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == GRADE * 100 + 5);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: ID PLANETE ORIGIN UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addpnj14.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 5);
    }
}

TEST_CASE("AJOUT D'UNE PLANETE") {
    SECTION("AJOUT D'UNE PLANETE") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addplanete1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "planetes");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "description") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("Fury", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(strcmp("Seul un furien peut y vivre", cJSON_GetObjectItem(node, "description")->valuestring) == 0);
        CHECK(dieu->getPlanetes().size() == 1);
        auto p = dieu->getPlanetes().find(cJSON_GetObjectItem(node, "id")->valueint);
        REQUIRE(p != dieu->getPlanetes().end());
        CHECK(strcmp("Fury", p->second->getName().c_str()) == 0);
        CHECK(strcmp("Seul un furien peut y vivre", p->second->getDescription().c_str()) == 0);
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UNE PLANETE DEFECTUEUSE: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addplanete2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 3);
    }

    SECTION("AJOUT D'UNE PLANETE DEFECTUEUSE: DESCRIPTION NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addplanete3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 4);
    }
}

TEST_CASE("AJOUT D'UN VAISSEAU") {
    SECTION("AJOUT D'UN VAISSEAU") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addship1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "ships");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "description") != NULL);
        CHECK(cJSON_GetObjectItem(node, "ap") != NULL);
        CHECK(cJSON_GetObjectItem(node, "dp") != NULL);
        CHECK(cJSON_GetObjectItem(node, "hp") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("Odyssey", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(strcmp("Le vaissal de la mort", cJSON_GetObjectItem(node, "description")->valuestring) == 0);
        CHECK(cJSON_GetObjectItem(node, "ap")->valueint == 200);
        CHECK(cJSON_GetObjectItem(node, "dp")->valueint == 150);
        CHECK(cJSON_GetObjectItem(node, "hp")->valueint == 1000);

        CHECK(dieu->getFlotte().size() == 1);
        auto s = dieu->getFlotte().find(cJSON_GetObjectItem(node, "id")->valueint);
        REQUIRE(s != dieu->getFlotte().end());
        CHECK(strcmp("Odyssey", s->second->getName().c_str()) == 0);
        CHECK(strcmp("Le vaissal de la mort", s->second->getDescription().c_str()) == 0);
        CHECK(s->second->getAp() == 200);
        CHECK(s->second->getDp() == 150);
        CHECK(s->second->getHp() == 1000);
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addship2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == SPACESHIP * 100 + 3);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: DESCRIPTION NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addship3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == SPACESHIP * 100 + 4);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: AP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addship4.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == SPACESHIP * 100 + 5);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: AD NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addship5.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == SPACESHIP * 100 + 6);
    }

    SECTION("AJOUT D'UN PNJ DEFECTUEUX: HP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addship6.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == SPACESHIP * 100 + 7);
    }
}

TEST_CASE("AJOUT D'UNE MISSION") {
    SECTION("AJOUT D'UNE MISSION") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addmission1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "missions");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "description") != NULL);
        CHECK(cJSON_GetObjectItem(node, "is_complete") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("Sauver Dr Landra", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(strcmp("une description de mission", cJSON_GetObjectItem(node, "description")->valuestring) == 0);
        CHECK(cJSON_GetObjectItem(node, "is_complete")->valueint == 0);
        CHECK(dieu->getMissions().size() == 1);

        auto p = dieu->getMissions().find(cJSON_GetObjectItem(node, "id")->valueint);
        REQUIRE(p != dieu->getMissions().end());
        CHECK(strcmp("Sauver Dr Landra", p->second->getName().c_str()) == 0);
        CHECK(strcmp("une description de mission", p->second->getDescription().c_str()) == 0);
        CHECK(p->second->getIsComplete() == 0);
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UNE MISSION DEFECTUEUSE: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addmission2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == MISSION * 100 + 3);
    }

    SECTION("AJOUT D'UNE MISSION DEFECTUEUSE: DESCRIPTION NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addmission3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == MISSION * 100 + 4);
    }

    SECTION("AJOUT D'UNE MISSION DEFECTUEUSE: IS COMPLETE NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addmission4.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == MISSION * 100 + 5);
    }
}

TEST_CASE("AJOUT D'UN EVIL") {
    SECTION("AJOUT D'UN EVIL") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "mechants");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_planet") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_planet_origin") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_ship") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_grade") != NULL);
        CHECK(cJSON_GetObjectItem(node, "ap") != NULL);
        CHECK(cJSON_GetObjectItem(node, "dp") != NULL);
        CHECK(cJSON_GetObjectItem(node, "hp") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("test evil 1", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(cJSON_GetObjectItem(node, "id_planet")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_planet_origin")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_ship")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_grade")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "ap")->valueint == 80);
        CHECK(cJSON_GetObjectItem(node, "dp")->valueint == 98);
        CHECK(cJSON_GetObjectItem(node, "hp")->valueint == 100);
        CHECK(dieu->getEvils().size() == 1);
        CHECK(dieu->getEvils().find(cJSON_GetObjectItem(node, "id")->valueint) != dieu->getEvils().end());
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ENTITY TYPE NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == -99);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 3);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: AP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil4.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 4);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: AD NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil5.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 6);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: HP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil6.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 5);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID PLANET NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil7.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 7);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID SHIP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil8.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 8);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID GRADE NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil9.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 10);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID PLANET ORIGIN NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil10.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == EVIL * 100 + 9);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID PLANET UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil11.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 5);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID SHIP UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil12.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint ==  SPACESHIP * 100 + 9);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID GRADE UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil13.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == GRADE * 100 + 5);
    }

    SECTION("AJOUT D'UN EVIL DEFECTUEUX: ID PLANETE ORIGIN UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addevil14.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 5);
    }
}

TEST_CASE("AJOUT D'UN HEROS") {
    SECTION("AJOUT D'UN HEROS") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "heros");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_planet") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_planet_origin") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_ship") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_grade") != NULL);
        CHECK(cJSON_GetObjectItem(node, "ap") != NULL);
        CHECK(cJSON_GetObjectItem(node, "dp") != NULL);
        CHECK(cJSON_GetObjectItem(node, "hp") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("test heros 1", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(cJSON_GetObjectItem(node, "id_planet")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_planet_origin")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_ship")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "id_grade")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "ap")->valueint == 80);
        CHECK(cJSON_GetObjectItem(node, "dp")->valueint == 98);
        CHECK(cJSON_GetObjectItem(node, "hp")->valueint == 100);
        CHECK(dieu->getPersos().size() == 1);
        CHECK(dieu->getPersos().find(cJSON_GetObjectItem(node, "id")->valueint) != dieu->getPersos().end());
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ENTITY TYPE NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == -99);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 3);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: AP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros4.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 4);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: AD NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros5.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 6);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: HP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros6.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 5);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID PLANET NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros7.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 7);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID SHIP NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros8.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 8);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID GRADE NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros9.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 10);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID PLANET ORIGIN NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros10.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == HEROS * 100 + 9);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID PLANET UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros11.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 5);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID SHIP UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros12.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint ==  SPACESHIP * 100 + 9);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID GRADE UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros13.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == GRADE * 100 + 5);
    }

    SECTION("AJOUT D'UN HEROS DEFECTUEUX: ID PLANETE ORIGIN UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addheros14.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == PLANETE * 100 + 5);
    }
}

TEST_CASE("AJOUT D'UN GRADE") {
    SECTION("AJOUT D'UN GRADE") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addgrade1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "grades");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "level") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("Capitaine", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(cJSON_GetObjectItem(node, "level")->valueint == 5);
        CHECK(dieu->getGrades().size() == 1);
        auto p = dieu->getGrades().find(cJSON_GetObjectItem(node, "id")->valueint);
        REQUIRE(p != dieu->getGrades().end());
        CHECK(strcmp("Capitaine", p->second->getNom().c_str()) == 0);
        CHECK(p->second->getLevel() == 5);
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UN GRADE DEFECTUEUX: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addgrade2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == GRADE * 100 + 3);
    }

    SECTION("AJOUT D'UN GRADE DEFECTUEUX: LEVEL NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/addgrade3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == GRADE * 100 + 4);
    }
}

TEST_CASE("AJOUT D'UN ITEM") {
    SECTION("AJOUT D'UN ITEM") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem1.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *node, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        REQUIRE(cJSON_GetObjectItem(r, "code")->valueint == 0);
        REQUIRE(r != NULL);
        node = cJSON_GetObjectItem(r, "return");
        REQUIRE(node != NULL);
        node = cJSON_GetObjectItem(node, "items");
        REQUIRE(node != NULL);
        REQUIRE(cJSON_GetArraySize(node) == 1);
        node = cJSON_GetArrayItem(node, 0);
        CHECK(cJSON_GetObjectItem(node, "id") != NULL);
        CHECK(cJSON_GetObjectItem(node, "name") != NULL);
        CHECK(cJSON_GetObjectItem(node, "stat") != NULL);
        CHECK(cJSON_GetObjectItem(node, "stat") != NULL);
        CHECK(cJSON_GetObjectItem(node, "effect") != NULL);
        CHECK(cJSON_GetObjectItem(node, "id_owner") != NULL);
        CHECK(cJSON_GetObjectItem(node, "type_owner") != NULL);

        CHECK(cJSON_GetObjectItem(node, "id")->valueint == 1);
        CHECK(strcmp("Escaliburne", cJSON_GetObjectItem(node, "name")->valuestring) == 0);
        CHECK(cJSON_GetObjectItem(node, "stat")->valueint == -90);
        CHECK(cJSON_GetObjectItem(node, "effect")->valueint == 2);
        CHECK(cJSON_GetObjectItem(node, "id_owner")->valueint == 0);
        CHECK(cJSON_GetObjectItem(node, "type_owner")->valueint == NONE);
        CHECK(dieu->getItems().size() == 1);
        auto p = dieu->getItems().find(cJSON_GetObjectItem(node, "id")->valueint);
        REQUIRE(p != dieu->getItems().end());
        CHECK(strcmp("Escaliburne", p->second->getName().c_str()) == 0);
        CHECK(p->second->getStat() == -90);
        CHECK(p->second->getEffect() == 2);
        CHECK(p->second->getTypeOwner() == NONE);
        CHECK(p->second->getIdOwner() == 0);
        cJSON_Delete(json);
        cJSON_Delete(r);
        free(retour);
        free(dieu);
    }

    SECTION("AJOUT D'UN ITEM DEFECTUEUX: NAME NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem2.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == ITEM * 100 + 3);
    }

    SECTION("AJOUT D'UN ITEM DEFECTUEUX: STAT NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem3.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == ITEM * 100 + 4);
    }

    SECTION("AJOUT D'UN ITEM DEFECTUEUX: EFFECT NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem4.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == ITEM * 100 + 5);
    }

    SECTION("AJOUT D'UN ITEM DEFECTUEUX: ID OWNER NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem5.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == ITEM * 100 + 6);
    }

    SECTION("AJOUT D'UN ITEM DEFECTUEUX: TYPE OWNER NOT FOUND") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem6.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == ITEM * 100 + 7);
    }

    SECTION("AJOUT D'UN ITEM DEFECTUEUX: ID OWNER UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem7.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == cJSON_GetObjectItem(cJSON_GetArrayItem(cJSON_GetObjectItem(json, "startrek"), 0), "type_owner")->valueint * 100 + 12);
    }

     SECTION("AJOUT D'UN ITEM DEFECTUEUX: TYPE OWNER UNKNOWN") {
        Controller *dieu = new Controller();
        char *retour;
        int code = 0;
        string parse = getMyJson("test/json/command/addEntities/additem8.json");
        REQUIRE(parse != "erreur d'ouverture");
        cJSON *r, *json = cJSON_Parse(parse.c_str());
        REQUIRE(json != NULL);
        retour = (code = List::isCorrectToGetAddEntitiesPrototype(json)) == 0 ? dieu->j_add_entities(cJSON_GetObjectItem(json, "startrek")) : List::returnJson(code);
        r = cJSON_Parse(retour);
        CHECK(cJSON_GetObjectItem(r, "code")->valueint == NONE * 100 + 17);
    }
}
