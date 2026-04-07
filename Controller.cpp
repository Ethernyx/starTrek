/*
 * File: Controller.cpp                                                        *
 * Project: starTrek                                                           *
 * Created Date: Tu May 2025, 11:12:38 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 3:21:53 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include "include/Controller.hh"

using namespace std;

Controller::Controller()
{
    this->_router = std::make_shared<Router>();
    this->_serveur = new Server(PORT, this->_router);
#ifdef DEBUG
    cout << "Des visiteurs, venues d'ailleurs, hoooooo!!!!. Le Controller!!!!!" << endl;
#endif
}

Controller::~Controller()
{
#ifdef DEBUG
    cout << "Le contrôler à été détruit, que va t'on devenir" << endl;
#endif
}

Server *Controller::getServeur() {
    return this->_serveur;
}

vector<string> split(string str, string delimiter)
{
    vector<string> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
            // Find the index of occurrence
            size_t idx = str.find(delimiter, start);
            if (idx == string::npos)
            {
                break;
            }

            // If found add the substring till that
            // occurrence in the vector
            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }

    return v;
}

void    Controller::saveJSON() {
    boost::json::object res, startrek;
    boost::json::array node;

    /* gestion des planètes */
    startrek[to_string(PLANETE)].emplace_array();
    for(auto p: this->_planetes) {
        node.push_back(p.second->generate(p.first));
    }
    startrek[to_string(PLANETE)] = node;
    node.clear();

    /* gestion des vaisseaux */
    startrek[to_string(SPACESHIP)].emplace_array();
    for(auto p: this->_flotte) {
        node.push_back(p.second->generate(p.first));
    }
    startrek[to_string(SPACESHIP)] = node;
    node.clear();

    /* gestion des quidams */
    for (auto q : this->_quidams) {
        startrek[to_string(q.first)].emplace_array();
        for (auto v : q.second) {
            node.push_back(v.second->generate(v.first));
        }
        startrek[to_string(q.first)] = node;
        node.clear();
    }

    /* gestion des missions */
    startrek[to_string(MISSION)].emplace_array();
    for(auto p: this->_missions) {
        node.push_back(p.second->generate(p.first));
    }
    startrek[to_string(MISSION)] = node;
    node.clear();

        /* gestion des items */
    startrek[to_string(ITEM)].emplace_array();
    for (auto i : this->_tableDeCorrespondance) { // comme fonctionnement par unique_ptr on prend la table des corespondances
        switch (i.first) {
        case HEROS:
        case PNJ:
        case EVIL:
            for (auto p : i.second) {
                node.push_back(this->_quidams[(OBJETS)i.first][p.second]->getInventory()[p.first]->generate(p.first));
            }
            break;
        case SPACESHIP:
            for (auto s : i.second) {
                node.push_back(this->_flotte[s.second]->getInventory()[s.first]->generate(s.first));
            }
            break;
        case NONE:
            for (auto s : i.second) {
                node.push_back(this->_items[s.first]->generate(s.first));
            }
            break;
        default:
            break;
        }
    }
    startrek[to_string(ITEM)] = node;
    node.clear();

    /* gestion des grades */
    startrek[to_string(GRADE)].emplace_array();
    for(auto p: this->_grades) {
        node.push_back(p.second->generate(p.first));
    }
    startrek[to_string(GRADE)] = node;
    node.clear();

    /* gestion des token */
    startrek[to_string(TOKEN)].emplace_object();
    for(auto it: this->_tokens) {
        node.push_back(it.second->generate(it.first));
    }
    startrek[to_string(TOKEN)] = node;
    node.clear();

    res["startrek"] = startrek;
    FILE *f;
    f = fopen(BDDFILE,"w");
    fprintf(f,"%s\n", boost::json::serialize(res).c_str());
    fclose(f);
}


