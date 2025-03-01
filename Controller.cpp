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

#include "Controller.hh"

using namespace std;

Controller::Controller()
{
    this->_serveur = new Serveur();
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

Serveur *Controller::getServeur() {
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

    cJSON *root, *startrek, *arr, *node;

    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "startrek", startrek = cJSON_CreateObject());

    /* gestion des planètes */
    cJSON_AddItemToObject(startrek, to_string(PLANETE).c_str(), arr = cJSON_CreateArray());
    for(auto p: this->_planetes) {
        cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
        node = p.second->generate(node, p.first);
    }

    /* gestion des vaisseaux */
    cJSON_AddItemToObject(startrek, to_string(SPACESHIP).c_str(), arr = cJSON_CreateArray());
    for(auto p: this->_flotte) {
        cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
        node = p.second->generate(node, p.first);
    }

    /* gestion des personnages */
    cJSON_AddItemToObject(startrek, to_string(HEROS).c_str(), arr = cJSON_CreateArray());
    for(auto p: this->_quidams[HEROS]) {
        cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
        node = p.second->generate(node, p.first);
    }

    /* gestion des missions */
    cJSON_AddItemToObject(startrek, to_string(MISSION).c_str(), arr = cJSON_CreateArray());
    for(auto p: this->_missions) {
        cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
        node = p.second->generate(node, p.first);
    }

    /* gestion des pnjs */
    cJSON_AddItemToObject(startrek, to_string(PNJ).c_str(), arr = cJSON_CreateArray());
    for(auto p: this->_quidams[PNJ]) {
        cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
        node = p.second->generate(node, p.first);
    }

    /* gestion des items */
    cJSON_AddItemToObject(startrek, to_string(ITEM).c_str(), arr = cJSON_CreateArray());

    for (auto i : this->_tableDeCorrespondance) { // comme fonctionnement par unique_ptr on prend la table des corespondances
        if (i.first == HEROS) for (auto p : i.second) { // ceux assignés à un personnage
                cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
                node = this->_quidams[HEROS][p.second]->getInventory()[p.first]->generate(node, p.first);
            }
        if (i.first == PNJ) for (auto p : i.second) { // ceux assignés à un pnj
                cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
                node = this->_quidams[PNJ][p.second]->getInventory()[p.first]->generate(node, p.first);
            }
        if (i.first == SPACESHIP) for (auto s : i.second) { // ceux assignés à un vaisseau
                cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
                node = this->_flotte[s.second]->getInventory()[s.first]->generate(node, s.first);
            }
        if (i.first == NONE) for (auto s : i.second) { // ceux assignés à personne
                cJSON_AddItemToArray(arr, node = cJSON_CreateObject());
                node = this->_items[s.first]->generate(node, s.first);
            }
    }

    auto out=cJSON_Print(root);
    cJSON_Delete(root);
    FILE *f;
    f = fopen(BDDFILE,"w");
    fprintf(f,"%s\n",out);
    free(out);
    fclose(f);
}

