#pragma once

#ifndef ITEM_H
#define ITEM_H


#include <string>

class Item
{

public:

    //This is my workign constructor for the Item Class
    Item(std::string name, double price, int calories);

    //Of course, you need a destructor too
    virtual ~Item(); //this is virtual too because we need to support the polymorhic aspects of the project

    //Retrieves the food or drink name on the menu
    std::string getTheMenuFoodName() const;

    //retrieves the food or drink price on the menu
    double getTheMenuFoodPrice() const;

    //retrieves the food or drink claroies on the menu
    int getTheMenuFoodCalories() const;

    //retrieves the food or drink type (whether its an appetiser, beverage or main course)
    virtual char getTheFoodType() const = 0;


    //coverts everything and displays it on the terminal in a string form
    virtual std::string toString() const = 0; // This is the pure virtual function that is meant to override in each child class


private:

    std::string name; // name of the food or drink item
    double price;// price of the food or drink item
    int calories;// calories of the food or drink item

};

class Appetiser : public Item //appetizer is a derived class from Item (inheritance)

{
public:

    //Constructor for appetizer
    Appetiser(std::string name, double price, int calories, bool shareable, bool twoForOne);

    //Converts ooutput to string
    virtual std::string toString() const override;

    //Retrieves the type of appetizer and returns it
    char getTheFoodType() const override { return 'a'; }

    //This is a function to check is the food item or drink is shareable
    bool getFoodShareable();

    //This is a function to check if the food or drink applies to the two for one deal
    bool getFoodTwoForOne();

private:
    bool shareable;
    bool twoForOne;

};

class MainCourse : public Item //inhertiance, derived class
{

public:

    //Constructor for the main course
    MainCourse(std::string name, double price, int calories);

    //Converts output to string
    virtual std::string toString() const override;

    //Returns the type of main course
    char getTheFoodType() const override { return 'm'; }

};

class Beverage : public Item //inehritance again
{
public:

    //constructor for the beverage
    Beverage(std::string name, double price, int calories, double abv, int volume);

    //turns all output to string format
    virtual std::string toString() const override;

    //this overrides the virtual function to change depending on the food type
    char getTheFoodType() const override { return 'b'; }

    //retrieves the volume within the drink
    int getTheDrinkVolume() const;

    //retrieves the alcohol percentage in the drink is it is alcoholic
    double getTheDrinkABV() const;



private:
    double abv;
    int volume;
};


#endif