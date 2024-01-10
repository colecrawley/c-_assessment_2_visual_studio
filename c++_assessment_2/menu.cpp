#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "utility.h"
#include "Itemlist.h"
#include "item.h"
#include "menu.h"
#include "order.h"
#include <cstdlib>
#include <map>
#include <algorithm>


//Menu Constructor with filepath for the menu.csv file
Menu::Menu(std::string filepath) {
    std::ifstream file(filepath);


    //checks if the program can access the file, if not, throw out this error
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filepath << std::endl;
        return;
    }


    //this parses each line and checks the data on the csv file
    std::string line = "";

    while (std::getline(file, line)) {
        char itemtype = 'O';
        std::string name = "";
        double price = 0.0;
        int calories = 0;
        bool shareable = false;
        bool twoForOne = false;
        double abv = 0.0;
        int volume = 0;

        int counter = 0;
        std::string value = "";

        //on the csv file, it is separate into commas, so after each comma, it's a different attribute of the menu item

        //so I used a switch case to determine what attribute it is because the istringstream wasn't working for me

        for (int i = 0; i <= line.size() - 1; i++) {
            if (line[i] == ',' || i >= line.size() - 1) {
                switch (counter) {
                case 0: itemtype = value[0]; break;
                case 1: name = value; break;
                case 2: price = atof(value.c_str()); break;
                case 3: calories = atoi(value.c_str()); break;
                case 4: if (value == "y") {
                    shareable = true;
                } break;
                case 5: if (value == "y") {
                    twoForOne = true;
                } break;
                case 6: volume = atoi(value.c_str()); break;
                case 7: abv = atof(value.c_str()); break;
                }

                value = "";
                counter += 1;
            }
            else {
                value += line[i];
            }
        }

        //this here is to make sure that every single item has tha main 4 attributes. name, price, calories and type
        if (counter < 4) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }

        //this is determinging the type of menu item it is and adding it to its corresponding list

        //These menu items are then added to the ItemsonMenu list which will store all the menu items
        switch (itemtype) {
        case 'a':
        {
            ItemsonMenu.push_back(new Appetiser(name, price, calories, shareable, twoForOne));
            break;
        }
        case 'b':
        {
            // Check for the presence of volume, abv, and discard remaining values
            if (volume >= 0 && abv >= 0.0) {
                ItemsonMenu.push_back(new Beverage(name, price, calories, abv, volume));
            }
            else {
                std::cerr << "Error parsing beverage: " << line << std::endl;
                continue;
            }
            break;
        }

        case 'm':
        {
            ItemsonMenu.push_back(new MainCourse(name, price, calories));
            break;
        }

        //if there is as item that is not listed on the menu then it throw an error for it
        default:
        {
            std::cerr << "Unknown menu item type: " << itemtype << " in line: " << line << std::endl;
            break;
        }
        }
    }

    file.close();
}

//This is the menu destructor
Menu::~Menu() {}


//This goes through everything in the Itemsonmenu list and prints each item on the list
void Menu::printTheMenuItemsByType(char itemType) const
{
    for (const auto& item : ItemsonMenu)
    {
        if (item->getTheFoodType() == itemType)
        {
            std::cout << item->toString() << std::endl;
        }
    }
}


//This is the main output of the Menu, with all the formatting and categorization
std::string Menu::toString() const {
    std::stringstream result;
    result << "========== Menu By Cole Crawley ==========\n";

    int itemNumber = 1; // menu item starts at 1

    // these are the different caterogies that the menu is split by
    std::map<char, std::string> categories = {
        {'a', "Appetizers"},
        {'b', "Beverages"},
        {'m', "Main Course"}
    };

    // this is a lambda function to print out the items on the menu in a neat way
    auto printItemsByCategory = [&](char itemType) {
        result << "========== " << categories[itemType] << " ==========\n";
        for (const auto& item : ItemsonMenu) {
            if (item->getTheFoodType() == itemType) {
                result << "(" << itemNumber++ << ") " << item->toString() << "\n";
            }
        }
        };

    //this one prints all the items for each category
    for (const auto& categoryPair : categories) {
        printItemsByCategory(categoryPair.first);
    }

    return result.str();
}


