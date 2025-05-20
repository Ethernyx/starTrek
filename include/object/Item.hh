/**
* File: Item.hh
* Project: objects
* File Created: Thursday, 13th July 2023 12:10:59 pm
* Author: LALIN Romain 
* -----
* Last Modified: Wednesday, 26th July 2023 9:52:32 pm
* Modified By: LALIN Romain
* -----
*/

#ifndef         ITEM_HH_
#define         ITEM_HH_

#include        <string>
#include        <memory>
#include        <iostream>
#include        "../define.hh"
#include        "../../lib_func/cJSON.hh"

using namespace std;

class           Item
{
private:
    string      _name;
    int         _stat;
    EFFECT      _effect;
    int         _id_owner;
    OBJETS      _type;
public:
                Item(const string, const int, const EFFECT);
                Item(const string, const int, const EFFECT, const int, const OBJETS);
                Item(cJSON *node);
    virtual     ~Item();

    EFFECT      getEffect() const;
    string      getName() const;
    int         getStat() const;
    int         getIdOwner() const;
    OBJETS      getTypeOwner() const;

    void        setOwner(const int, const OBJETS);
    void        setStat(const int);
    void        setEffect(const EFFECT);
    void        setName(const string);

    void        setAttr(const string, const int, const EFFECT, const int, const OBJETS);
    boost::json::object generate(int id);
};

#endif
