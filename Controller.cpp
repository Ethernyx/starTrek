/**
* File: Controller.cpp
* Project: star_strek
* File Created: Monday, 24th July 2023 11:31:29 am
* Author: LALIN Romain 
* -----
* Last Modified: Thursday, 27th July 2023 10:46:47 pm
* Modified By: LALIN Romain
* -----
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

map<int, shared_ptr<Spaceship>> &Controller::getFlotte()
{
    return this->_flotte;
}

map<int, shared_ptr<AQuidam>> &Controller::getPersos()
{
    return this->_quidams[HEROS];
}
map<int, shared_ptr<AQuidam>> &Controller::getPnjs()
{   
    return this->_quidams[PNJ];
}

map<int, shared_ptr<AQuidam>> &Controller::getEvils()
{   
    return this->_quidams[EVIL];
}

map<int, shared_ptr<Planete>> &Controller::getPlanetes()
{
    return this->_planetes;
}

map<int, shared_ptr<Mission>> &Controller::getMissions()
{
    return this->_missions;
}

map<int, unique_ptr<Item>> &Controller::getItems()
{
    return this->_items;
}

map<int, shared_ptr<Grade>> &Controller::getGrades()
{
    return this->_grades;
}

vector<string> Controller::getItems(bool isAffected)
{
    vector<string> items;

    if (!isAffected) for (auto c : this->_tableDeCorrespondance[NONE]) items.push_back(this->_items[c.first]->getName());
    if (isAffected) {
        for (auto c : this->_tableDeCorrespondance[HEROS]) items.push_back(this->_quidams[HEROS][c.second]->getInventory()[c.first]->getName());
        for (auto c : this->_tableDeCorrespondance[PNJ]) items.push_back(this->_quidams[PNJ][c.second]->getInventory()[c.first]->getName());
        for (auto c : this->_tableDeCorrespondance[SPACESHIP]) items.push_back(this->_flotte[c.second]->getInventory()[c.first]->getName());
    }
    return items;
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

// suppression de la planete par son nom
// cette methode fait appel a la methode ci-dessous qui supprime une planete par son ID
bool Controller::deletePlanete(string const name)
{
    for (auto pl : this->_planetes)
    {
        if (pl.second->getName() == name)
        {
            this->deletePlanete(pl.first);
            return true;
        }
    }
    return false;
}
// surcharge de la methode de suppression
bool Controller::deletePlanete(int const id_planet)
{
    auto it = this->_planetes.find(id_planet);
    if (it == this->_planetes.end())
        return false;

    for (auto p : this->_quidams[HEROS])
    {
        if (it->first == p.second->getIdPlanetOrigin())
        {
            p.second->setIdPlanetOrigin(0);
        }
        if (it->first == p.second->getIdPlanet())
        {
            deletePerso(p.first);
        }
    }
    this->_planetes.erase(it);
    return true;
}

bool Controller::deleteMission(string const name)
{
    for (auto m : this->_missions)
    {
        if (m.second->getName() == name)
        {
            this->deleteMission(m.first);
            return true;
        }
    }
    return false;
}
bool Controller::deleteMission(int const id)
{
    auto it = this->_missions.find(id);
    if (it == this->_missions.end())
        return false;
    this->_missions.erase(it);
    return true;
}

bool Controller::deleteSpaceship(string const name)
{
    for (auto s : this->_flotte)
    {
        if (s.second->getName() == name)
        {
            this->deleteSpaceship(s.first);
            return true;
        }
    }
    return false;
}
// surcharge de la methode de suppression
bool Controller::deleteSpaceship(const int id_ship)
{
    auto it = this->_flotte.find(id_ship);
    if (it == this->_flotte.end())
        return false;
    for (auto p : this->_quidams[HEROS])
    {
        if (it->first == p.second->getIdShip())
        {
            deletePerso(p.first);
        }
    }
    for (auto i =  it->second->getInventory().begin(); i !=  it->second->getInventory().end(); i++) this->removeItem(i->first, it->second->getName(), SPACESHIP);
    this->_flotte.erase(it);
    return true;
}

bool Controller::deletePerso(string const name)
{
    for (auto p : this->_quidams[HEROS])
    {
        if (p.second->getName() == name)
        {
            this->deletePerso(p.first);
            return true;
        }
    }
    return false;
}
// surcharge de la methode de suppression
bool Controller::deletePerso(const int id)
{
    OBJETS type;
    auto it = this->_quidams[HEROS].find(id);
    type = HEROS;
    if (it == this->_quidams[HEROS].end()) { // si pas trouvé dans perso
        it = this->_quidams[PNJ].find(id);
        type = PNJ;
        if (it == this->_quidams[HEROS].end()) return false; // si pas trouvé non plus dans pnj
    }
    
    /* je m'occupe des items que possède le perso/pnj */
    if (it->second->getInventory().size() > 0) {
        for (auto i = it->second->getInventory().begin(); i != it->second->getInventory().end(); i++) {
            this->removeItem(i->first, it->second->getName(), type);
        }
    }

    /* je check le type pour savoir ou je dois mettre le nullptr*/
    if (type == HEROS) this->_quidams[HEROS][id] = nullptr;
    else this->_quidams[PNJ][id] = nullptr;

    for (auto &p : this->_planetes)
        p.second->cleanHabitants();
    for (auto &f : this->_flotte)
        f.second->cleanEquipage();
    for (auto &g : this->_grades)
        g.second->cleanMembres();

    /* je check le type pour savoir ou je dois erase*/
    if (type == HEROS) this->_quidams[HEROS].erase(it);
    else this->_quidams[PNJ].erase(it);
    return true;
}