void Controller::init(cJSON *node) {
    cJSON *startrek = cJSON_GetObjectItem(node, "startrek");

    cJSON *items = startrek->child;
    while (items != NULL) {
        for (int i = 0; i < cJSON_GetArraySize(items); i++) {
            cJSON *item = cJSON_GetArrayItem(items, i);
            switch (stoi(items->string))
            {
                case PLANETE:
                    this->_planetes[cJSON_GetObjectItem(item, "id")->valueint] = make_shared<Planete>(item);
                    break;
                case SPACESHIP:
                    this->_flotte[cJSON_GetObjectItem(item, "id")->valueint] = make_shared<Spaceship>(item);
                    break;
                case HEROS:
                    this->_quidams[HEROS][cJSON_GetObjectItem(item, "id")->valueint] = make_shared<Heros>(item);
                    break;
                case PNJ:
                    this->_quidams[PNJ][cJSON_GetObjectItem(item, "id")->valueint] = make_shared<Pnj>(item);
                    break;
                case EVIL:
                    this->_quidams[EVIL][cJSON_GetObjectItem(item, "id")->valueint] = make_shared<Evil>(item);
                    break;
                case MISSION:
                    this->_missions[cJSON_GetObjectItem(item, "id")->valueint] = make_shared<Mission>(item);
                    break;
                case ITEM:
                    this->_items[cJSON_GetObjectItem(item, "id")->valueint] = make_unique<Item>(item);
                    this->_tableDeCorrespondance[cJSON_GetObjectItem(item, "type_owner")->valueint][cJSON_GetObjectItem(item, "id")->valueint] = cJSON_GetObjectItem(item, "id_owner")->valueint;
                    break;
                case GRADE:
                    this->_grades[cJSON_GetObjectItem(item, "id")->valueint] = make_shared<Grade>(item);
                default:
                    cout << "pas planete" << endl;
                    break;
            }

        }
        items = items->next;
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
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action d'attaque
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return string (cJSON_Print())
 */
char *Controller::j_attack(cJSON *startrek) {
    int hp = 0, dead = 0;
    char *retour = NULL;
    cJSON *root, *defenseur, *attaquant, *val;
    defenseur = cJSON_GetObjectItem(startrek, "defenseur");
    attaquant = cJSON_GetObjectItem(startrek, "attaquant");
    root = List::defaultNode();
    val = cJSON_GetObjectItem(root, "return");
    OBJETS typeAttaquant = (OBJETS)cJSON_GetObjectItem(attaquant, "type")->valueint;
    OBJETS typeDefenseur = (OBJETS)cJSON_GetObjectItem(defenseur, "type")->valueint;

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
                dead = this->attaqueSimple((OBJETS)typeAttaquant, cJSON_GetObjectItem(attaquant, "id")->valueint, (OBJETS)typeDefenseur,cJSON_GetObjectItem(defenseur, "id")->valueint);
                if (dead == -1) return List::returnJson(NONE * 100 + 11); // si c'est -1 ça veut dire qu'1 des 2 n'existe pas 
                cJSON_AddItemToObject(val, "id", cJSON_CreateNumber(cJSON_GetObjectItem(defenseur, "id")->valueint));
                cJSON_AddItemToObject(val, "name", cJSON_CreateString(this->_quidams[typeDefenseur][cJSON_GetObjectItem(defenseur, "id")->valueint]->getName().c_str()));
                hp = dead ? 0 : this->_quidams[typeDefenseur][cJSON_GetObjectItem(defenseur, "id")->valueint]->getHp();
                cJSON_AddItemToObject(val, "hp", cJSON_CreateNumber(hp));
                retour = cJSON_Print(root);
                break;
            case SPACESHIP:
                dead = this->attaqueSimple((OBJETS)typeAttaquant, cJSON_GetObjectItem(attaquant, "id")->valueint, (OBJETS)typeDefenseur,cJSON_GetObjectItem(defenseur, "id")->valueint);
                if (dead == -1) return List::returnJson(NONE * 100 + 11);
                cJSON_AddItemToObject(val, "id", cJSON_CreateNumber(cJSON_GetObjectItem(defenseur, "id")->valueint));
                cJSON_AddItemToObject(val, "name", cJSON_CreateString(this->_flotte[cJSON_GetObjectItem(defenseur, "id")->valueint]->getName().c_str()));
                hp = dead ? 0 : this->_flotte[cJSON_GetObjectItem(defenseur, "id")->valueint]->getHp();
                cJSON_AddItemToObject(val, "hp", cJSON_CreateNumber(hp));
                retour = cJSON_Print(root);
                break;
            default:
                retour = List::returnJson(HEROS * 100 + 40);
                break;
        }
    } else retour = List::returnJson(NONE * 100 + 13);
    cJSON_Delete(root); 
    return retour;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action exchangeItem
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char * (cJSON_Print())
 */
char *Controller::j_exchangeItem(cJSON *startrek) {
    cJSON *root;
    root = cJSON_CreateObject();
    int code = 0;

    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto objet = cJSON_GetArrayItem(startrek, i);
        OBJETS type = (OBJETS)cJSON_GetObjectItem(objet, "entity_type")->valueint;
        auto entity_id = cJSON_GetObjectItem(objet, "entity_id")->valueint;
        auto action = cJSON_GetObjectItem(objet, "action")->valuestring;

        switch (type) {
            case HEROS:
            case PNJ:
            case EVIL:
                for (int j = 0; j < cJSON_GetArraySize(cJSON_GetObjectItem(objet, "items")); j++) {
                    auto id_item = cJSON_GetArrayItem(cJSON_GetObjectItem(objet, "items"),j)->valueint;
                    if (this->_quidams[type].find(entity_id) == this->_quidams[type].end()) return List::returnJson(type * 100 + 12);
                    if(strcmp(action,"pull") == 0) {
                        //le perso recupere les items
                        if(this->getPerso(this->_quidams[type].find(entity_id)->second->getName())->getInventory().size() <= this->getPerso(this->_quidams[type].find(entity_id)->second->getName())->getMaxItem()) {
                            if (this->_tableDeCorrespondance[NONE].find(id_item) == this->_tableDeCorrespondance[NONE].end()) return List::returnJson(NONE * 100 + 16);
                            this->takeItem(id_item, entity_id, type);
                        } else return List::returnJson(type * 100 + 11);
                    } else if (strcmp(action, "push") == 0) {
                        if (!(this->_tableDeCorrespondance[type].find(id_item) != this->_tableDeCorrespondance[type].end() && this->_tableDeCorrespondance[type][id_item] == entity_id)) return List::returnJson(type * 100 + 13);
                        this->removeItem(id_item, this->_quidams[type].find(entity_id)->second->getName(), type);
                    } else return List::returnJson(NONE * 100 + 15);
                }
                break;
            case SPACESHIP:
                for (int j = 0; j < cJSON_GetArraySize(cJSON_GetObjectItem(objet, "items")); j++) {
                    auto id_item = cJSON_GetArrayItem(cJSON_GetObjectItem(objet, "items"),j)->valueint;
                    if (this->_flotte.find(entity_id) == this->_flotte.end()) return List::returnJson(type * 100 + 9);
                    if(strcmp(action,"pull") == 0) {
                        //le Spaceship recupere les items
                        if(this->getSpaceship(this->_flotte.find(entity_id)->second->getName())->getInventory().size() <= this->getSpaceship(this->_flotte.find(entity_id)->second->getName())->getMaxItem()) {
                            if (this->_tableDeCorrespondance[NONE].find(id_item) == this->_tableDeCorrespondance[NONE].end()) return List::returnJson(NONE * 100 + 16);
                            this->takeItem(id_item, entity_id, type);
                        } else return List::returnJson(type * 100 + 8);
                    } else if (strcmp(action, "push") == 0) {
                        if (!(this->_tableDeCorrespondance[type].find(id_item) != this->_tableDeCorrespondance[type].end() && this->_tableDeCorrespondance[type][id_item] == entity_id)) return List::returnJson(type * 100 + 10);
                        this->removeItem(id_item, this->_flotte.find(entity_id)->second->getName(), type);
                    } else return List::returnJson(NONE * 100 + 15);
                }
                break;
            default:
                return List::returnJson(NONE * 100 + 14);
                break;
        }
    }
    return List::returnJson(code);
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getInfos
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char * (cJSON_Print())
 */
char *Controller::j_getInfos(cJSON *startrek) {
    char *ret;
    cJSON *root;
    cJSON *entities, *retour, *node;
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "statut", "Success");
    cJSON_AddNumberToObject(root, "code", 0);
    cJSON_AddItemToObject(root, "return", retour = cJSON_CreateObject());

    OBJETS entity_type = (OBJETS)cJSON_GetObjectItem(startrek, "entity_type")->valueint;
    cJSON *entity_id = cJSON_GetObjectItem(startrek, "entity_id");


    cJSON_AddNumberToObject(retour, "entity_type", entity_type);
    cJSON_AddItemToObject(retour, "entities", entities = cJSON_CreateArray());

    switch(entity_type) {
        case PLANETE:
            if(entity_id != NULL) {
                if (this->_planetes.find(entity_id->valueint) == this->_planetes.end()) return List::returnJson(entity_type * 100 + 5);
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = this->_planetes[entity_id->valueint]->generate(node, entity_id->valueint);
                return cJSON_Print(root);
            }
            for(auto p: this->_planetes) {
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = p.second->generate(node, p.first);
            }
            break;
        case LIVING:
            if(entity_id != NULL) {
                for (auto living: this->_quidams) {
                    if (living.second.find(entity_id->valueint) == living.second.end()) return List::returnJson(living.first * 100 + 12);
                    cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                    node = living.second[entity_id->valueint]->generate(node, entity_id->valueint);
                    return cJSON_Print(root);
                }
                
            }
            for(auto living: this->_quidams) {
                for (auto l: living.second) {
                    cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                    cJSON_AddNumberToObject(node, "entity_type", living.first);
                    node = l.second->generate(node, l.first);
                }
            }
            break;
        case HEROS:
        case EVIL:
        case PNJ:
            if(entity_id != NULL) {
                if (this->_quidams[entity_type].find(entity_id->valueint) == this->_quidams[entity_type].end()) return List::returnJson(entity_type * 100 + 12);
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = this->_quidams[entity_type][entity_id->valueint]->generate(node, entity_id->valueint);
                return cJSON_Print(root);
            }
            for(auto p: this->_quidams[entity_type]) {
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = p.second->generate(node, p.first);
            }
            break;
        case MISSION:
            if(entity_id != NULL) {
                if (this->_missions.find(entity_id->valueint) == this->_missions.end()) return List::returnJson(entity_type * 100 + 5);
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = this->_missions[entity_id->valueint]->generate(node, entity_id->valueint);
                return cJSON_Print(root);
            }
            for(auto p: this->_missions) {
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = p.second->generate(node, p.first);
            }
            break;
        case SPACESHIP:
            if(entity_id != NULL) {
                if (this->_flotte.find(entity_id->valueint) == this->_flotte.end()) return List::returnJson(entity_type * 100 + 9);
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = this->_flotte[entity_id->valueint]->generate(node, entity_id->valueint);
                return cJSON_Print(root);
            }
            for(auto p: this->_flotte) {
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                node = p.second->generate(node, p.first);
            }
            break;
        case ITEM:
            for (auto i : this->_tableDeCorrespondance) { // comme fonctionnement par unique_ptr on prend la table des corespondances
                cout << i.first << endl;
                if (i.first == HEROS || i.first == PNJ || i.first == EVIL) {
                    cout << "bad" << endl;
                    for (auto p : i.second) { // ceux assignés à un quidam
                        if(entity_id != NULL) {
                            if (this->_quidams[(OBJETS)i.first][p.second]->getInventory().find(entity_id->valueint) == this->_quidams[(OBJETS)i.first][p.second]->getInventory().end()) return List::returnJson(entity_type * 100 + 8);
                            cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                            node = this->_quidams[(OBJETS)i.first][p.second]->getInventory()[entity_id->valueint]->generate(node, entity_id->valueint);
                            return cJSON_Print(root);
                        }
                        cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                        node = this->_quidams[(OBJETS)i.first][p.second]->getInventory()[p.first]->generate(node, p.first);
                    }
                }
                if (i.first == SPACESHIP) {
                    for (auto s : i.second) { // ceux assignés à un vaisseau
                        if(entity_id != NULL) {
                            if (this->_flotte[s.second]->getInventory().find(entity_id->valueint) ==  this->_flotte[s.second]->getInventory().end()) return List::returnJson(entity_type * 100 + 8);
                            cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                            node = this->_flotte[s.second]->getInventory()[entity_id->valueint]->generate(node, entity_id->valueint);
                            return cJSON_Print(root);
                        }
                        cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                        node = this->_flotte[s.second]->getInventory()[s.first]->generate(node, s.first);
                    }
                }
                if (i.first == NONE) {
                    cout << "tutu" << endl;
                    for (auto s : i.second) { // ceux assignés à personne
                        cout << s.first << endl;
                        if(entity_id != NULL) {
                            if (this->_items.find(entity_id->valueint) ==  this->_items.end()) return List::returnJson(entity_type * 100 + 8);
                            cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                            node = this->_items[entity_id->valueint]->generate(node, entity_id->valueint);
                            return cJSON_Print(root);
                        }
                        cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                        node = this->_items[s.first]->generate(node, s.first);
                    }
                }
            }
            break;
        case GRADE:
            if(entity_id != NULL) {
                if (this->_grades.find(entity_id->valueint) == this->_grades.end())  return List::returnJson(entity_type * 100 + 5);
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                this->_grades[entity_id->valueint]->generate(node, entity_id->valueint);
                return cJSON_Print(root);
            }
            for(auto p: this->_grades) {
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                p.second->generate(node, p.first);
            }
            break;
        default:
            break;
    }
    ret = cJSON_Print(root);
    cJSON_Delete(root);
    return ret;

}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action kill
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char * (cJSON_Print())
 */
