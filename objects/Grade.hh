/**
* File: Grade.hh
* Project: objects
* File Created: Friday, 23rd June 2023 6:54:56 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 10:40:28 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef                         GRADE_HH_
#define                         GRADE_HH_

#include                        <string>
#include                        <vector>
#include                        <iostream>

#include                        "AQuidam.hh"
#include                        "../lib_func/cJSON.hh"

using namespace                 std;

class                           Grade
{
private:
    string                      _name;
    int                         _level;
    vector<weak_ptr<AQuidam>>   _membre;
public:
                                Grade(const string, const int);
                                Grade(cJSON *node);
    virtual                     ~Grade();
    string                      getNom() const;
    int                         getLevel() const;
    vector<weak_ptr<AQuidam>>   &getMembre();
    void                        addMembre(shared_ptr<AQuidam> &);
    bool                        deleteMembre(const string);
    cJSON                       *generate(cJSON *node, int id);
    void                        cleanMembres();
};

#endif