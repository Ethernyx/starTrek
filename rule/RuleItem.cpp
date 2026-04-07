/*
 * File: RuleItem.cpp                                                          *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:04:30 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 10:55:03 am                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/rule/RuleItem.hh"

bool    RuleItem::kill(map<int, Item*> &items) {
    bool isOk = true;

    for(auto it = items.begin(); it != items.end(); it++) {
        isOk = this->deleteItem(it->first);
        if (!isOk) return isOk;
    }
    return isOk;
}

void    RuleItem::addToResultRequest(ResultRequest *result, int id) {
    result->_items[id] = this->_items[id].get();
}

ResultRequest   &RuleItem::fillResultRequestKill(int id) {
    ResultRequest result;

    result._code = UNKNOWN_ITEM;
    for (auto type : this->_tableDeCorrespondance) for (auto it : type.second) if (it.first == id) {
        addToResultRequest(&result, id);
        result._code = OK;
        break;
    }
    return result;
}