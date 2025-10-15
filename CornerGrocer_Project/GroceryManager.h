#ifndef GROCERYMANAGER_H
#define GROCERYMANAGER_H

#include <string>
#include <vector>
#include "GroceryItem.h"

class GroceryManager {
private:
    std::vector<GroceryItem*> items;
    std::string inputFilename;
    std::string backupFilename;

    // helpers
    std::string toLower(const std::string& s) const;

    // cleanup helper
    void clearItems();

public:
    GroceryManager(const std::string& inputFile = "CS210_Project_Three_Input_File.txt",
        const std::string& backupFile = "frequency.dat");
    ~GroceryManager();

    // Load data fresh from input file into items 
    bool loadFromFile();

    // Create/update backup file with current frequencies
    bool writeBackupFile() const;

    // Reporting operations - each will call loadFromFile() internally
    int getFrequencyForItem(const std::string& name);
    void printFrequencyList();
    void printHistogram();

    // For unit testing or external access (returns number of distinct items)
    int getDistinctItemCount() const;
};

#endif // GROCERYMANAGER_H#pragma once