//This retrieves the number of menu items on the menu
int Menu::getTheMenuSize() const {
    return static_cast<int>(ItemsonMenu.size());
}


//This gives us the specific menu item from its numbered position, it searches by using the items type whether it be Appetizer, beverage or main course
Item* Menu::getTheItemOnMenu(int index) const {
    int itemNumber = 0;

    //appetizer
    for (const auto& item : ItemsonMenu) {
        if (item->getTheFoodType() == 'a') {
            if (index == itemNumber) {
                return item;
            }
            itemNumber++;
        }
    }

    //beverage
    for (const auto& item : ItemsonMenu) {
        if (item->getTheFoodType() == 'b') {
            if (index == itemNumber) {
                return item;
            }
            itemNumber++;
        }
    }

    //main course
    for (const auto& item : ItemsonMenu) {
        if (item->getTheFoodType() == 'm') {
            if (index == itemNumber) {
                return item;
            }
            itemNumber++;
        }
    }

    return nullptr;
}


//I use this to find the menu item using its name, I've implemented a toLowercase function to handle input in a neat and consistent way so that there are no errors when searching for names on the menu
Item* Menu::findTheMenuItemByName(const std::string& itemName) const
{

    //this is the function where I format the inputs to lower case
    std::string lowercaseFood = wordsToLowerCase(itemName);

    int index = 1; // Starting menu item number

    for (const auto& item : ItemsonMenu)
    {
        std::string currentFoodName = wordsToLowerCase(item->getTheMenuFoodName());

        if (currentFoodName == lowercaseFood)
        {
            return item;
        }

        //this one adds to the index so it moves on to the nest item in the menu
        ++index;
    }

    return nullptr;
}


//This function is what is used above, it turns all input into lowercase strings so that it is easier and more consistent to handle data
std::string Menu::wordsToLowerCase(const std::string& str) const
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


//This function gives us a list that contains pointers to the menu items, it is for the outputting to the reciept file
std::vector<Item*> Menu::getTheMenuItemsForReceipt() const
{
    return ItemsonMenu;

}

//This sorts the menu and each category in ascending order in terms of price
void Menu::sortTheMenuAscendingOrder() {
    sortTheMenuItemsByPrice('a', true);  //Appetizers
    sortTheMenuItemsByPrice('b', true);  //Beverages
    sortTheMenuItemsByPrice('m', true);  //Main Course
}

//This sorts the menu and each category in descending order in terms of price
void Menu::sortTheMenuDescendingOrder() {
    sortTheMenuItemsByPrice('a', false);  //Appetizers
    sortTheMenuItemsByPrice('b', false);  //Beverages
    sortTheMenuItemsByPrice('m', false);  //Main Course
}


//This is the function that allows us to sort the menu items in either ascending or descending order based on the brief
void Menu::sortTheMenuItemsByPrice(char itemType, bool ascending)
{

    std::vector<Item*> categoryItems;

    // we create a new list and add the menu items into that list above
    for (const auto& item : ItemsonMenu) {
        if (item->getTheFoodType() == itemType) {
            categoryItems.push_back(item);
        }
    }

    // I am sorting the items here based on price using a lambda function so its a more quick way of typing it out. It sorts it and it checks the boolean value ascending, if we give it the value true, it is ascending, if it is false, it is descending
    std::sort(categoryItems.begin(), categoryItems.end(), [ascending](Item* a, Item* b) {
        return ascending ? a->getTheMenuFoodPrice() < b->getTheMenuFoodPrice() : a->getTheMenuFoodPrice() > b->getTheMenuFoodPrice();
        });

    // referesh the original list with the new items in order
    int categoryIndex = 0;
    for (auto& item : ItemsonMenu) {
        if (item->getTheFoodType() == itemType) {
            item = categoryItems[categoryIndex++];
        }
    }
}