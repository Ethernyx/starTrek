/**
 * File: Planete.hh
 * Project: objects
 * File Created: Friday', 28th July 2023 2:33:51 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Friday', 28th July 2023 2:33:51 pm
 * Modified by: LALIN Romain
 * -----
*/

#ifndef                         PLANETE_HH_
#define                         PLANETE_HH_

#include                        <vector>
#include                        "AQuidam.hh"

using namespace                 std;

class                           Planete {
public:
                                Planete(string nom, string description);
                                Planete(cJSON *node);
    virtual                     ~Planete();

    //getters
    string                      getName() const;
    string                      getDescription() const;
    vector<weak_ptr<AQuidam>>   &getHabitants();
    void                        cleanHabitants();

    //setters
    void                        setHabitant(std::shared_ptr<AQuidam> &habitant);

    bool                        deleteHabitant(const string name);
    bool                        isExists(const string name);
    boost::json::object         generate(int id);

private:
    string                      _name;
    string                      _description;
    vector<weak_ptr<AQuidam>>   _habitants;

};

#endif //CPP_HEROSNNAGE_PLANETE_H
