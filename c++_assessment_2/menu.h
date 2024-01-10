#pragma once

#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <vector>
#include "Itemlist.h"
#include "order.h"

class Item; //this is a forward declaration so that the compiler knows Item exists. I have pointers from this class in many places so i need this here

class Menu : public ItemList //inheritance
{

public:

    //Menu constructor
    Menu(std::string filepath);

    //
    virtual std::string toString() const override; //this is to display the menu

    //converts all letters in a string to lowercase so it's easier to handle input
    std::string wordsToLowerCase(const std::string& str) const;

    //This is to get all the pointers into a vector to present it for the receipt output
    std::vector<Item*> getTheMenuItemsForReceipt() const;


    //this prints the menu items according to its type
    void printTheMenuItemsByType(char itemType) const;

    //Gets the item on the menu depedning on its menu number
    Item* getTheItemOnMenu(int index) const;

    //Gets the size of the menu
    int getTheMenuSize() const;

    //Finds the menu item using its name
    Item* findTheMenuItemByName(const std::string& itemName) const;


    //sorts the menu in ascending order
    void sortTheMenuAscendingOrder();

    //sorts the menu in descending order
    void sortTheMenuDescendingOrder();


    ~Menu(); // desctructor

private:

    //this stores a list of pointers to Item that holds the menu items
    std::vector<Item*> ItemsonMenu;

    //sorts the menu by price depedning on the type of item whether its main course, appetizer, or beverage
    void sortTheMenuItemsByPrice(char itemType, bool ascending);
};

#endif