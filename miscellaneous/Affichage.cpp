/**
* File: Affichage.cpp
* Project: miscellaneous
* File Created: Thursday, 27th July 2023 9:13:55 pm
* Author: LALIN Romain 
* -----
* Last Modified: Thursday, 27th July 2023 9:22:53 pm
* Modified By: LALIN Romain
* -----
*/

#include    "Affichage.hh"

using namespace std;

void        Affichage::displayMainMenu() {
    cout << "1 - Voir les missions" << endl;
    cout << "2 - Parler aux personnages" << endl;
    cout << "3 - Voyager vers un autre planete" << endl;
    cout << "4 - Quitter le jeu" << endl;
}

void        Affichage::displayMissions(map<int, shared_ptr<Mission>> &missions) {
    cout << "------------- Missions en cours ---------------" << endl;
    for(auto m : missions)
        cout << m.second->getName() << endl;
    cout << endl;
}

void        Affichage::displayHeros(map<int, shared_ptr<Heros>> &personnages) {
    cout << "------------- Liste des personnages ---------------" << endl;
    for (auto p : personnages) {
        cout << "==> " << p.second->getName() << ": count " << p.second.use_count() << " : " << p.second->getAp() << " d'attaque et " << p.second->getHp() << " PV" << endl;
    }
}

void        Affichage::displayPlanetes(map<int, shared_ptr<Planete>> &planetes) {
    cout << "------------- Liste des planetes ---------------" << endl;
    for (auto p : planetes) {
        cout << "- " << p.second->getName() << ": count " << p.second.use_count() << " : " << p.second->getDescription() << endl;
        cout << "Liste des habitants :" << endl;
        for (auto h : p.second->getHabitants()) {
            shared_ptr<AQuidam> sptr = h.lock();
            if (sptr) cout << "\t+ " << sptr->getName() << endl;
        }
    }
}

void        Affichage::displaySpaceShips(map<int, shared_ptr<Spaceship>> &ships) {
    cout << "------------- Liste des vaisseaux ---------------" << endl;
    for (auto s : ships) {
        cout << "- " << s.second->getName() << ": count " << s.second.use_count() << " : " << s.second->getDescription() << endl;
        cout << "Liste des membres d'équipage :" << endl;
        for (auto h : s.second->getEquipage()) {
            shared_ptr<AQuidam> sptr = h.lock();
            if (sptr) cout << "\t+ " << sptr->getName() << endl;
        }
    }
}

void        Affichage::clear() {
    #ifdef DEBUG
    std::cout << "Mode débug activé : pas de clear" << std::endl;
    #else
    std::cout << "\033[H\033[J";
    #endif
}