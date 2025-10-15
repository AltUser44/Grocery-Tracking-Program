#include "GroceryManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>

GroceryManager::GroceryManager(const std::string& inputFile, const std::string& backupFile)
    : inputFilename(inputFile), backupFilename(backupFile) {
    // This runs an initial load, and writes backup when program is ran.
    loadFromFile();
    writeBackupFile();
}

GroceryManager::~GroceryManager() {
    clearItems();
}

void GroceryManager::clearItems() {
    for (std::size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }
    items.clear();
}

std::string GroceryManager::toLower(const std::string& s) const {
    std::string result = s;
    for (std::size_t i = 0; i < result.size(); ++i) {
        result[i] = static_cast<char>(std::tolower(result[i]));
    }
    return result;
}

bool GroceryManager::loadFromFile() {
    // Clear previous items
    clearItems();

    std::ifstream infile(inputFilename.c_str());
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open input file '" << inputFilename << "'\n";
        return false;
    }

    std::string word;
    while (infile >> word) {
        // Normalize characters to lowercase single-word item
        std::string nameLower = toLower(word);

        // Find existing item
        bool found = false;
        for (std::size_t i = 0; i < items.size(); ++i) {
            if (toLower(items[i]->getName()) == nameLower) {
                items[i]->incrementQuantity(1);
                found = true;
                break;
            }
        }
        if (!found) {
            GroceryItem* gi = new GroceryItem(word); // Keep the original casing from file thesame
            gi->setQuantity(1);
            items.push_back(gi);
        }
    }

    infile.close();
    return true;
}

bool GroceryManager::writeBackupFile() const {
    std::ofstream outfile(backupFilename.c_str());
    if (!outfile.is_open()) {
        std::cerr << "Error: Unable to write backup file '" << backupFilename << "'\n";
        return false;
    }
    for (std::size_t i = 0; i < items.size(); ++i) {
        outfile << items[i]->getName() << " " << items[i]->getQuantity() << "\n";
    }
    outfile.close();
    return true;
}

int GroceryManager::getFrequencyForItem(const std::string& name) {
    // Re-load the file to reflect any dynamic changes 
    if (!loadFromFile()) {
        return 0;
    }

    std::string queryLower = toLower(name);
    for (std::size_t i = 0; i < items.size(); ++i) {
        if (toLower(items[i]->getName()) == queryLower) {
            return items[i]->getQuantity();
        }
    }
    return 0;
}

void GroceryManager::printFrequencyList() {
    if (!loadFromFile()) {
        return;
    }

    // This sort items alphabetically for consistent output
    // This performs a simple selection-sort to avoid auto and keep types explicit
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::size_t minIndex = i;
        for (std::size_t j = i + 1; j < items.size(); ++j) {
            std::string a = toLower(items[j]->getName());
            std::string b = toLower(items[minIndex]->getName());
            if (a < b) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            GroceryItem* tmp = items[i];
            items[i] = items[minIndex];
            items[minIndex] = tmp;
        }
    }

    std::cout << "\nItem Frequency List\n";
    std::cout << "-------------------\n";
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::cout << std::left << std::setw(15) << items[i]->getName() << " : " << items[i]->getQuantity() << "\n";
    }

    // after building the report update backup file
    writeBackupFile();
}

void GroceryManager::printHistogram() {
    if (!loadFromFile()) {
        return;
    }

    // Sort alphabetically as in frequency list
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::size_t minIndex = i;
        for (std::size_t j = i + 1; j < items.size(); ++j) {
            std::string a = toLower(items[j]->getName());
            std::string b = toLower(items[minIndex]->getName());
            if (a < b) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            GroceryItem* tmp = items[i];
            items[i] = items[minIndex];
            items[minIndex] = tmp;
        }
    }

    std::cout << "\nHistogram\n";
    std::cout << "---------\n";
    for (std::size_t i = 0; i < items.size(); ++i) {
        std::cout << std::left << std::setw(15) << items[i]->getName() << " ";
        int count = items[i]->getQuantity();
        for (int s = 0; s < count; ++s) {
            std::cout << "*";
        }
        std::cout << "\n";
    }

    writeBackupFile();
}

int GroceryManager::getDistinctItemCount() const {
    return static_cast<int>(items.size());
}