/**
* File: Spaceship.hh
* Project: objects
* File Created: Thursday, 13th July 2023 11:49:25 am
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:56:43 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef                         SPACESHIP_HH_
#define                         SPACESHIP_HH_

#include                        <vector>
#include                        "AQuidam.hh"


using namespace                 std;

class                           Spaceship : public Attribut, public Inventory {
public:
    //constructeur
                                Spaceship(string nom, string description, int ap, int hp, int dp);
                                Spaceship(boost::json::object item);
    virtual                     ~Spaceship();

    //getters
    string                      getName();
    string                      getDescription();
    vector<weak_ptr<AQuidam>>   &getEquipage();

    //setters
    void                        set_name(string nom);

    //methodes
    void                        addEquipage(shared_ptr<AQuidam> &adresse_de_obj_personne);
    bool                        deleteEquipage(string);
    void                        cleanEquipage();
    bool                        isExists(const std::string namePerso);
    boost::json::object         generate(int id);



private:
    vector<weak_ptr<AQuidam>>   _equipage;
    string                      _name;
    string                      _description;

};

#endif //CPP_HEROSNNAGE_SPACESHIP_H
