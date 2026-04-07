/*
 * File: LifeDoor.cpp                                                          *
 * Project: starTrek                                                           *
 * Created Date: Su Apr 2026, 3:45:50 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 12:49:32 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "include/LifeDoor.hh"

bool LifeDoor::deleteMission(string const name)
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
bool LifeDoor::deleteMission(int const id)
{
    auto it = this->_missions.find(id);
    if (it == this->_missions.end())
        return false;
    this->_missions.erase(it);
    return true;
}

bool LifeDoor::deleteSpaceship(string const name)
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
bool LifeDoor::deleteSpaceship(const int id_ship)
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

bool LifeDoor::deletePerso(string const name)
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
bool LifeDoor::deletePerso(const int id)
{
    shared_ptr<AQuidam> found = nullptr;
    OBJETS foundType = NONE;

    for (auto type : QUIDAMS) {
        auto it = this->_quidams[type].find(id);
        if (it != this->_quidams[type].end()) {
            found = it->second;
            foundType = type;
            break;
        }
    }
    if (!found) return false;

    // ── gestion des inventaires ────────────────
    vector<int> itemIds;
    for (auto &i : found->getInventory()) itemIds.push_back(i.first);
    for (auto itemId : itemIds) this->removeItem(itemId, found->getName(), foundType);

    // ── suppression du quidam ────────────────
    this->_quidams[foundType].erase(id);

    // ── gestion des effets de bords ────────────────
    for (auto &p : this->_planetes) p.second->cleanHabitants();
    for (auto &f : this->_flotte)   f.second->cleanEquipage();
    for (auto &g : this->_grades)   g.second->cleanMembres();
    return true;
}

bool    LifeDoor::deleteItem(int id) {
    for (auto type : this->_tableDeCorrespondance) for (auto it : type.second) if (it.first == id) {
            switch (type.first)
            {
                case HEROS:
                case PNJ:
                case EVIL:
                    if (this->_quidams[(OBJETS)type.first][it.second]->getInventory().find(it.first) == this->_quidams[(OBJETS)type.first][it.second]->getInventory().end()) return false;
                    this->_quidams[(OBJETS)type.first][it.second]->getInventory().erase(this->_quidams[(OBJETS)type.first][it.second]->getInventory().find(it.first));
                    break;
                case SPACESHIP:
                    if (this->_flotte[it.second]->getInventory().find(it.first) == this->_flotte[it.second]->getInventory().end()) return false;
                    this->_flotte[it.second]->getInventory().erase(this->_flotte[it.second]->getInventory().find(it.first));
                case NONE:
                    if (this->_items.find(id) == this->_items.end()) return false;
                    this->_items.erase(this->_items.find(id));
                    break;
                default:
                    return false;
                    break;
            }
        }
    return true;
}

void    LifeDoor::removeItem(int idItem, string name, OBJETS type) {
    if (type == SPACESHIP) this->_items[idItem].swap(this->getSpaceship(name)->getInventory()[idItem]);
    else this->_items[idItem].swap(this->getPerso(name)->getInventory()[idItem]);
    /* je set le owner */
    this->_items[idItem]->setOwner(0, NONE);
    /* j'erase l'ancienne corespondance */
    this->_tableDeCorrespondance[type].erase(this->_tableDeCorrespondance[type].find(idItem));
    /* j'ajoute la nouvelle */
    this->_tableDeCorrespondance[NONE][idItem] = 0;
}

bool    LifeDoor::deleteGrade(const int id) {
    auto it = this->_grades.find(id);

    if (it == this->_grades.end()) return false;
    
    for (auto i = this->_quidams[HEROS].begin(); i != this->_quidams[HEROS].end();i++) if (i->second->getIdGrade() == it->first) i->second->setIdGrade(0);
    for (auto i = this->_quidams[PNJ].begin(); i != this->_quidams[PNJ].end();i++) if (i->second->getIdGrade() == it->first) i->second->setIdGrade(0);

    this->_grades.erase(it);
    return true;
}

int LifeDoor::addQuidam(boost::json::object &item)
{
    auto quidam = AQuidamBuilder::fromJson(item);
    int id = this->getMaxId(quidam->getType()) + 1;
    
    if (quidam->getIdShip() != 0 && !this->_flotte[quidam->getIdShip()])        throw runtime_error("ID SHIP inconnu");
    if (quidam->getIdPlanet() != 0 && !this->_planetes[quidam->getIdPlanet()])  throw runtime_error("ID PLANET inconnu");
    if (quidam->getIdGrade() != 0 && !this->_grades[quidam->getIdGrade()])      throw runtime_error("ID GRADE inconnu");

    this->_quidams[quidam->getType()][id] = quidam;
    if (quidam->getIdShip() != 0)   this->_flotte[quidam->getIdShip()]->addEquipage(quidam);
    if (quidam->getIdPlanet())      this->_planetes[quidam->getIdPlanet()]->setHabitant(quidam);
    if (quidam->getIdGrade() != 0)  this->_grades[quidam->getIdGrade()]->addMembre(quidam);  
    return id;
}
int LifeDoor::addPnj(const string name, const int puissance, const int sante, const int dp, const int id_planet, const int id_ship, const int id_planete_origine, const int id_grade) {
    int id = this->getMaxId(PNJ) + 1;
    this->_quidams[PNJ][id] = make_shared<Pnj>(name, puissance, sante, dp, id_planete_origine, id_ship, id_planet, id_grade);
    if (id_ship != 0 && this->_flotte[id_ship]) this->_flotte[id_ship]->addEquipage(this->_quidams[PNJ][id]);
    if (id_planet != 0 && this->_planetes[id_planet]) this->_planetes[id_planet]->setHabitant(this->_quidams[PNJ][id]);
    return id;
}

int LifeDoor::addPlanet(boost::json::object &item)
{
    int id = this->getMaxId(PLANETE) + 1;
    this->_planetes[id] = PlaneteBuilder::fromJson(item);
    return id;
}
int LifeDoor::addSpaceShip(boost::json::object &item)
{
    int id = this->getMaxId(SPACESHIP) + 1;
    this->_flotte[id] = SpaceshipBuilder::fromJson(item);
    return id;
}
int LifeDoor::addMission(boost::json::object &item)
{
    int id = this->getMaxId(MISSION) + 1;
    this->_missions[id] = MissionBuilder::fromJson(item);
    return id;
}

int LifeDoor::addItem(boost::json::object &item) {
    int id = this->getMaxId(ITEM) + 1;
    this->_items[id] = ItemBuilder::fromJson(item);
    
    this->_tableDeCorrespondance[this->_items[id]->getTypeOwner()][id] = this->_items[id]->getIdOwner();
    if (this->_items[id]->getIdOwner() != 0) {
        switch (this->_items[id]->getTypeOwner())
        {
        case HEROS:
        case EVIL:
        case PNJ:
            this->_quidams[this->_items[id]->getTypeOwner()][this->_items[id]->getIdOwner()]->addItem(this->_items[id], id);
            break;
        case SPACESHIP:
            this->_flotte[this->_items[id]->getIdOwner()]->addItem(this->_items[id], id);
            break;
        default:
            break;
        }
    }
    return id;
}

int     LifeDoor::addGrade(boost::json::object &item) {
    int id = this->getMaxId(GRADE) + 1;
    this->_grades[id] = GradeBuilder::fromJson(item);
    return id;
}