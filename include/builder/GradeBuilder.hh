/*
 * File: GradeBuilder.hh                                                       *
 * Project: builder                                                            *
 * Created Date: Sa Apr 2026, 9:59:04 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 12:02:52 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef GRADE_BUILDER_HH
#define GRADE_BUILDER_HH

#include                        <string>
#include                        <memory>
#include                        "../object/Grade.hh"
#include                        "../define.hh"

class                           GradeBuilder {
    private:
    string                      _name = "";
    int                         _level = 0;
    
    void                        validate();
    
    public:
    GradeBuilder                &withName(string name);
    GradeBuilder                &withLevel(int lvl);
    shared_ptr<Grade>           build();
    static shared_ptr<Grade>    fromJson(boost::json::object &item);
};

#endif