/**
* File: Mission.hh
* Project: objects
* File Created: Wednesday, 12th July 2023 4:18:01 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:43:29 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef         MISSION_HH_
#define         MISSION_HH_

#include        <string>
#include        <iostream>
#include        <vector>
#include        "../lib_func/cJSON.hh"

using namespace std;


class           Mission {

public:
                Mission(string objectif, string description, bool is_completed);
                Mission(cJSON *node);
    virtual     ~Mission();

    //setters
    void        setIsCompleted(bool is);

    //getters
    string      getName() const;
    string      getDescription() const;
    bool        getIsComplete();
    cJSON       *generate(cJSON *node, int id);

private:
    string      _name;
    string      _description;
    bool        _isComplete;
};

#endif //CPP_HEROSNNAGE_MISSION_HH
