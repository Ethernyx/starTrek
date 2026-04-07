/*
 * File: Grade.hh                                                              *
 * Project: object                                                             *
 * Created Date: Tu May 2025, 11:12:03 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 4:10:08 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef                         GRADE_HH_
#define                         GRADE_HH_

#include                        <string>
#include                        <vector>
#include                        <iostream>

#include                        "AQuidam.hh"

using namespace                 std;

class                           Grade
{
private:
    string                      _name;
    int                         _level;
    vector<weak_ptr<AQuidam>>   _membre;
public:
                                Grade(const string, const int);
                                Grade(boost::json::object item);
    virtual                     ~Grade();
    string                      getNom() const;
    int                         getLevel() const;
    vector<weak_ptr<AQuidam>>   &getMembre();
    void                        addMembre(shared_ptr<AQuidam> &);
    bool                        deleteMembre(const string);
    bool                        deleteMembre(shared_ptr<AQuidam> &);
    boost::json::object         generate(int id);
    void                        cleanMembres();
};

#endif