#include "item.h"
#include "menu.h"
#include "Itemlist.h"
#include <sstream>
#include <iomanip>


//Initializing the Item, with name, price and calories
Item::Item(std::string name, double price, int calories) : name(name), price(price), calories(calories) {}


//This is the output for the terminal
std::string Item::toString() const
{
    std::stringstream result;
    result << getTheMenuFoodName() << ": $" << getTheMenuFoodPrice() << ", " << getTheMenuFoodCalories() << " calories";

    return result.str();
}

//This is my Item destructor
Item::~Item() {}


//This return the name from the menu
std::string Item::getTheMenuFoodName() const
{
    return name;
}


//This returns the price from the menu
double Item::getTheMenuFoodPrice() const
{
    return price;
}


////This returns the calories from the menu
int Item::getTheMenuFoodCalories() const
{
    return calories;
}


//This is the appetizer constructor being initialized
Appetiser::Appetiser(std::string name, double price, int calories, bool shareable, bool twoForOne) : Item(name, price, calories), shareable(shareable), twoForOne(twoForOne) {}


//Output for the terminal
std::string Appetiser::toString() const
{
    std::stringstream result;

    result << Item::getTheMenuFoodName() << ": $" << Item::getTheMenuFoodPrice() << ", " << Item::getTheMenuFoodCalories() << " calories, ";

    if (shareable)
    {
        result << " (shareable)";
    }
    if (twoForOne)
    {
        result << " (twoForOne)";
    }

    return result.str();

};


//Returns the shareable data
bool Appetiser::getFoodShareable()
{
    return shareable;
}


//returns the two for one data
bool Appetiser::getFoodTwoForOne()
{
    return twoForOne;
}


//Initializing the main course object
MainCourse::MainCourse(std::string name, double price, int calories) : Item(name, price, calories) {}


//Outputs to the terminal
std::string MainCourse::toString() const
{
    std::stringstream result;

    result << Item::getTheMenuFoodName() << ": $" << Item::getTheMenuFoodPrice() << ", " << Item::getTheMenuFoodCalories() << " calories";

    return result.str();
}


//Initilizes the beverage object
Beverage::Beverage(std::string name, double price, int calories, double abv, int volume) : Item(name, price, calories), abv(abv), volume(volume) {}


//Outputs to the terminal
std::string Beverage::toString() const
{
    std::stringstream result;

    result << getTheMenuFoodName() << ": $" << std::fixed << std::setprecision(2) << getTheMenuFoodPrice() << ": "
        << std::to_string(getTheMenuFoodCalories()) << " calories, " << std::to_string(getTheDrinkVolume())
        << "ml, " << std::fixed << std::setprecision(2) << getTheDrinkABV() << "%";


    return result.str();
}


//Returns the alcohol value
double Beverage::getTheDrinkABV() const
{
    return abv;
}


//returns the volume value
int Beverage::getTheDrinkVolume() const
{
    return volume;
}