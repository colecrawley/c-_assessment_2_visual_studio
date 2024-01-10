//Have to include the necessary headers to call the other files in this project
#include <stdio.h>
#include <iostream>
#include "menu.h"
#include "order.h"
#include "item.h"

//start
int main() {

    //ccreate a new instance of the menu using the Menu.csv file as the file path to get the items from the csv file
    Menu menu("menu.csv");

    //create a new instance of the order class
    Order order;

    //while loop that keeps running unless told to stop by a break
    while (true)
    {

        //Menu format
        std::cout << "\n========== Welcome to Cole's Restaurant Menu! ==========\n";
        std::cout << "1. View Menu in ascending order\n";
        std::cout << "2. View Menu in descending order\n";
        std::cout << "3. Add food to Order\n";
        std::cout << "4. Remove food from order\n";
        std::cout << "5. View your Order\n";
        std::cout << "6. Print Receipt\n";
        std::cout << "7. Order Multiple items at once\n";
        std::cout << "8. Exit Restaurant\n";
        std::cout << "=========================================================\n";

        //user input
        int user_choice;

        //this is error handling in case a user inputs something that is not a number or a number that is outside the boundaries
        while (true)
        {
            std::cout << "Enter a number: ";
            std::cin >> user_choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid answer, please try again! " << std::endl;
            }
            else
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }

        //this is a switch case based on the user's input, each number is a different swtich case that does something else
        switch (user_choice)
        {

            //Viewing the menu in ascending order in terms of price
        case 1:
            menu.sortTheMenuAscendingOrder();
            std::cout << menu.toString() << std::endl;
            break;

            //Viewing the menu in descending order in terms of price
        case 2:
            menu.sortTheMenuDescendingOrder();
            std::cout << menu.toString() << std::endl;
            break;


            //This is the user adding food to the order, if not found, an error is thrown out and user is prompted again
        case 3:
        {
            std::string foodName;
            std::cout << "Enter the number of the item to add: ";
            int itemNumber;
            std::cin >> itemNumber;

            if (itemNumber >= 1 && itemNumber <= menu.getTheMenuSize())
            {
                Item* chosenItem = menu.getTheItemOnMenu(itemNumber - 1);
                order.addAnItemToOrder(chosenItem);
            }
            else
            {
                std::cout << "Food or Beverage is not found on the menu!\n";
            }
            break;
        }


        //This is to remove an item from the order, it shows the current order to the customer and then allows them to choose the number of the item they want to remove
        case 4:
        {
            std::cout << "========== Your Order ==========\n";
            const std::vector<Item*>& orderedItems = order.getTheOrderedItems();

            for (int i = 0; i < orderedItems.size(); ++i)
            {
                std::cout << i + 1 << ".) " << orderedItems[i]->toString() << "\n";
            }

            int removedItem;

            std::cout << "Enter the number of the food or beverage to remove: ";
            std::cin >> removedItem;

            if (removedItem > 0 && removedItem <= orderedItems.size())
            {
                order.removeAnItemFromOrder(removedItem);
            }
            else
            {
                std::cout << "Entered number is not on your order. No item has been removed.\n";
            }
            break;
        }


        //This displays the current order to the customer
        case 5:
        {

            std::cout << "========== Your Order ==========\n";

            const std::vector<Item*>& orderedItems = order.getTheOrderedItems();

            for (int i = 0; i < order.getTheOrderSize(); ++i)
            {
                std::cout << i + 1 << ".) " << orderedItems[i]->toString() << "\n";
            }

            std::cout << "Order Total: $" << order.calculateTotal() << std::endl;
            break;
        }


        //This prints out the current order to the external file receipt.txt as a receipt for the customer
        case 6:
            order.printReceipt("receipt.txt");
            break;


            //This allows the customer to order multiple items at once, separating each number of the menu item with a space. When they are done adding the items to the order, you finish it by typing -1
        case 7:

        {
            std::cout << menu.toString();

            std::vector<int> itemIndices;
            int itemIndex;

            std::cout << "Enter the numbers of the items on the menu you want to add to your order (separate your choices with spaces, finish with -1): ";

            while (std::cin >> itemIndex)
            {
                if (itemIndex == -1) //if user types -1, they are finished
                {
                    break;
                }
                itemIndices.push_back(itemIndex);
            }

            for (int index : itemIndices)
            {
                if (index >= 1 && index <= menu.getTheMenuSize())
                {
                    Item* chosenItem = menu.getTheItemOnMenu(index - 1);
                    order.addAnItemToOrder(chosenItem);
                }
                else
                {
                    std::cout << "Invalid item number " << index << ". Item skipped.";
                }
            }
            break;
        }


        //Exits the program
        case 8:
            std::cout << "Exiting the Restaurant.\n";
            return 0;


            //this is the catch all, if the user inputs something that is not part of the choices, they will get prompted again
        default:
            std::cout << "Invalid choice, please try again!";
        }
    }

    //main returns 0 if the program is successful
    return 0;
}