int Controller::addQuidam(const string name, const int puissance, const int sante, const int dp, const int id_planet, const int id_ship, const int id_planete_origine, const int id_grade, OBJETS type)
{
    int id = this->getMaxId(type) + 1;
    switch (type)
    {
        case HEROS:
            this->_quidams[type][id] = make_shared<Heros>(name, puissance, sante, dp, id_planet, id_ship, id_planete_origine, id_grade);
            break;
        case PNJ:
            this->_quidams[type][id] = make_shared<Pnj>(name, puissance, sante, dp, id_planet, id_ship, id_planete_origine, id_grade);
            break;
        case EVIL:
            this->_quidams[type][id] = make_shared<Evil>(name, puissance, sante, dp, id_planet, id_ship, id_planete_origine, id_grade);
            break;
        default:
            break;
    }
    if (id_ship != 0 && this->_flotte[id_ship]) this->_flotte[id_ship]->addEquipage(this->_quidams[type][id]);
    if (id_planet != 0 && this->_planetes[id_planet]) this->_planetes[id_planet]->setHabitant(this->_quidams[type][id]);
    if (id_grade != 0 && this->_grades[id_grade]) this->_grades[id_grade]->addMembre(this->_quidams[type][id]);  
    return id;
}
int Controller::addPnj(const string name, const int puissance, const int sante, const int dp, const int id_planet, const int id_ship, const int id_planete_origine, const int id_grade) {
    int id = this->getMaxId(PNJ) + 1;
    this->_quidams[PNJ][id] = make_shared<Pnj>(name, puissance, sante, dp, id_planete_origine, id_ship, id_planet, id_grade);
    if (id_ship != 0 && this->_flotte[id_ship]) this->_flotte[id_ship]->addEquipage(this->_quidams[PNJ][id]);
    if (id_planet != 0 && this->_planetes[id_planet]) this->_planetes[id_planet]->setHabitant(this->_quidams[PNJ][id]);
    return id;
}

int Controller::addPlanet(const string name, const string description)
{
    int id = this->getMaxId(PLANETE) + 1;
    this->_planetes[id] = make_shared<Planete>(name, description);
    return id;
}
int Controller::addSpaceShip(const std::string name, const std::string description, int ap, int hp, int dp)
{
    int id = this->getMaxId(SPACESHIP) + 1;
    this->_flotte[id] = make_shared<Spaceship>(name, description, ap, hp, dp);
    return id;
}
int Controller::addMission(const std::string name, const std::string description)
{
    int id = this->getMaxId(MISSION) + 1;
    this->_missions[id] = make_shared<Mission>(name, description, false);
    return id;
}