string Controller::init(string bdd) {
    boost::json::object root = boost::json::parse(bdd).as_object().at("startrek").as_object();
    for (auto it = root.begin(); it != root.end(); it++) {
        for (size_t i = 0; i < it->value().as_array().size(); i++) {
            boost::json::object item = it->value().as_array().at(i).as_object();
            switch (stoi(it->key())) {
                case PLANETE:
                    this->_planetes[item.at("id").as_int64()] = make_shared<Planete>(item);
                    break;
                case SPACESHIP:
                    this->_flotte[item.at("id").as_int64()] = make_shared<Spaceship>(item);
                    break;
                case HEROS:
                    this->_quidams[HEROS][item.at("id").as_int64()] = make_shared<Heros>(item);
                    break;
                case PNJ:
                    this->_quidams[PNJ][item.at("id").as_int64()] = make_shared<Pnj>(item);
                    break;
                case EVIL:
                    this->_quidams[EVIL][item.at("id").as_int64()] = make_shared<Evil>(item);
                    break;
                case MISSION:
                    this->_missions[item.at("id").as_int64()] = make_shared<Mission>(item);
                    break;
                case ITEM:
                    this->_items[item.at("id").as_int64()] = make_unique<Item>(item);
                    this->_tableDeCorrespondance[item.at("type_owner").as_int64()][item.at("id").as_int64()] = item.at("id_owner").as_int64();
                    break;
                case GRADE:
                    this->_grades[item.at("id").as_int64()] = make_shared<Grade>(item);
                    break;
                case TOKEN:
                    this->_tokens[item.at("id").as_int64()] = make_shared<Token>(item);
                    break;
                default:
                    cout << "pas planete" << endl;
                    break;
            }
        }
    }

    /* je remplis mes relations */
    for (auto it = this->_items.begin(); it != this->_items.end(); it++) {
        if (it->second->getIdOwner() != 0) {
            switch (it->second->getTypeOwner())
            {
                case PNJ:
                    this->_quidams[PNJ][it->second->getIdOwner()]->addItem(it->second, it->first);
                    break;
                case HEROS:
                    this->_quidams[HEROS][it->second->getIdOwner()]->addItem(it->second, it->first);
                    break;
                case SPACESHIP:
                    this->_flotte[it->second->getIdOwner()]->addItem(it->second, it->first);
                    break;
                default:
                    break;
            }
        }
    }

    vector<OBJETS> types {HEROS, PNJ, EVIL};
    for (auto type : types) {
        for (auto elem : this->_quidams[type])
        { // pour chaque player
            if (elem.second->getIdPlanet() != 0)
            { // je test si il ont une planete
                for (auto pl : this->_planetes)
                {
                    if (elem.second->getIdPlanet() == pl.first)
                    {
                        pl.second->setHabitant(elem.second); // si id du player = id planete je add
                        break;
                    }
                }
            }
            if (elem.second->getIdShip() != 0)
            { // je test si il ont un ship
                for (auto sh : this->_flotte)
                {
                    if (elem.second->getIdShip() == sh.first)
                    {
                        sh.second->addEquipage(elem.second); // si id du player = id ship je add
                        break;
                    }
                }
            }
            if (elem.second->getIdGrade() != 0) {
            for (auto g : this->_grades)
                {
                    if (elem.second->getIdGrade() == g.first)
                    {
                        g.second->addMembre(elem.second); // si id du player = id ship je add
                        break;
                    }
                }
            }
        }
    }
    return string("OK");
}
string Controller::init() {
        FILE *f;
        long lSize;
        if (access( BDDFILE, F_OK ) == -1) {
            f = fopen(BDDFILE, "w");
            fclose(f);
        }
        f = fopen(BDDFILE, "r");
        fseek (f , 0 , SEEK_END);
        lSize = ftell (f);
        rewind (f);
        char *buffer = (char*) malloc (sizeof(char)*lSize + 1);
        fread (buffer,1,lSize,f);
        string json = string(buffer, strlen(buffer));
        if (!List::checkJson(json)) cout << "Error json incorect bdd mauvaise ?" << endl;
        fclose(f);
        free(buffer);
        return this->init(json);
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action d'attaque
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_attack(Context &ctx) {
    int hp = 0, dead = 0;
    string retour = NULL;
    boost::json::object json = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object(), defenseur, attaquant, res, node;
    attaquant = json.at("attaquant").as_object();
    defenseur = json.at("defenseur").as_object();

    OBJETS  typeAttaquant = (OBJETS)attaquant.at("type").as_int64();
    OBJETS  typeDefenseur = (OBJETS)defenseur.at("type").as_int64();

    if(typeDefenseur == typeAttaquant 
        || (find(QUIDAMS.begin(), QUIDAMS.end(), typeAttaquant) != QUIDAMS.end() 
            && find(QUIDAMS.begin(), QUIDAMS.end(), typeDefenseur) != QUIDAMS.end())) {
        switch (typeAttaquant) {
            case HEROS:
            case EVIL:
            case PNJ:
                //retourne si la victime est morte
                //dans la generation du json, on retourne le HP du perso, donc,
                // savoir si la victime est morte ou pas, ici, n'a aucun intérêt
                dead = this->attaqueSimple((OBJETS)typeAttaquant, attaquant.at("id").as_int64(), (OBJETS)typeDefenseur,defenseur.at("id").as_int64());
                if (dead == -1) return List::returnJson(UNKNOWN_DEFENSE_OR_ATTACK); // si c'est -1 ça veut dire qu'1 des 2 n'existe pas
                hp = dead ? 0 : this->_quidams[typeDefenseur][defenseur.at("id").as_int64()]->getHp();
                break;
            case SPACESHIP:
                dead = this->attaqueSimple((OBJETS)typeAttaquant, attaquant.at("id").as_int64(), (OBJETS)typeDefenseur,defenseur.at("id").as_int64());
                if (dead == -1) return List::returnJson(UNKNOWN_DEFENSE_OR_ATTACK);
                hp = dead ? 0 : this->_flotte[defenseur.at("id").as_int64()]->getHp();
                break;
            case MISSION:
            case GRADE:
            case PLANETE:
            case ITEM:
                retour = List::returnJson(UNKNOWN_ENTITY);
                break;
            default:
                retour = List::returnJson(UNKNOWN_ENTITY);
                break;
        }
    } else retour = List::returnJson(ENTITY_OUT_RANGE);

    if (!retour.empty()) return retour;
    node["id"] = defenseur.at("id").as_int64();
    node["entity_type"] = defenseur.at("type").as_int64();
    node["hp"] = hp;
    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"] = node;
    this->saveJSON();
    return boost::json::serialize(res);
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action exchangeItem
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string 
 */
string  Controller::j_exchangeItem(Context &ctx) {
    auto startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_array();
    int code = 0;

    for (size_t i = 0; i < startrek.size(); i++) {
        auto objet = startrek.at(i).as_object();
        OBJETS type = (OBJETS)objet.at("entity_type").as_int64();
        auto entity_id = objet.at("entity_id").as_int64();
        auto action = objet.at("action").as_string();
        switch (type) {
            case HEROS:
            case PNJ:
            case EVIL:
                for (size_t j = 0; j < objet.at("items").as_array().size(); j++) {
                    auto id_item = objet.at("items").as_array().at(j).as_int64();
                    if (this->_quidams[type].find(entity_id) == this->_quidams[type].end()) return List::returnJson((type == HEROS ? UNKNOWN_HEROS : (type == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)));
                    if(strcmp(action.c_str(),"pull") == 0) {
                        //le perso recupere les items
                        if(this->getPerso(this->_quidams[type].find(entity_id)->second->getName())->getInventory().size() <= this->getPerso(this->_quidams[type].find(entity_id)->second->getName())->getMaxItem()) {
                            if (this->_tableDeCorrespondance[NONE].find(id_item) == this->_tableDeCorrespondance[NONE].end()) return List::returnJson(ITEM_OCCUPY);
                            this->takeItem(id_item, entity_id, type);
                        } else return List::returnJson((type == HEROS ? MAX_ITEM_OVERFLOW_HEROS : (type == PNJ ? MAX_ITEM_OVERFLOW_PNJ : MAX_ITEM_OVERFLOW_EVIL)));
                    } else if (strcmp(action.c_str(), "push") == 0) {
                        if (!(this->_tableDeCorrespondance[type].find(id_item) != this->_tableDeCorrespondance[type].end() && this->_tableDeCorrespondance[type][id_item] == entity_id)) return List::returnJson((type == HEROS ? UNKNOWN_ITEM_HEROS : (type == PNJ ? UNKNOWN_ITEM_PNJ : UNKNOWN_ITEM_EVIL)));
                        this->removeItem(id_item, this->_quidams[type].find(entity_id)->second->getName(), type);
                    } else return List::returnJson(UNKNOWN_ACTION);
                }
                break;
            case SPACESHIP:
                for (size_t j = 0; j < objet.at("items").as_array().size(); j++) {
                    auto id_item = objet.at("items").as_array().at(j).as_int64();
                    if (this->_flotte.find(entity_id) == this->_flotte.end()) return List::returnJson(UNKNOWN_SPACESHIP);
                    if(strcmp(action.c_str(),"pull") == 0) {
                        //le Spaceship recupere les items
                        if(this->getSpaceship(this->_flotte.find(entity_id)->second->getName())->getInventory().size() <= this->getSpaceship(this->_flotte.find(entity_id)->second->getName())->getMaxItem()) {
                            if (this->_tableDeCorrespondance[NONE].find(id_item) == this->_tableDeCorrespondance[NONE].end()) return List::returnJson(ITEM_OCCUPY);
                            this->takeItem(id_item, entity_id, type);
                        } else return List::returnJson(MAX_ITEM_OVERFLOW_SPACESHIP);
                    } else if (strcmp(action.c_str(), "push") == 0) {
                        if (!(this->_tableDeCorrespondance[type].find(id_item) != this->_tableDeCorrespondance[type].end() && this->_tableDeCorrespondance[type][id_item] == entity_id)) return List::returnJson(UNKNOWN_ITEM_SPACECHIP);
                        this->removeItem(id_item, this->_flotte.find(entity_id)->second->getName(), type);
                    } else return List::returnJson(UNKNOWN_ACTION);
                }
                break;
            default:
                return List::returnJson(UNKNOWN_ENTITY);
                break;
        }
    }
    this->saveJSON();
    return List::returnJson(code);
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getInfos
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &vtx
 * @return string
 */
string  Controller::j_getInfos(Context &ctx) {
    OBJETS entity_type = (OBJETS)atoi(ctx.getParam("entity_type").c_str());
    int entity_id = ctx.getParam("entity_id").c_str() ? atoi(ctx.getParam("entity_id").c_str()) : -1;
    return this->buildResponse(Rule::fillResultRequestGetInfos(entity_type, entity_id));
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action kill
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_kill(Context &ctx) {
    boost::json::object startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object(), res;

    auto entity_type = (OBJETS)startrek.at("entity_type").as_int64();
    auto entity_id = startrek.at("entity_id").as_int64();

    auto result = this->fillResultRequestKillEntities(entity_type, entity_id);
    string responce = this->buildResponse(result);
    this->killEntities(result);
    this->saveJSON();
    return responce;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action addPnj
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_add_entities(Context &ctx) {
    int id;
    boost::json::array startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_array();
    boost::json::object res, node;
    map<OBJETS, string> _quidams {{HEROS, "heros"}, {PNJ, "pnjs"}, {EVIL, "mechants"}};
    boost::json::object res_array;
    vector<boost::json::object>    entities;
    for (size_t i = 0; i < startrek.size(); i++) entities.push_back(startrek.at(i).as_object());

    for (size_t i = 0; i < startrek.size(); i++) {
        auto array = startrek.at(i).as_object();
        OBJETS type_owner;
        switch ((OBJETS)array.at("entity_type").as_int64()) {
            case PLANETE:
            case MISSION:
            case SPACESHIP:
            case GRADE:
                break;
            case PNJ:
            case HEROS:
            case EVIL:
                if (array.at("id_planet").as_int64() != 0 
                && this->_planetes.find(array.at("id_planet").as_int64()) == this->_planetes.end()) return List::returnJson(UNKNOWN_PLANET);
                if (array.at("id_planet_origin").as_int64() != 0
                && this->_planetes.find(array.at("id_planet_origin").as_int64()) == this->_planetes.end()) return List::returnJson(UNKNOWN_PLANET);
                if (array.at("id_ship").as_int64() != 0
                && this->_flotte.find(array.at("id_ship").as_int64()) == this->_flotte.end()) return List::returnJson(UNKNOWN_SPACESHIP);
                if (array.at("id_grade").as_int64() != 0
                && this->_grades.find(array.at("id_grade").as_int64()) == this->_grades.end()) return List::returnJson(UNKNOWN_GRADE);
                break;
            case ITEM:
                type_owner =  (OBJETS)array.at("type_owner").as_int64();
                if (type_owner != NONE) {
                    switch (type_owner)
                    {
                    case HEROS:
                    case EVIL:
                    case PNJ:
                    case SPACESHIP:
                        if (find(QUIDAMS.begin(), QUIDAMS.end(), type_owner) == QUIDAMS.end()) {
                            if (this->_flotte.find(array.at("id_owner").as_int64()) == this->_flotte.end()) return List::returnJson(UNKNOWN_SPACESHIP);
                        } else {
                            if (this->_quidams[type_owner].find(array.at("id_owner").as_int64()) == this->_quidams[type_owner].end()) return List::returnJson((type_owner == HEROS ? UNKNOWN_HEROS : (type_owner == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)));
                        }
                        
                        break;
                    
                    default:
                        return List::returnJson(MISSING_INVENTORY);
                        break;
                    }
                }
                break;
            default:
                return List::returnJson(UNKNOWN_ENTITY);
                break;
        }
    }
    
    for (size_t i = 0; i < startrek.size(); i++) {
        auto array = startrek.at(i).as_object();
        string key = to_string(array.at("entity_type").as_int64());
        if (!res_array.contains(key)) res_array[key].emplace_array();
        switch (array.at("entity_type").as_int64())
        {
            case HEROS:
            case PNJ:
            case EVIL:
                id = this->addQuidam(array);
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_quidams[(OBJETS)array.at("entity_type").as_int64()][id]->generate(id));
                break;
            case PLANETE:
                id = this->addPlanet(array);
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_planetes[id]->generate(id));
                break;
            case MISSION:
                id = this->addMission(array);;
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_missions[id]->generate(id));
                break;
            case SPACESHIP:
                id = this->addSpaceShip(array);
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_flotte[id]->generate(id));
                break;
            case ITEM:
                id = this->addItem(array);
                switch ((OBJETS)array.at("type_owner").as_int64())
                {
                case HEROS:
                case PNJ:
                case EVIL:
                    res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_quidams[(OBJETS)array.at("type_owner").as_int64()][array.at("id_owner").as_int64()]->getInventory()[id]->generate(id));
                    break;
                case SPACESHIP:
                    res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_flotte[array.at("id_owner").as_int64()]->getInventory()[id]->generate(id));
                    
                case NONE:
                    res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_items[id]->generate(id));
                    break;
                default:
                    break;
                }
                break;
            case GRADE:
                id = this->addGrade(array);
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_grades[id]->generate(id));
                break;
            default:
                break;
        }
    }
    this->saveJSON();
    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"] = res_array;

    return boost::json::serialize(res);
}   

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getHabitants
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_getHabitants(Context &ctx) {
    int id = atoi(ctx.getParam("id_planet").c_str());
    return this->buildResponse(RulePlanete::fillResultGetHabitant(id));
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getEquipage
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_getEquipage(Context &ctx) {
    int id = atoi(ctx.getParam("id_ship").c_str());
    return this->buildResponse(RuleSpaceship::fillResultGetEquipage(id));
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getInventory
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_getInventory(Context &ctx) {
    OBJETS entity_type = (OBJETS)atoi(ctx.getParam("entity_type").c_str());
    int entity_id = atoi(ctx.getParam("entity_id").c_str());
    return this->buildResponse(Rule::fillResultRequestGetInventory(entity_type, entity_id));
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action promote
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_promote(Context &ctx) {
    boost::json::array startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_array();
    boost::json::array pnjs, heros, evils;
    boost::json::object res;
    int entity_id, id_grade;
    OBJETS entity_type;

    for (size_t i = 0; i < startrek.size(); i++) {
        entity_type = (OBJETS)startrek.at(i).as_object().at("entity_type").as_int64();
        entity_id = startrek.at(i).as_object().at("entity_id").as_int64();
        id_grade = startrek.at(i).as_object().at("id_grade").as_int64();
        if (find(QUIDAMS.begin(), QUIDAMS.end(), entity_type) == QUIDAMS.end()) return List::returnJson(MISSING_GRADE);
        if (this->_quidams[entity_type].find(entity_id) == this->_quidams[entity_type].end()) return List::returnJson((entity_type == HEROS ? UNKNOWN_HEROS : (entity_type == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)));
        if (this->_grades.find(id_grade) == this->_grades.end()) return List::returnJson(UNKNOWN_GRADE);
    }
    for (size_t i = 0; i < startrek.size(); i++) {
        entity_type = (OBJETS)startrek.at(i).as_object().at("entity_type").as_int64();
        entity_id = startrek.at(i).as_object().at("entity_id").as_int64();
        id_grade = startrek.at(i).as_object().at("id_grade").as_int64();
        this->promote(id_grade, entity_id, (OBJETS) entity_type);
        switch (entity_type)
        {
            case HEROS:
                heros.push_back(this->_quidams[entity_type][entity_id]->generate(entity_id));
                break;
            case PNJ:
                pnjs.push_back(this->_quidams[entity_type][entity_id]->generate(entity_id));
                break;
            case EVIL:
                evils.push_back(this->_quidams[entity_type][entity_id]->generate(entity_id));
                break;
            default:
                break;
        }
    }
    this->saveJSON();
    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"].as_object()["quidams"].emplace_object();
    res["return"].as_object()["quidams"].as_object()["heros"] = heros;
    res["return"].as_object()["quidams"].as_object()["pnjs"] = pnjs;
    res["return"].as_object()["quidams"].as_object()["evils"] = evils;
    return boost::json::serialize(res);
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getHierarchy
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_getHierarchy(Context &ctx) {
    boost::json::array pnjs, heros, evils;
    boost::json::object res;
    int id = atoi(ctx.getParam("id_grade").c_str());
    return this->buildResponse(RuleGrade::fillResultRequestGetHierarchy(id));
}

string  Controller::j_getToken(Context &ctx) {
    boost::json::object body = boost::json::parse(ctx.getRequest().body()).as_object();
    boost::json::object res;
    shared_ptr<Token> token;
    bool is_OK = true;
    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();

    token = make_shared<Token>((string)body.at("user").as_string().c_str(), (string)body.at("user").as_string().c_str());

    for (auto it: this->_tokens) {
        if (it.second->getToken().compare(token->getToken()) == 0 || it.second->getUser().compare(token->getUser()) == 0) {
            is_OK = false;
            res["return"].as_object()["token"] = it.second->getToken();
            break;
        }
    }
    if (is_OK) {
        int id = this->getMaxId(TOKEN) + 1;
        this->_tokens[id] = token;
        this->saveJSON();
        res["return"].as_object()["token"] = token->getToken();
    } 
    
    return boost::json::serialize(res);
}

string  Controller::buildResponse(ResultRequest result) {
    if (result._code != OK) return List::returnJson(result._code);
    boost::json::object res;

    res["statut"] = "Success";
    res["code"] = OK;
    res["return"].emplace_object();
    if(!result._quidams.empty()) res["return"].as_object()["quidams"].emplace_object();
    for (auto q = result._quidams.begin(); q != result._quidams.end(); q++) {
        string typeStr = q->first == HEROS ? "heros" : (q->first == PNJ ? "pnjs" : "evils");
        if (!q->second.empty()) res["return"].as_object()["quidams"].as_object()[typeStr].emplace_array();
        for (auto it = q->second.begin(); it != q->second.end(); it++) {
            res["return"].as_object()["quidams"].as_object()[typeStr].as_array().push_back(it->second->generate(it->first));
        }
        
    }
    if(!result._items.empty()) res["return"].as_object()["items"].emplace_array();
    for (auto it = result._items.begin(); it != result._items.end(); it++) {
        res["return"].as_object()["items"].as_array().push_back(it->second->generate(it->first));
    }
    if(!result._missions.empty()) res["return"].as_object()["missions"].emplace_array();
    for (auto it = result._missions.begin(); it != result._missions.end(); it++) {
        res["return"].as_object()["missions"].as_array().push_back(it->second->generate(it->first));
    }
    if(!result._planetes.empty()) res["return"].as_object()["planetes"].emplace_array();
    for (auto it = result._planetes.begin(); it != result._planetes.end(); it++) {
        res["return"].as_object()["planetes"].as_array().push_back(it->second->generate(it->first));
    }
    if(!result._spaceships.empty()) res["return"].as_object()["spaceships"].emplace_array();
    for (auto it = result._spaceships.begin(); it != result._spaceships.end(); it++) {
        res["return"].as_object()["spaceships"].as_array().push_back(it->second->generate(it->first));
    }
    if(!result._grades.empty()) res["return"].as_object()["grades"].emplace_array();
    for (auto it = result._grades.begin(); it != result._grades.end(); it++) {
        res["return"].as_object()["grades"].as_array().push_back(it->second->generate(it->first));
    }
    return boost::json::serialize(res);
}
