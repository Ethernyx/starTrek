/**
 * File: Inventory.hh
 * Project: objects
 * File Created: Sunday', 30th July 2023 6:39:51 pm
 * Author: LALIN Romain
 * -----
 * Last Modified: Sunday', 30th July 2023 6:39:51 pm
 * Modified by: LALIN Romain
 * -----
*/

#ifndef INVENTORY_HH_
#define INVENTORY_HH_

#include                        <map>
#include                        <memory>
#include                        "Item.hh"

using namespace                 std;

class                           Inventory
{
protected:
    size_t                      _maxItem;
    map<int, unique_ptr<Item>>  _inventory;
public:
                                Inventory(size_t maxItem);
    virtual                     ~Inventory();
    map<int, unique_ptr<Item>>  &getInventory();
    size_t                      getMaxItem() const;
    void                        addItem(unique_ptr<Item> &item, int id);
};

#endif