int Controller::attaqueSimple(OBJETS type_attaquant, const int id_attaquant, OBJETS type_victime,const int id_victime)
{
    switch (type_attaquant)
    {
        case HEROS:
        case PNJ:
        {
            auto a = type_attaquant == HEROS ? this->_quidams[HEROS][id_attaquant] : this->_quidams[PNJ][id_attaquant];
            auto v = type_victime == HEROS ? this->_quidams[HEROS][id_victime] : this->_quidams[PNJ][id_victime];

            if (a == nullptr || v == nullptr)
                return -1;
            v->setAttributs(v->getDp(), v->getHp() - (a->getAp() - v->getDp()), v->getDp()); // HP vic - (attack AP - vi DP)
            if (v->getHp() <= 0)
                return 1;
        }
            break;
        case SPACESHIP:
        {
            auto a = this->_flotte[id_attaquant];
            auto v = this->_flotte[id_victime];

            if (a == nullptr || v == nullptr)
                return -1;
            v->setAttributs(v->getDp(), v->getHp() - (a->getAp() - v->getDp()), v->getDp()); // HP vic - (attack AP - vi DP)
            if (v->getHp() <= 0)
                return 1;
        }
            break;
        default:
            break;
    }
    return 0;
}

shared_ptr<AQuidam> Controller::getPerso(const string name)
{
    for (auto p : this->_quidams[HEROS])
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    for (auto p : this->_quidams[PNJ])
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}
shared_ptr<Spaceship> Controller::getSpaceship(const string name)
{
    for (auto p : this->_flotte)
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}
shared_ptr<Mission> Controller::getMission(const string name)
{
    for (auto p : this->_missions)
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}
shared_ptr<Planete> Controller::getPlanete(const string name)
{
    for (auto p : this->_planetes)
    {
        if (p.second->getName() == name)
        {
            return p.second;
        }
    }
    return nullptr;
}

void    Controller::takeItem(const int item, const int owner, OBJETS type) {
    switch (type)
    {
        case HEROS:
            if (this->_items[item]) this->_quidams[HEROS][owner]->addItem(this->_items[item], item);
            this->_quidams[HEROS][owner]->getInventory()[item]->setOwner(owner, type);
            break;
        case PNJ:
            this->_quidams[PNJ][owner]->addItem(this->_items[item], item);
            this->_quidams[PNJ][owner]->getInventory()[item]->setOwner(owner, type);
            break;
        case SPACESHIP:
            this->_flotte[owner]->addItem(this->_items[item], item);
            this->_flotte[owner]->getInventory()[item]->setOwner(owner, type);
            break;
        default:
            break;
    }
    /* j'erase l'ancienne corespondance */
    this->_tableDeCorrespondance[NONE].erase(this->_tableDeCorrespondance[NONE].find(item));
    /* j'ajoute la nouvelle */
    this->_tableDeCorrespondance[type][item] = owner;
}

void    Controller::removeItem(int idItem, string name, OBJETS type) {
    if (type == SPACESHIP) this->_items[idItem].swap(this->getSpaceship(name)->getInventory()[idItem]);
    else this->_items[idItem].swap(this->getPerso(name)->getInventory()[idItem]);
    /* je set le owner */
    this->_items[idItem]->setOwner(0, NONE);
    /* j'erase l'ancienne corespondance */
    this->_tableDeCorrespondance[type].erase(this->_tableDeCorrespondance[type].find(idItem));
    /* j'ajoute la nouvelle */
    this->_tableDeCorrespondance[NONE][idItem] = 0;
}

int Controller::addItem(const string name, const int stat, const EFFECT effect, const int id_owner, const OBJETS type) {
    int id = this->getMaxId(ITEM) + 1;
    this->_items[id] = make_unique<Item>(name, stat, effect, id_owner, type);
    this->_tableDeCorrespondance[type][id] = id_owner;
    if (id_owner != 0) {
        switch (type)
        {
        case HEROS:
        case EVIL:
        case PNJ:
            this->_quidams[type][id_owner]->addItem(this->_items[id], id);
            break;
        case SPACESHIP:
            this->_flotte[id_owner]->addItem(this->_items[id], id);
            break;
        default:
            break;
        }
    }
    return id;
}

void    Controller::deleteItem(int id) {
for (auto type : this->_tableDeCorrespondance) for (auto it : type.second) if (it.first == id) {
        switch (type.first)
        {
            case HEROS:
            case PNJ:
            case EVIL:
                this->_quidams[(OBJETS)type.first][it.second]->getInventory().erase(this->_quidams[(OBJETS)type.first][it.second]->getInventory().find(it.first));
                break;
            case SPACESHIP:
                this->_flotte[it.second]->getInventory().erase(this->_flotte[it.second]->getInventory().find(it.first));
            case NONE:
                this->_items.erase(this->_items.find(id));
            default:
                break;
        }
    }
}

