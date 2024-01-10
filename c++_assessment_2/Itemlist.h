#pragma once
#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <string>

class ItemList
{
public:

    //pure virtual destructor. I want the derived classes to use their own specific destructors
    virtual ~ItemList() = default;

    //forces the derived classes to use their own toString fucntions
    virtual std::string toString() const = 0; //abstract class, meant to be overriden
};

#endif