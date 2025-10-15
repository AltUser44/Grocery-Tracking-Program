/*
 * Corner Grocer - Project Three
 * Author: Jaeyy Nkese
 * Date: October 14th, 2025
 *
 * Main program: reads the input file, creates frequency.dat backup,
 * and presents a menu for frequency queries, listing, histogram, and exit.
 */

#include <iostream>
#include <string>
#include "GroceryTracker.h"
#include <limits>

using namespace std;

int main() {
    const string inputFile = "CS210_Project_Three_Input_File.txt";
    const string backupFile = "frequency.dat";

    cout << "Corner Grocer - Grocery Tracking Program\n";

    GroceryTracker tracker;
    if (!tracker.loadFromFile(inputFile)) {
        cerr << "Error: Failed to open input file '" << inputFile << "'. Make sure the file exists in the program folder.\n";
        return 1;
    }

    // create backup file at program start (requirement)
    if (!tracker.writeBackup(backupFile)) {
        cerr << "Warning: Could not write backup file '" << backupFile << "'.\n";
    }

    bool running = true;
    while (running) {
        cout << "\nMenu:\n";
        cout << "1 - Get frequency of a specific item\n";
        cout << "2 - Print frequency list for all items\n";
        cout << "3 - Print histogram for all items\n";
        cout << "4 - Exit\n";
        cout << "Enter choice (1-4): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number 1-4.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // consume rest of line

        switch (choice) {
        case 1: {
            cout << "Enter item name to search (case-insensitive single word): ";
            string item;
            if (!(cin >> item)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input.\n";
                break;
            }
            size_t freq = tracker.getFrequency(item);
            cout << item << " : " << freq << '\n';
            break;
        }
        case 2:
            tracker.printFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            cout << "Exiting program. Goodbye.\n";
            running = false;
            break;
        default:
            cout << "Please enter a valid option (1-4).\n";
            break;
        }
    }

    return 0;
}
