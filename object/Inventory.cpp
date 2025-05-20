/**
 * File: Inventory.cpp
 * Project: objects
 * File Created: Sunday', 30th July 2023 6:46:05 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Sunday', 30th July 2023 6:46:05 pm
 * Modified by: LALIN Romain
 * -----
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