/*
 * File: List.hh                                                               *
 * Project: lib_func                                                           *
 * Created Date: Tu May 2025, 11:14:09 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Saturday, April 4th 2026, 3:03:02 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef             LIST_HH_
#define             LIST_HH_

#include            <string>
#include            <string.h>
#include            <iostream>
#include            <boost/json.hpp>
#include            "../include/define.hh"

using namespace     std;

class               List
{
public:
    static int      isCorectToObjPrototype(boost::json::object const &node, OBJETS type_obj, bool required);
    static int      isRequiredRootStructure(boost::json::object const &root);
    static int      isCorectToInitPrototype(boost::json::object const &root);
    static int      isCorrectToAttackPrototype(boost::json::object const &root);
    static int      isCorrectToExhangeItemPrototype(boost::json::object const &root);
    static int      isCorrectToGetInfosPrototype(boost::json::object const &root);
    static int      isCorrectToGetAddEntitiesPrototype(boost::json::object const &root);
    static int      isCorrectToEscapePrototype(boost::json::object const &root);
    static int      isCorrectToKillPrototype(boost::json::object const &root);
    static int      isCorrectToGetHabitantsPrototype(boost::json::object const &root);
    static int      isCorrectToGetEquipagePrototype(boost::json::object const &root);
    static int      isCorrectToGetInventoryPrototype(boost::json::object const &root);
    static int      isCorrectToPromotePrototype(boost::json::object const &root);
    static int      isCorrectToGetHierarchyPrototype(boost::json::object const &root);
    static string   codeError(int error);
    static string   returnJson(int code);
    static bool     checkJson(string const &json);
    static vector<string> split(string, string);
};

#endif
