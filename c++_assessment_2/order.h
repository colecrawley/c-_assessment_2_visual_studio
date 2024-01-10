#pragma once

#ifndef ORDER_H
#define ORDER_H


#include <vector>
#include "item.h"
#include "menu.h"
class Order
{

public:
    Order(); //this is the constructor for the order class
    ~Order(); //this is the destructor as well for the order class

    //This function is made to add a food or drink item to the order. I'm using a pointer to the Item object
    void addAnItemToOrder(Item* item);

    //This function is similar to the add function however, it just removes the item from the order by its indexed location (numbered order)
    void removeAnItemFromOrder(int index);

    //This function is used to calculate the total cost of the user's order, taking into account the two for one deals
    double calculateTotal() const;

    //This is used to turn the representation on the terminal into a string to make everything cohesive
    std::string toString() const; //doesn't need to be virtual because no derived classes

    //This method prints out the receipt to an external file called receipt.txt to mimic the receipt given to customers in real restaurants
    void printReceipt(const std::string& filePath) const;


    //This function retrieves how many food or drinks are on the current order
    int getTheOrderSize() const;


    //This is a list that retrieves the current order of Items on the menu
    const std::vector<Item*>& getTheOrderedItems() const;

private:

    //This stores the food or drinks in an order.
    std::vector<Item*> itemsInOrder;

};

#endif