char *Controller::j_kill(cJSON *startrek) {
    char *print;
    cJSON *inv = NULL, *perso = NULL, *pnj = NULL, *item, *retour, *root;
    int code;

    auto entity_type = (OBJETS)cJSON_GetObjectItem(startrek, "entity_type")->valueint;
    auto entity_id = cJSON_GetObjectItem(startrek, "entity_id")->valueint;

    switch (entity_type) {
        case PLANETE:
            if (this->_planetes.find(entity_id) == this->_planetes.end()) return List::returnJson(entity_type * 100 + 5);
            for (auto h = this->_planetes[entity_id]->getHabitants().begin(); h != this->_planetes[entity_id]->getHabitants().end(); h++) {
                if (h->lock()) {
                    /* je remplis mon array de perso ou pnj qui vont mourir avec la planete */
                    if (h->lock()->getType() == HEROS) {
                        for (auto p = this->_quidams[HEROS].begin(); p != this->_quidams[HEROS].end(); p++) {
                            if (p->second == h->lock()) {
                                if (perso == NULL) perso = cJSON_CreateArray();
                                cJSON_AddItemToArray(perso, item = cJSON_CreateObject());
                                p->second->generate(item, p->first);
                            }
                        }
                    } else {
                        for (auto p = this->_quidams[HEROS].begin(); p != this->_quidams[HEROS].end(); p++) {
                            if (p->second == h->lock()) {
                                if (pnj == NULL) pnj = cJSON_CreateArray();
                                cJSON_AddItemToArray(pnj, item = cJSON_CreateObject());
                                p->second->generate(item, p->first);
                            }
                        }
                    }
                }

                // recuperation des ID de l'inventaire
                for (auto i = h->lock()->getInventory().begin(); i != h->lock()->getInventory().end(); i++) {
                    if (inv == NULL) inv = cJSON_CreateArray();
                    cJSON_AddItemToArray(inv, item = cJSON_CreateObject());
                    i->second->generate(item, i->first);
                }
            }
            this->deletePlanete(entity_id);
            break;
        case HEROS:
        case PNJ:
        case EVIL:
            //recuperation des ID de l'inventaire
            if (this->_quidams[entity_type].find(entity_id) == this->_quidams[entity_type].end()) return List::returnJson(entity_type * 100 + 12);
            for (auto it = this->_quidams[entity_type][entity_id]->getInventory().begin(); it != this->_quidams[entity_type][entity_id]->getInventory().end(); it++) {
                if (inv == NULL) inv = cJSON_CreateArray();
                cJSON_AddItemToArray(inv, item = cJSON_CreateObject());
                it->second->generate(item, it->first);
            }
            this->deletePerso(entity_id);
            break;
        case MISSION:
            if (this->_missions.find(entity_id) == this->_missions.end()) return List::returnJson(entity_type * 100 + 5);
            this->deleteMission(entity_id);
            break;
        case SPACESHIP:
            if (this->_flotte.find(entity_id) == this->_flotte.end()) return List::returnJson(entity_type * 100 + 9);
            for (auto it = this->_flotte[entity_id]->getInventory().begin(); it != this->_flotte[entity_id]->getInventory().end(); it++) {
                if (inv == NULL) inv = cJSON_CreateArray();
                cJSON_AddItemToArray(inv, item = cJSON_CreateObject());
                it->second->generate(item, it->first);
            }
            this->deleteSpaceship(entity_id);
            break;
        case GRADE:
            if (this->_grades.find(entity_id) == this->_grades.end()) return List::returnJson(entity_type * 100 + 5);
            this->deleteGrade(entity_id);
            break;
        case ITEM:
            code = ITEM * 100 + 8;
            for (auto type : this->_tableDeCorrespondance) for (auto it : type.second) if (it.first == entity_id) {
                this->deleteItem(entity_id);
                code = 0;
            }
            if (code != 0) List::returnJson(code);
            break;        
        default:
            return List::returnJson(NONE * 100 + 14);
            break;
    }

    if (perso != NULL || pnj != NULL || inv != NULL) {
        root = List::defaultNode();
        retour = cJSON_GetObjectItem(root, "return");
        if (perso != NULL) cJSON_AddItemToObject(retour, "personnages", perso);
        if (pnj != NULL) cJSON_AddItemToObject(retour, "pnjs", pnj);
        if (inv != NULL) cJSON_AddItemToObject(retour, "items", inv);
    } else root = List::defaultNode();
    
    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action addPnj
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char * (cJSON_Print())
 */
char *Controller::j_add_entities(cJSON *startrek) {
    char *print;
    cJSON *obj, *item;
    int id;

    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto array = cJSON_GetArrayItem(startrek, i);
        OBJETS type_owner;
        switch (cJSON_GetObjectItem(array, "entity_type")->valueint) {
            case PLANETE:
            case MISSION:
            case SPACESHIP:
            case GRADE:
                break;
            case PNJ:
            case HEROS:
            case EVIL:
                if (cJSON_GetObjectItem(array, "id_planet")->valueint != 0 
                && this->_planetes.find(cJSON_GetObjectItem(array, "id_planet")->valueint) == this->_planetes.end()) return List::returnJson(PLANETE * 100 + 5);
                if (cJSON_GetObjectItem(array, "id_planet_origin")->valueint != 0
                && this->_planetes.find(cJSON_GetObjectItem(array, "id_planet_origin")->valueint) == this->_planetes.end()) return List::returnJson(PLANETE * 100 + 5);
                if (cJSON_GetObjectItem(array, "id_ship")->valueint != 0
                && this->_flotte.find(cJSON_GetObjectItem(array, "id_ship")->valueint) == this->_flotte.end()) return List::returnJson(SPACESHIP * 100 + 9);
                if (cJSON_GetObjectItem(array, "id_grade")->valueint != 0
                && this->_grades.find(cJSON_GetObjectItem(array, "id_grade")->valueint) == this->_grades.end()) return List::returnJson(GRADE * 100 + 5);
                break;
            case ITEM:
                type_owner =  (OBJETS)cJSON_GetObjectItem(array, "type_owner")->valueint;
                if (type_owner != NONE) {
                    switch (cJSON_GetObjectItem(array, "type_owner")->valueint)
                    {
                    case HEROS:
                    case EVIL:
                    case PNJ:
                    case SPACESHIP:
                        if (find(QUIDAMS.begin(), QUIDAMS.end(), (OBJETS)cJSON_GetObjectItem(array, "type_owner")->valueint) == QUIDAMS.end()) {
                            if (this->_flotte.find(cJSON_GetObjectItem(array, "id_owner")->valueint) == this->_flotte.end()) return List::returnJson(SPACESHIP * 100 + 9);
                        } else {
                            if (this->_quidams[type_owner].find(cJSON_GetObjectItem(array, "id_owner")->valueint) == this->_quidams[type_owner].end()) return List::returnJson(type_owner * 100 + 12);
                        }
                        
                        break;
                    
                    default:
                        return List::returnJson(NONE * 100 + 17);
                        break;
                    }
                }
                break;
            default:
                return List::returnJson(NONE * 100 + 14);
                break;
        }
    }

    map<OBJETS, string> _quidams {{HEROS, "heros"}, {PNJ, "pnjs"}, {EVIL, "mechants"}};
    cJSON *root = List::defaultNode();
    obj = cJSON_GetObjectItem(root, "return");
    
    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        auto array = cJSON_GetArrayItem(startrek, i);
        switch (cJSON_GetObjectItem(array, "entity_type")->valueint)
        {
            case HEROS:
            case PNJ:
            case EVIL:
                id = this->addQuidam(
                    cJSON_GetObjectItem(array, "name")->valuestring,
                    cJSON_GetObjectItem(array, "ap")->valueint,
                    cJSON_GetObjectItem(array, "hp")->valueint,
                    cJSON_GetObjectItem(array, "dp")->valueint,
                    cJSON_GetObjectItem(array, "id_planet")->valueint,
                    cJSON_GetObjectItem(array, "id_ship")->valueint,
                    cJSON_GetObjectItem(array, "id_planet_origin")->valueint,
                    cJSON_GetObjectItem(array, "id_grade")->valueint,
                    (OBJETS)cJSON_GetObjectItem(array, "entity_type")->valueint);
                if (cJSON_GetObjectItem(obj, _quidams[(OBJETS)cJSON_GetObjectItem(array, "entity_type")->valueint].c_str()) == NULL) cJSON_AddItemToObject(obj,  _quidams[(OBJETS)cJSON_GetObjectItem(array, "entity_type")->valueint].c_str(), cJSON_CreateArray());
                cJSON_AddItemToArray(cJSON_GetObjectItem(obj, _quidams[(OBJETS)cJSON_GetObjectItem(array, "entity_type")->valueint].c_str()), item = cJSON_CreateObject());
                this->_quidams[(OBJETS)cJSON_GetObjectItem(array, "entity_type")->valueint][id]->generate(item, id);
                break;
            case PLANETE:
                id = this->addPlanet(
                    cJSON_GetObjectItem(array, "name")->valuestring,
                    cJSON_GetObjectItem(array, "description")->valuestring
                    );
                if (cJSON_GetObjectItem(obj, "planetes") == NULL) cJSON_AddItemToObject(obj, "planetes", cJSON_CreateArray());
                cJSON_AddItemToArray(cJSON_GetObjectItem(obj, "planetes"), item = cJSON_CreateObject());
                this->_planetes[id]->generate(item, id);
                break;
            case MISSION:
                id = this->addMission(
                    cJSON_GetObjectItem(array, "name")->valuestring,
                    cJSON_GetObjectItem(array, "description")->valuestring
                    );
                if (cJSON_GetObjectItem(obj, "missions") == NULL) cJSON_AddItemToObject(obj, "missions", cJSON_CreateArray());
                cJSON_AddItemToArray(cJSON_GetObjectItem(obj, "missions"), item = cJSON_CreateObject());
                this->_missions[id]->generate(item, id);
                break;
            case SPACESHIP:
                id = this->addSpaceShip(
                    cJSON_GetObjectItem(array, "name")->valuestring,
                    cJSON_GetObjectItem(array, "description")->valuestring,
                    cJSON_GetObjectItem(array, "ap")->valueint,
                    cJSON_GetObjectItem(array, "hp")->valueint,
                    cJSON_GetObjectItem(array, "dp")->valueint
                    );
                if (cJSON_GetObjectItem(obj, "ships") == NULL) cJSON_AddItemToObject(obj, "ships", cJSON_CreateArray());
                cJSON_AddItemToArray(cJSON_GetObjectItem(obj, "ships"), item = cJSON_CreateObject());
                this->_flotte[id]->generate(item, id);
                break;
            case ITEM:
                id = this->addItem(
                    cJSON_GetObjectItem(array, "name")->valuestring,
                    cJSON_GetObjectItem(array, "stat")->valueint,
                    (EFFECT)cJSON_GetObjectItem(array, "effect")->valueint,
                    cJSON_GetObjectItem(array, "id_owner")->valueint,
                    (OBJETS)cJSON_GetObjectItem(array, "type_owner")->valueint
                    );
                if (cJSON_GetObjectItem(obj, "items") == NULL) cJSON_AddItemToObject(obj, "items", cJSON_CreateArray());
                cJSON_AddItemToArray(cJSON_GetObjectItem(obj, "items"), item = cJSON_CreateObject());
                switch ((OBJETS)cJSON_GetObjectItem(array, "type_owner")->valueint)
                {
                case HEROS:
                case PNJ:
                case EVIL:
                    this->_quidams[(OBJETS)cJSON_GetObjectItem(array, "type_owner")->valueint][cJSON_GetObjectItem(array, "id_owner")->valueint]->getInventory()[id]->generate(item, id);
                    break;
                case SPACESHIP:
                    this->_flotte[cJSON_GetObjectItem(array, "id_owner")->valueint]->getInventory()[id]->generate(item, id);
                case NONE:
                    this->_items[id]->generate(item, id);
                    break;
                default:
                    break;
                }
                break;
            case GRADE:
                id = this->addGrade(
                    cJSON_GetObjectItem(array, "name")->valuestring,
                    cJSON_GetObjectItem(array, "level")->valueint
                    );
                if (cJSON_GetObjectItem(obj, "grades") == NULL) cJSON_AddItemToObject(obj, "grades", cJSON_CreateArray());
                cJSON_AddItemToArray(cJSON_GetObjectItem(obj, "grades"), item = cJSON_CreateObject());
                this->_grades[id]->generate(item, id);
                break;
            default:
                break;
        }
    }

    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action escape
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char * (cJSON_Print())
 */