void    Controller::promote(int id_grade, int id_entity, OBJETS entity_type) {
    this->_quidams[entity_type][id_entity]->setIdGrade(id_grade);
    this->_grades[id_grade]->addMembre(this->_quidams[HEROS][id_entity]);
}

void    Controller::removeGrade(int id_entity, OBJETS entity_type) {
    switch (entity_type)
    {
    case HEROS:
        this->_grades[this->_quidams[HEROS][id_entity]->getIdGrade()]->deleteMembre(this->_quidams[HEROS][id_entity]->getName());
        break;
    case PNJ:
        this->_grades[this->_quidams[PNJ][id_entity]->getIdGrade()]->deleteMembre(this->_quidams[PNJ][id_entity]->getName());
    default:
        break;
    }
}

int     Controller::addGrade(const string name, const int level) {
    int id = this->getMaxId(GRADE) + 1;
    this->_grades[id] = make_shared<Grade>(name, level);
    return id;
}

bool    Controller::deleteGrade(const int id) {
    auto it = this->_grades.find(id);

    if (it == this->_grades.end()) return false;
    
    for (auto i = this->_quidams[HEROS].begin(); i != this->_quidams[HEROS].end();i++) if (i->second->getIdGrade() == it->first) i->second->setIdGrade(0);
    for (auto i = this->_quidams[PNJ].begin(); i != this->_quidams[PNJ].end();i++) if (i->second->getIdGrade() == it->first) i->second->setIdGrade(0);

    this->_grades.erase(it);
    return true;
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
                    if (elem.second->getIdShip() == g.first)
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
    char *retour = NULL;
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

    auto startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object();
    boost::json::object res, node;
    OBJETS entity_type = (OBJETS)startrek.at("entity_type").as_int64();
    int entity_id = -1;
    if (startrek.contains("entity_id")) entity_id = startrek.at("entity_id").as_int64(); 

    node["entity_type"] = entity_type;
    node["entities"].emplace_array();
    switch(entity_type) {
        case PLANETE:
            if(entity_id == -1) {
                if (this->_planetes.find(entity_id) == this->_planetes.end()) return List::returnJson(UNKNOWN_PLANET);
                node["entities"].get_array().push_back(this->_planetes[entity_id]->generate(entity_id));
                return boost::json::serialize(res);
            }
            for(auto p: this->_planetes) {
                node["entities"].get_array().push_back(p.second->generate(p.first));
            }
            break;
        case LIVING:
            if(entity_id != -1) {
                for (auto living: this->_quidams) {
                    
                    if (living.second.find(entity_id) == living.second.end()) return List::returnJson((living.first == HEROS ? UNKNOWN_HEROS : (living.first == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)));
                    node["entities"].get_array().push_back(living.second[entity_id]->generate(entity_id));
                    return boost::json::serialize(res);
                }
                
            }
            for(auto living: this->_quidams) {
                for (auto l: living.second) {
                    node["entities"].get_array().push_back(l.second->generate(l.first));
                }
            }
            break;
        case HEROS:
        case EVIL:
        case PNJ:
            if(entity_id != -1) {
                if (this->_quidams[entity_type].find(entity_id) == this->_quidams[entity_type].end()) return List::returnJson((entity_type == HEROS ? UNKNOWN_HEROS : (entity_type == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)));
                node["entities"].get_array().push_back(this->_quidams[entity_type][entity_id]->generate(entity_id));
                break;
            }
            for(auto p: this->_quidams[entity_type]) {
                node["entities"].get_array().push_back(p.second->generate(p.first));
            }
            break;
        case MISSION:
            if(entity_id != -1) {
                if (this->_missions.find(entity_id) == this->_missions.end()) return List::returnJson(UNKNOWN_MISSION);
                node["entities"].get_array().push_back(this->_missions[entity_id]->generate(entity_id));
                break;
            }
            for(auto p: this->_missions) {
                node["entities"].get_array().push_back(p.second->generate(p.first));
            }
            break;
        case SPACESHIP:
            if(entity_id != -1) {
                if (this->_flotte.find(entity_id) == this->_flotte.end()) return List::returnJson(UNKNOWN_SPACESHIP);
                node["entities"].get_array().push_back(this->_flotte[entity_id]->generate(entity_id));
                break;
            }
            for(auto p: this->_flotte) {
                node["entities"].get_array().push_back(p.second->generate(p.first));
            }
            break;
        case ITEM:
            for (auto i : this->_tableDeCorrespondance) { // comme fonctionnement par unique_ptr on prend la table des corespondances
                if (i.first == HEROS || i.first == PNJ || i.first == EVIL) {
                    for (auto p : i.second) { // ceux assignés à un quidam
                        if(entity_id != -1) {
                            if (this->_quidams[(OBJETS)i.first][p.second]->getInventory().find(entity_id) == this->_quidams[(OBJETS)i.first][p.second]->getInventory().end()) return List::returnJson(UNKNOWN_ITEM);
                            node["entities"].get_array().push_back(this->_quidams[(OBJETS)i.first][p.second]->getInventory()[entity_id]->generate(entity_id));
                            break;
                        }
                        node["entities"].get_array().push_back(this->_quidams[(OBJETS)i.first][p.second]->getInventory()[p.first]->generate(p.first));
                    }
                }
                if (i.first == SPACESHIP) {
                    for (auto s : i.second) { // ceux assignés à un vaisseau
                        if(entity_id != -1) {
                            if (this->_flotte[s.second]->getInventory().find(entity_id) ==  this->_flotte[s.second]->getInventory().end()) return List::returnJson(UNKNOWN_ITEM);
                            node["entities"].get_array().push_back(this->_flotte[s.second]->getInventory()[entity_id]->generate(entity_id));
                            break;
                        }
                        node["entities"].get_array().push_back(this->_flotte[s.second]->getInventory()[s.first]->generate(s.first));
                    }
                }
                if (i.first == NONE) {
                    for (auto s : i.second) { // ceux assignés à personne
                        cout << s.first << endl;
                        if(entity_id != -1) {
                            if (this->_items.find(entity_id) ==  this->_items.end()) return List::returnJson(UNKNOWN_ITEM);
                            node["entities"].get_array().push_back(this->_items[entity_id]->generate(entity_id));
                            break;
                        }
                        node["entities"].get_array().push_back(this->_items[s.first]->generate(s.first));
                    }
                }
            }
            break;
        case GRADE:
            if(entity_id != -1) {
                if (this->_grades.find(entity_id) == this->_grades.end())  return List::returnJson(UNKNOWN_GRADE);
                node["entities"].get_array().push_back(this->_grades[entity_id]->generate(entity_id));
                break;
            }
            for(auto p: this->_grades) {
                node["entities"].get_array().push_back(p.second->generate(p.first));
            }
            break;
        default:
            break;
    }
     res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"] = node;
    return boost::json::serialize(res);

}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action kill
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_kill(Context &ctx) {
    boost::json::array heros, pnjs, evils, inv;
    boost::json::object startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object(), res;
    int code;

    auto entity_type = (OBJETS)startrek.at("entity_type").as_int64();
    auto entity_id = startrek.at("entity_id").as_int64();

    switch (entity_type) {
        case PLANETE:
            if (this->_planetes.find(entity_id) == this->_planetes.end()) return List::returnJson(UNKNOWN_PLANET);
            for (auto h = this->_planetes[entity_id]->getHabitants().begin(); h != this->_planetes[entity_id]->getHabitants().end(); h++) {
                if (h->lock()) {
                    // je remplis mon array de perso ou pnj qui vont mourir avec la planete
                    for (auto p = this->_quidams[h->lock()->getType()].begin(); p != this->_quidams[h->lock()->getType()].end(); p++) {
                        if (p->second == h->lock()) {
                            switch (p->second->getType())
                            {
                                case HEROS:
                                    heros.push_back(p->second->generate(p->first));
                                    break;
                                case PNJ:
                                    pnjs.push_back(p->second->generate(p->first));
                                    break;
                                case EVIL:
                                    evils.push_back(p->second->generate(p->first));
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }

                // recuperation des ID de l'inventaire
                for (auto i = h->lock()->getInventory().begin(); i != h->lock()->getInventory().end(); i++) inv.push_back(i->second->generate(i->first));
            }
            this->deletePlanete(entity_id);
            break;
        case HEROS:
        case PNJ:
        case EVIL:
            //recuperation des ID de l'inventaire
            if (this->_quidams[entity_type].find(entity_id) == this->_quidams[entity_type].end()) return List::returnJson((entity_type == HEROS ? UNKNOWN_HEROS : (entity_type == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)));
            for (auto it = this->_quidams[entity_type][entity_id]->getInventory().begin(); it != this->_quidams[entity_type][entity_id]->getInventory().end(); it++) {
                inv.push_back(it->second->generate(it->first));
            }
            this->deletePerso(entity_id);
            break;
        case MISSION:
            if (this->_missions.find(entity_id) == this->_missions.end()) return List::returnJson(UNKNOWN_MISSION);
            this->deleteMission(entity_id);
            break;
        case SPACESHIP:
            if (this->_flotte.find(entity_id) == this->_flotte.end()) return List::returnJson(UNKNOWN_SPACESHIP);
            for(auto it = this->_flotte[entity_id]->getEquipage().begin(); it != this->_flotte[entity_id]->getEquipage().end(); it++) {
                if (it->lock()) {
                    for (auto p = this->_quidams[it->lock()->getType()].begin(); p != this->_quidams[it->lock()->getType()].end(); p++) {
                        if (p->second == it->lock()) {
                            switch (p->second->getType())
                            {
                                case HEROS:
                                    heros.push_back(p->second->generate(p->first));
                                    break;
                                case PNJ:
                                    pnjs.push_back(p->second->generate(p->first));
                                    break;
                                case EVIL:
                                    evils.push_back(p->second->generate(p->first));
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
            for (auto it = this->_flotte[entity_id]->getInventory().begin(); it != this->_flotte[entity_id]->getInventory().end(); it++) inv.push_back(it->second->generate(it->first));
            this->deleteSpaceship(entity_id);
            break;
        case GRADE:
            if (this->_grades.find(entity_id) == this->_grades.end()) return List::returnJson(UNKNOWN_GRADE);
            this->deleteGrade(entity_id);
            break;
        case ITEM:
            code = UNKNOWN_ITEM;
            for (auto type : this->_tableDeCorrespondance) for (auto it : type.second) if (it.first == entity_id) {
                this->deleteItem(entity_id);
                code = 0;
            }
            if (code != 0) List::returnJson(code);
            break;        
        default:
            return List::returnJson(UNKNOWN_ENTITY);
            break;
    }
    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"].as_object()["quidams"].emplace_object();
    res["return"].as_object()["quidams"].as_object()["heros"] = heros;
    res["return"].as_object()["quidams"].as_object()["pnjs"] = pnjs;
    res["return"].as_object()["quidams"].as_object()["evils"] = evils;
    res["return"].as_object()["objets"] = inv;
    this->saveJSON();
    return boost::json::serialize(res);
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
        switch (array.at("entity_type").as_int64())
        {
            case HEROS:
            case PNJ:
            case EVIL:
                id = this->addQuidam(
                    array.at("name").as_string().c_str(),
                    array.at("ap").as_int64(),
                    array.at("hp").as_int64(),
                    array.at("dp").as_int64(),
                    array.at("id_planet").as_int64(),
                    array.at("id_ship").as_int64(),
                    array.at("id_planet_origin").as_int64(),
                    array.at("id_grade").as_int64(),
                    (OBJETS)array.at("entity_type").as_int64());
                if (res_array.at(to_string(array.at("entity_type").as_int64())).as_object() == NULL) res_array.at(to_string(array.at("entity_type").as_int64())).emplace_array();
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_quidams[(OBJETS)array.at("entity_type").as_int64()][id]->generate(id));
                break;
            case PLANETE:
                id = this->addPlanet(
                    array.at("name").as_string().c_str(),
                    array.at("description").as_string().c_str()
                    );
                if (res_array.at(to_string(array.at("entity_type").as_int64())).as_object() == NULL) res_array.at(to_string(array.at("entity_type").as_int64())).emplace_array();
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_planetes[id]->generate(id));
                break;
            case MISSION:
                id = this->addMission(
                    array.at("name").as_string().c_str(),
                    array.at("description").as_string().c_str()
                    );

                if (res_array.at(to_string(array.at("entity_type").as_int64())).as_object() == NULL) res_array.at(to_string(array.at("entity_type").as_int64())).emplace_array();
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_missions[id]->generate(id));
                break;
            case SPACESHIP:
                id = this->addSpaceShip(
                    array.at("name").as_string().c_str(),
                    array.at("description").as_string().c_str(),
                    array.at("ap").as_int64(),
                    array.at("hp").as_int64(),
                    array.at("dp").as_int64()
                    );
                if (res_array.at(to_string(array.at("entity_type").as_int64())).as_object() == NULL) res_array.at(to_string(array.at("entity_type").as_int64())).emplace_array();
                res_array.at(to_string(array.at("entity_type").as_int64())).as_array().push_back(this->_flotte[id]->generate(id));
                break;
            case ITEM:
                id = this->addItem(
                    array.at("name").as_string().c_str(),
                    array.at("stat").as_int64(),
                    (EFFECT)array.at("effect").as_int64(),
                    array.at("id_owner").as_int64(),
                    (OBJETS)array.at("type_owner").as_int64()
                    );
                if (res_array.at(to_string(array.at("entity_type").as_int64())).as_object() == NULL) res_array.at(to_string(array.at("entity_type").as_int64())).emplace_array();
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
                id = this->addGrade(
                    array.at("name").as_string().c_str(),
                    array.at("level").as_int64()
                    );
                    if (res_array.at(to_string(array.at("entity_type").as_int64())).as_object() == NULL) res_array.at(to_string(array.at("entity_type").as_int64())).emplace_array();
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

int Controller::getMaxId(OBJETS type) {
    int id = 0;
    switch (type)
    {
    case PLANETE:
        for (auto it = this->_planetes.begin(); it != this->_planetes.end(); it++) if (id < it->first) id = it->first;
        break;
    case SPACESHIP:
        for (auto it = this->_flotte.begin(); it != this->_flotte.end(); it++) if (id < it->first) id = it->first;
        break;
    case HEROS:
    case PNJ:
    case EVIL:
        for (auto it = this->_quidams[type].begin(); it != this->_quidams[type].end(); it++) if (id < it->first) id = it->first;
        break;
    case MISSION:
        for (auto it = this->_missions.begin(); it != this->_missions.end(); it++) if (id < it->first) id = it->first;
        break;
    case ITEM:
        for (auto i = this->_tableDeCorrespondance.begin(); i != this->_tableDeCorrespondance.end(); i++) for (auto it = i->second.begin(); it != i->second.end(); it++) if (id < it->first) id = it->first;
        break;
    case GRADE:
        for (auto it = this->_grades.begin(); it != this->_grades.end(); it++) if (id < it->first) id = it->first;
        break;
    default:
        break;
    }
    
    return id;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getHabitants
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_getHabitants(Context &ctx) {
    boost::json::object startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object();
    boost::json::array pnjs, heros, evils;
    boost::json::object res;

    int id = startrek.at("id_planet").as_int64();
    if (this->_planetes.find(id) == this->_planetes.end()) return List::returnJson(UNKNOWN_PLANET);

    for (auto h : this->_planetes[id]->getHabitants()) {
        if (!h.lock()) continue;

        int id_h = 0;
        switch (h.lock()->getType())
        {
        case PNJ:
            for (auto p : this->_quidams[PNJ]) if (p.second == h.lock()) pnjs.push_back(h.lock()->generate(p.first));
            break;
        case HEROS:
            for (auto p : this->_quidams[HEROS]) if (p.second == h.lock()) heros.push_back(h.lock()->generate(p.first));
            break;
        case EVIL:
            for (auto p : this->_quidams[EVIL]) if (p.second == h.lock()) evils.push_back(h.lock()->generate(p.first));
            break;
        default:
            break;
        }
    }
    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"].as_object()["id_planet"] = id;
    res["return"].as_object()["quidams"].emplace_object();
    res["return"].as_object()["quidams"].as_object()["heros"] = heros;
    res["return"].as_object()["quidams"].as_object()["pnjs"] = pnjs;
    res["return"].as_object()["quidams"].as_object()["evils"] = evils;
    return boost::json::serialize(res);
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getEquipage
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param Context &ctx
 * @return string
 */
string  Controller::j_getEquipage(Context &ctx) {
    boost::json::object startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object();
    boost::json::array pnjs, heros, evils;
    boost::json::object res;

    int id = startrek.at("id_ship").as_int64();
    if (this->_flotte.find(id) == this->_flotte.end()) return List::returnJson(UNKNOWN_SPACESHIP);
    
   for (auto h : this->_flotte[id]->getEquipage()) {
        if (!h.lock()) continue;

        int id_h = 0;
        switch (h.lock()->getType())
        {
        case PNJ:
            for (auto p : this->_quidams[PNJ]) if (p.second == h.lock()) pnjs.push_back(h.lock()->generate(p.first));
            break;
        case HEROS:
            for (auto p : this->_quidams[HEROS]) if (p.second == h.lock()) heros.push_back(h.lock()->generate(p.first));
            break;
        case EVIL:
            for (auto p : this->_quidams[EVIL]) if (p.second == h.lock()) evils.push_back(h.lock()->generate(p.first));
            break;
        default:
            break;
        }
    }

    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"].as_object()["id_ship"] = id;
    res["return"].as_object()["quidams"].emplace_object();
    res["return"].as_object()["quidams"].as_object()["heros"] = heros;
    res["return"].as_object()["quidams"].as_object()["pnjs"] = pnjs;
    res["return"].as_object()["quidams"].as_object()["evils"] = evils;
    return boost::json::serialize(res);
}
string  Controller::j_getInventory(Context &ctx) {
    boost::json::object startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object();
    boost::json::array obj;
    boost::json::object res;
    OBJETS entity_type = (OBJETS)startrek.at("entity_type").as_int64();
    int entity_id = startrek.at("entity_id").as_int64();
    switch (entity_type)
    {
        case HEROS:
        case EVIL:
        case PNJ:
            if (this->_quidams[entity_type].find(entity_id) == this->_quidams[entity_type].end()) return List::returnJson((entity_type == HEROS ? UNKNOWN_HEROS : (entity_type == PNJ ? UNKNOWN_PNJ : UNKNOWN_EVIL)));
            break;
        case SPACESHIP:
            if (this->_flotte.find(entity_id) == this->_flotte.end()) return List::returnJson(UNKNOWN_SPACESHIP);
            break;
        case MISSION:
        case ITEM:
        case PLANETE:
        case GRADE:
            return List::returnJson(MISSING_INVENTORY);
            break;
        default:
            return List::returnJson(UNKNOWN_ENTITY);
            break;
    }

    switch(entity_type) {
        case HEROS:
        case PNJ:
        case EVIL:
            for (auto c : this->_tableDeCorrespondance[entity_type]) {
                if (c.second != entity_id) continue;
                obj.push_back(this->_quidams[entity_type][c.second]->getInventory()[c.first]->generate(c.first));
            }
            break;
        case SPACESHIP:
            for (auto c : this->_tableDeCorrespondance[SPACESHIP]) {
                if (c.second != entity_id) continue;
                obj.push_back(this->_flotte[c.second]->getInventory()[c.first]->generate(c.first));
            }
            break;
        default:
            break;
    }


    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"].as_object()["entity_type"] = entity_type;
    res["return"].as_object()["entity_id"] = entity_id;
    res["return"].as_object()["object"].emplace_array();
    res["return"].as_object()["object"].as_array() = obj;
    return boost::json::serialize(res);
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
    char *print;
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
    boost::json::object startrek = boost::json::parse(ctx.getRequest().body()).as_object().at("startrek").as_object();
    boost::json::array pnjs, heros, evils;
    boost::json::object res;

    int id = startrek.at("id_grade").as_int64();
    if (this->_grades.find(id) == this->_grades.end()) return List::returnJson(UNKNOWN_GRADE);
    for (auto h : this->_grades[id]->getMembre()) {
        if (!h.lock()) continue;

        int id_h = 0;
        switch (h.lock()->getType())
        {
        case PNJ:
            for (auto p : this->_quidams[PNJ]) if (p.second == h.lock()) pnjs.push_back(h.lock()->generate(p.first));
            break;
        case HEROS:
            for (auto p : this->_quidams[HEROS]) if (p.second == h.lock()) heros.push_back(h.lock()->generate(p.first));
            break;
        case EVIL:
            for (auto p : this->_quidams[EVIL]) if (p.second == h.lock()) evils.push_back(h.lock()->generate(p.first));
            break;
        default:
            break;
        }
    }

    res["statut"] = "Success";
    res["code"] = 0;
    res["return"].emplace_object();
    res["return"].as_object()["id_grade"] = id;
    res["return"].as_object()["quidams"].emplace_object();
    res["return"].as_object()["quidams"].as_object()["heros"] = heros;
    res["return"].as_object()["quidams"].as_object()["pnjs"] = pnjs;
    res["return"].as_object()["quidams"].as_object()["evils"] = evils;
    return boost::json::serialize(res);
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
