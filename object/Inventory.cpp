/*
 * File: Inventory.cpp                                                         *
 * Project: object                                                             *
 * Created Date: Tu May 2025, 11:12:16 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Thursday, April 9th 2026, 2:23:11 pm                         *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#include    "../include/object/Inventory.hh"

Inventory::Inventory(size_t maxItem) : _maxItem(maxItem) {}

Inventory::~Inventory() {}

map<int, unique_ptr<Item>>  &Inventory::getInventory() {
    return this->_inventory;
}

size_t Inventory::getMaxItem() const {
    return this->_maxItem;
}

void    Inventory::addItem(unique_ptr<Item> &item, int id) {
    if (this->_inventory.size() <= this->_maxItem && item) this->_inventory.insert(make_pair(id, std::move(item)));
}