char *Controller::j_escape(cJSON *startrek) {
    char *print;
    cJSON *defenseur, *obj;
    cJSON *root = List::defaultNode();
    obj = cJSON_GetObjectItem(root, "return");


    defenseur = cJSON_GetObjectItem(startrek, "defenseur");
    OBJETS type_def = (OBJETS)cJSON_GetObjectItem(defenseur, "type")->valueint;
    int id_def = cJSON_GetObjectItem(defenseur, "id")->valueint;

    if (this->_quidams[type_def].find(id_def) == this->_quidams[type_def].end()) return List::returnJson(type_def * 100 + 12);
    this->_quidams[type_def][id_def]->generate(obj, id_def);

    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
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
 * @param cJSON *startrek
 * @return char * (cJSON_Print())
 */
char    *Controller::j_getHabitants(cJSON *startrek) {
    char *print;
    
    cJSON *pnjs = NULL, *heros = NULL, *evils = NULL, *item;

    int id = cJSON_GetObjectItem(startrek, "id_planet")->valueint;
    if (this->_planetes.find(id) == this->_planetes.end()) return List::returnJson(PLANETE * 100 + 5);
    cJSON *root = List::defaultNode();

    for (auto h : this->_planetes[id]->getHabitants()) {
        if (!h.lock()) continue;

        int id_h = 0;
        item = cJSON_CreateObject();
        if (h.lock()->getType() == PNJ) {
            if (pnjs == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "pnjs", pnjs = cJSON_CreateArray());
            cJSON_AddItemToArray(pnjs, item = cJSON_CreateObject());
            for (auto p : this->_quidams[PNJ]) if (p.second == h.lock()) id_h = p.first;
        } else if (h.lock()->getType() == HEROS) {
            if (heros == NULL)  cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "heros", heros = cJSON_CreateArray());
            cJSON_AddItemToArray(heros, item = cJSON_CreateObject());
            for (auto p : this->_quidams[HEROS]) if (p.second == h.lock()) id_h = p.first;
        } else if (h.lock()->getType() == EVIL) {
            if (evils == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "mechants", evils = cJSON_CreateArray());
            cJSON_AddItemToArray(evils, item = cJSON_CreateObject());
             for (auto p : this->_quidams[EVIL]) if (p.second == h.lock()) id_h = p.first;
        }
        h.lock()->generate(item, id_h);
    }
    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getEquipage
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char * (cJSON_Print())
 */
char    *Controller::j_getEquipage(cJSON *startrek) {
    char *print;
    
    cJSON *pnjs = NULL, *heros = NULL, *evils = NULL, *item;
    int id = cJSON_GetObjectItem(startrek, "id_ship")->valueint;
    if (this->_flotte.find(id) == this->_flotte.end()) return List::returnJson(SPACESHIP * 100 + 9);

    cJSON *root = List::defaultNode();

    
    for (auto h : this->_flotte[id]->getEquipage()) {
        if (!h.lock()) continue;

        int id_h = 0;
        item = cJSON_CreateObject();
        if (h.lock()->getType() == PNJ) {
            if (pnjs == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "pnjs", pnjs = cJSON_CreateArray());
            cJSON_AddItemToArray(pnjs, item = cJSON_CreateObject());
            for (auto p : this->_quidams[PNJ]) if (p.second == h.lock()) id_h = p.first;
        } else if (h.lock()->getType() == HEROS) {
            if (heros == NULL)  cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "heros", heros = cJSON_CreateArray());
            cJSON_AddItemToArray(heros, item = cJSON_CreateObject());
            for (auto p : this->_quidams[HEROS]) if (p.second == h.lock()) id_h = p.first;
        } else if (h.lock()->getType() == EVIL) {
            if (evils == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "mechants", evils = cJSON_CreateArray());
            cJSON_AddItemToArray(evils, item = cJSON_CreateObject());
             for (auto p : this->_quidams[EVIL]) if (p.second == h.lock()) id_h = p.first;
        }
        h.lock()->generate(item, id_h);
    }

    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
}
char    *Controller::j_getInventory(cJSON *startrek) {
    char *print;
    cJSON *entities, *node;
    OBJETS entity_type = (OBJETS)cJSON_GetObjectItem(startrek, "entity_type")->valueint;
    int entity_id = cJSON_GetObjectItem(startrek, "entity_id")->valueint;
    switch (entity_type)
    {
        case HEROS:
        case EVIL:
        case PNJ:
            if (this->_quidams[entity_type].find(entity_id) == this->_quidams[entity_type].end()) return List::returnJson(entity_type * 100 + 12);
            break;
        case SPACESHIP:
            if (this->_flotte.find(entity_id) == this->_flotte.end()) return List::returnJson(entity_type * 100 + 9);
            break;
        case MISSION:
        case ITEM:
        case PLANETE:
        case GRADE:
            return List::returnJson(NONE * 100 + 17);
            break;
        default:
            return List::returnJson(NONE * 100 + 14);
            break;
    }
    
    cJSON *root = List::defaultNode();
    cJSON *obj = cJSON_GetObjectItem(root, "return");
    cJSON_AddItemToObject(obj, "entities", entities = cJSON_CreateArray());

    switch(entity_type) {
        case HEROS:
        case PNJ:
        case EVIL:
            for (auto c : this->_tableDeCorrespondance[entity_type]) {
                if (c.second != entity_id) continue;
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                this->_quidams[entity_type][c.second]->getInventory()[c.first]->generate(node, c.first);
            }
            break;
        case SPACESHIP:
            for (auto c : this->_tableDeCorrespondance[SPACESHIP]) {
                if (c.second != entity_id) continue;
                cJSON_AddItemToArray(entities, node = cJSON_CreateObject());
                this->_flotte[c.second]->getInventory()[c.first]->generate(node, c.first);
            }
            break;
        default:
            break;
    }
    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action promote
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char* (cJSON_Print())
 */
char    *Controller::j_promote(cJSON *startrek) {
    char *print;
    int entity_id, id_grade;
    OBJETS entity_type;
    cJSON *heros = NULL, *pnjs = NULL, *evils = NULL, *obj;

    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        if (find(QUIDAMS.begin(), QUIDAMS.end(), (OBJETS)cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "entity_type")->valueint) == QUIDAMS.end()) return List::returnJson(NONE * 100 + 18);
        if (this->_quidams[(OBJETS)cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "entity_type")->valueint].find(cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "entity_id")->valueint) == this->_quidams[(OBJETS)cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "entity_type")->valueint].end()) return List::returnJson(cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "entity_type")->valueint * 100 + 12);
        if (this->_grades.find((OBJETS)cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "id_grade")->valueint) == this->_grades.end()) return List::returnJson(GRADE * 100 + 5);
    }
    cJSON *root = List::defaultNode();
    for (int i = 0; i < cJSON_GetArraySize(startrek); i++) {
        entity_id = cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "entity_id")->valueint;
        entity_type = (OBJETS)cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "entity_type")->valueint;
        id_grade = cJSON_GetObjectItem(cJSON_GetArrayItem(startrek, i), "id_grade")->valueint;

        switch (entity_type)
        {
            case HEROS:
                if (heros == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "heros", heros = cJSON_CreateArray());
                cJSON_AddItemToArray(heros, obj = cJSON_CreateObject());
                break;
            case PNJ:
                if (pnjs == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "pnjs", pnjs = cJSON_CreateArray());
                cJSON_AddItemToArray(pnjs, obj = cJSON_CreateObject());
                break;
            case EVIL:
                if (evils == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "mechants"), "evils", pnjs = cJSON_CreateArray());
                cJSON_AddItemToArray(evils, obj = cJSON_CreateObject());
                break;
            default:
                break;
        }
        this->promote(id_grade, entity_id, (OBJETS) entity_type);
        this->_quidams[entity_type][entity_id]->generate(obj, entity_id);
    }
    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
}

