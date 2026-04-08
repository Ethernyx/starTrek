/*
 * File: RuleGrade.hh                                                          *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:57:49 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 6:39:12 pm                        *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_GRADE_HH_
#define RULE_GRADE_HH_

#include    "RuleQuidam.hh"
#include    "../ReturnRequest.hh"

class       RuleGrade : public virtual RuleQuidam
{
public:
    bool    kill(map<int, shared_ptr<Grade>> &grades);
    void    fillResultRequestKill(ResultRequest *result, int id);
    void    fillResultRequestGetHierarchy(ResultRequest *result, int id);
    void    fillResultRequestGetInfos(ResultRequest *result, int id);
    void    fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);
    void    addToResultRequest(ResultRequest *result, int id);
};


#endif