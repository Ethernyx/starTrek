/*
 * File: ItemBuilder.hh                                                        *
 * Project: builder                                                            *
 * Created Date: Su Apr 2026, 11:26:26 am                                      *
 * Author: LALIN Romain                                                        *
 * -----                                                                       *
 * Last Modified: Sunday, April 5th 2026, 12:03:03 pm                          *
 * By: LALIN Romain                                                            *
 * ----------	---	---------------------------------------------------------  *
*/

#ifndef ITEM_BUILDER_HH_
#define ITEM_BUILDER_HH_

#include                    <string>
#include                    <memory>
#include                    "../object/Item.hh"


class                       ItemBuilder
{
private:
    string                  _name = "";
    int                     _stat = 0;
    EFFECT                  _effect = (EFFECT) 0;
    int                     _id_owner = 0;
    OBJETS                  _type = NONE;

    void                    validate();
public:
    ItemBuilder             &withName(const string name);
    ItemBuilder             &withStat(const int stat);
    ItemBuilder             &withEffect(const EFFECT effect);
    ItemBuilder             &withOwner(const int id_owner);
    ItemBuilder             &withType(const OBJETS type);
    unique_ptr<Item>        build();
    static unique_ptr<Item> fromJson(boost::json::object &item);
};


#endif