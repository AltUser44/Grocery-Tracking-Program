/*
 * Corner Grocer - Project Three
 * Author: Jaeyy Nkese
 * Date: October 15th, 2025
 *
 * Main program: reads the input file, creates frequency.dat backup,
 * and presents a menu for frequency queries, listing, histogram, and exit.
 */

#include <iostream>
#include <string>
#include <limits>
#include "GroceryManager.h"

 // Display the menu options and display program title.
int getMenuChoice() {
    int choice = 0;
    bool validChoice = false;

    while (!validChoice) {
        std::cout << "**************************************************\n";
        std::cout << "*              CORNER GROCER PROJECT             *\n";
        std::cout << "*           Grocery Tracking Program             *\n";
        std::cout << "**************************************************\n";
        std::cout << "\nMenu:\n";
        std::cout << "1 - Get frequency of a specific item\n";
        std::cout << "2 - Print frequency list for all items\n";
        std::cout << "3 - Print histogram for all items\n";
        std::cout << "4 - Exit\n";
        std::cout << "Enter choice (1-4): ";

        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 4) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                validChoice = true;
            }
            else {
                std::cout << "Invalid choice. Enter 1-4.\n";
            }
        }
        else {
            std::cout << "Invalid input. Please enter a number 1-4.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return choice;
}

std::string getItemQuery() {
    std::string item;
    bool gotValidItem = false;

    while (!gotValidItem) {
        std::cout << "Enter item name to search (case-insensitive single word): ";
        if (std::cin >> item) {
            // check validation: word only (no spaces) and no empty inputs.
            if (!item.empty()) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                gotValidItem = true;
            }
            else {
                std::cout << "Invalid input. Try again.\n";
            }
        }
        else {
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return item;
}

int main() {
    GroceryManager manager("CS210_Project_Three_Input_File.txt", "frequency.dat");

    bool running = true;
    while (running) {
        int choice = getMenuChoice();

        if (choice == 1) {
            std::string query = getItemQuery();
            int freq = manager.getFrequencyForItem(query);
            // Preserve user case by printing query as typed.
            std::cout << query << " : " << freq << "\n";
        }
        else if (choice == 2) {
            manager.printFrequencyList();
        }
        else if (choice == 3) {
            manager.printHistogram();
        }
        else if (choice == 4) {
            std::cout << "Exiting program. Goodbye.\n";
            running = false;
        }
    }

    return 0;
}