/** Fonctions de traitement des JSON reçus par le client TCP */
/**
 * Lit le JSON startrek node passé en parametre et effectue l'action getHierarchy
 * la fonction retourne le string json qui sera renvoyé au serveur
 * @param cJSON *startrek
 * @return char* (cJSON_Print())
 */
char    *Controller::j_getHierarchy(cJSON *startrek) {
    char *print;
    cJSON *pnjs = NULL, *heros = NULL, *evils = NULL, *item;
    int id = cJSON_GetObjectItem(startrek, "id_grade")->valueint;
    if (this->_grades.find(id) == this->_grades.end()) return List::returnJson(GRADE * 100 + 5);

    cJSON *root = List::defaultNode();
    for (auto h : this->_grades[id]->getMembre()) {
        if (!h.lock()) continue;

        int id_h = 0;
        item = cJSON_CreateObject();
        if (h.lock()->getType() == PNJ) {
            if (pnjs == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "pnjs", pnjs = cJSON_CreateArray());
            cJSON_AddItemToArray(pnjs, item = cJSON_CreateObject());
            for (auto p : this->_quidams[PNJ]) if (p.second == h.lock()) id_h = p.first;
        } else if (h.lock()->getType() == HEROS) {
            if (heros == NULL)  cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "heros", heros = cJSON_CreateArray());
            cJSON_AddItemToArray(heros, item = cJSON_CreateObject());
            for (auto p : this->_quidams[HEROS]) if (p.second == h.lock()) id_h = p.first;
        } else if (h.lock()->getType() == EVIL) {
            if (evils == NULL) cJSON_AddItemToObject(cJSON_GetObjectItem(root, "return"), "mechants", evils = cJSON_CreateArray());
            cJSON_AddItemToArray(evils, item = cJSON_CreateObject());
             for (auto p : this->_quidams[EVIL]) if (p.second == h.lock()) id_h = p.first;
        }
        h.lock()->generate(item, id_h);
    }

    print = cJSON_Print(root);
    cJSON_Delete(root);
    return print;
}
