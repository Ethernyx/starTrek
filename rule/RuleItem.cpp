/*
 * File: RuleItem.cpp                                                          *
 * Project: rule                                                               *
 * Created Date: Tu Apr 2026, 10:04:30 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Tuesday, April 7th 2026, 5:21:40 pm                          *
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

ResultRequest   RuleItem::fillResultRequestKill(int id) {
    ResultRequest result;

    if (!this->isItemExist(&result, id)) return result;

    this->addToResultRequest(&result, id);
    return result;
}

ResultRequest   RuleItem::fillResultRequestGetInfos(int id) {
    ResultRequest   result;

    if (id != -1 && !this->isItemExist(&result, id)) return result;
    for (auto type : this->_tableDeCorrespondance) { // comme fonctionnement par unique_ptr on prend la table des corespondances
        for (auto item : type.second) {
            if (id != -1 && item.first == id || id == -1) this->addToResultRequest(&result, item.first); 
        }
    }
    return result;
}