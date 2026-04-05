/*
 * File: MissionBuilder.hh                                                     *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 10:27:28 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 12:03:09 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef MISSION_BUILDER_HH
#define MISSION_BUILDER_HH

#include                        <string>
#include                        <memory>
#include                        "../object/Mission.hh"
#include                        "../define.hh"

class                           MissionBuilder
{
private:
    string                      _name = "";
    string                      _description = "";
    bool                        _isComplete = false;

    void                        validate();
public:
    MissionBuilder              &withName(string name);
    MissionBuilder              &withDescription(string desc);
    MissionBuilder              &isComplete();
    shared_ptr<Mission>         build();
    static shared_ptr<Mission>  fromJson(boost::json::object &item);
};


#endif