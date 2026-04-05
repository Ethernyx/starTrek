/*
 * File: PlaneteBuilder.hh                                                     *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 10:14:52 pm                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 12:03:17 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef PLANETE_BUILDER_HH
#define PLANETE_BUILDER_HH

#include                        <string>
#include                        <memory>
#include                        "../object/Planete.hh"
#include                        "../define.hh"

class                           PlaneteBuilder
{
private:
    string                      _name;
    string                      _description;
    
    void                        validate();
public:
    PlaneteBuilder              &withName(string name);
    PlaneteBuilder              &withDescription(string desc);
    shared_ptr<Planete>         build();
    static shared_ptr<Planete>  fromJson(boost::json::object &item);
};

#endif