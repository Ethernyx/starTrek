/*
 * File: RuleGrade.hh                                                          *
 * Project: rule                                                               *
 * Created Date: Mo Apr 2026, 1:57:49 pm                                       *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Wednesday, April 8th 2026, 12:24:08 pm                       *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef RULE_GRADE_HH_
#define RULE_GRADE_HH_

#include    "RuleQuidam.hh"
#include    "../ReturnRequest.hh"

class RuleGrade : public virtual RuleQuidam
{
private:
public:
    bool                                        kill(map<int, shared_ptr<Grade>> &grades);
    ResultRequest                               fillResultRequestKill(int id);
    ResultRequest                               fillResultRequestGetHierarchy(int id);
    ResultRequest                               fillResultRequestGetInfos(int id);
    void                                        fillResultRequestAddEntities(ResultRequest *result, map<string, int> attr_int, map<string, string> attr_string);
    void                                        addToResultRequest(ResultRequest *result, int id);
};


#endif