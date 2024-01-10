#include "order.h"
#include "utility.h"
#include "menu.h"
#include "item.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>


//this is initilizing the Order class
//I'm creating an empty list to store the menu items for our customers order later on
Order::Order() : itemsInOrder() {}

Order::~Order() {} //don't want to delete items in order because it would be double deletion with items in the menu. we want menu to stay constant and items in order to be pointers to the menu that we can delete and add


//This function is to add an item to the order
void Order::addAnItemToOrder(Item* item)
{
    itemsInOrder.push_back(item);
    std::cout << item->getTheMenuFoodName() << " has been added to your order!" << std::endl;
}


//This is to remove the item from the customer's order
void Order::removeAnItemFromOrder(int index)
{
    if (index > 0 && index <= static_cast<int>(itemsInOrder.size()))
    {

        Item* removedItem = itemsInOrder[index - 1];
        if (removedItem)
        {
            std::cout << itemsInOrder[index - 1]->getTheMenuFoodName() << " has been removed from your order!" << std::endl;

            itemsInOrder.erase(itemsInOrder.begin() + index - 1);
        }

    }
    else
    {
        std::cerr << "Invalid index for removal of item." << std::endl;
    }
}


//This calculates the customer's order total, accounting for the two for one deals and shareable appetizers too, applying discounts too
double Order::calculateTotal() const
{
    double total_amount = 0.0;
    double total_discount = 0.0;
    int eligible_twoForOne = 0;

    for (const auto& item : itemsInOrder)
    {
        total_amount += item->getTheMenuFoodPrice();

        //i am checking if two for one applies
        if (item->getTheFoodType() == 'a' && dynamic_cast<Appetiser*>(item)->getFoodTwoForOne())
        {

            eligible_twoForOne++;
            if (eligible_twoForOne % 2 == 0)
            {
                total_discount += item->getTheMenuFoodPrice();
            }
        }
    }

    if (eligible_twoForOne >= 2)
    {

        total_amount -= total_discount;

        std::cout << "2-4-1 discount has been applied! Your savings is: $" << std::fixed << std::setprecision(2) << total_discount << std::endl;
    }

    return total_amount;
}

//This is the output that you can see in the terminal
std::string Order::toString() const
{
    std::stringstream result;
    result << "===== ORDER =====\n";

    int indexItem = 1;
    double total = 0.0;
    double savings = 0.0;
    int eligible_twoForOne = 0;

    for (const auto& item : itemsInOrder)
    {
        result << "(" << indexItem << ")" << item->toString() << "\n";
        total += item->getTheMenuFoodPrice();

        if (item->getTheFoodType() == 'a' && dynamic_cast<Appetiser*>(item)->getFoodTwoForOne())
        {
            eligible_twoForOne++;
            if (eligible_twoForOne % 2 == 0)
            {
                savings += item->getTheMenuFoodPrice();
            }
        }

        indexItem++;
    }

    if (eligible_twoForOne >= 2)
    {
        total -= savings;
        result << "Total: $" << std::fixed << std::setprecision(2) << total << "\n";
        result << "Savings: $" << std::fixed << std::setprecision(2) << savings << "\n";
    }
    else
    {
        result << "Total: $" << std::fixed << std::setprecision(2) << total << "\n";
        result << "Savings: $0.00\n";
    }

    return result.str();
}


//This is opening the .txt file in the project folder and writing to the text file the customer's order, mimicking printing out a receipt
void Order::printReceipt(const std::string& filePath) const
{

    std::ofstream receiptFile(filePath); //receipt.txt file path
    if (receiptFile.is_open())
    {
        receiptFile << toString();
        receiptFile.close();
        std::cout << "Receipt has been written to the text file receipt.txt" << std::endl;
    }
    else
    {
        std::cout << "Error: Unable to open receipt.txt." << std::endl;
    }
}

//This retrieves how many things are in the cusomter's order currently
int Order::getTheOrderSize() const
{
    return static_cast<int>(itemsInOrder.size());
}


//This is returning a reference to the list containing the menu items in the order
const std::vector<Item*>& Order::getTheOrderedItems() const
{
    return itemsInOrder;
}