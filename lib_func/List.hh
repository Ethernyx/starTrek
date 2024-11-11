/**
 * File: List.hh
 * Project: lib_func
 * File Created: Friday', 28th July 2023 2:33:51 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Friday', 28th July 2023 2:33:51 pm
 * Modified by: LALIN Romain
 * -----
*/

#ifndef             LIST_HH_
#define             LIST_HH_

#include            <string>
#include            <string.h>
#include            <iostream>
#include            "cJSON.hh"
#include            "../define.hh"

using namespace     std;

class               List
{
public:
    static size_t   size(cJSON *node);
    static cJSON    *firstElem(cJSON *node);
    static cJSON    *defaultNode();
    static int      isCorectToObjPrototype(cJSON *node, OBJETS type_obj, bool required);
    static int      isRequiredRootStructure(cJSON *root);
    static int      isCorectToInitPrototype(cJSON *root);
    static int      isCorrectToAttackPrototype(cJSON *root);
    static int      isCorrectToExhangeItemPrototype(cJSON *root);
    static int      isCorrectToGetInfosPrototype(cJSON *root);
    static int      isCorrectToGetAddEntitiesPrototype(cJSON *root);
    static int      isCorrectToEscapePrototype(cJSON *root);
    static int      isCorrectToKillPrototype(cJSON *root);
    static int      isCorrectToGetHabitantsPrototype(cJSON *root);
    static int      isCorrectToGetEquipagePrototype(cJSON *root);
    static int      isCorrectToGetInventoryPrototype(cJSON *root);
    static int      isCorrectToPromotePrototype(cJSON *root);
    static int      isCorrectToGetHierarchyPrototype(cJSON *root);
    static string   codeError(int error);
    static char     *returnJson(int code);
    static bool     checkJson(string json);

};

#endif