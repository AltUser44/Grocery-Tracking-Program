#ifndef GROCERYTRACKER_H
#define GROCERYTRACKER_H

#include <string>
#include <map>

class GroceryTracker {
public:
    GroceryTracker();
    // Load items from input file (one word per line). Returns false on failure.
    bool loadFromFile(const std::string& filename);

    // Write frequency backup to file (frequency.dat)
    bool writeBackup(const std::string& filename) const;

    // Get frequency (case-insensitive) of a single item
    size_t getFrequency(const std::string& item) const;

    // Print frequency list (alphabetical by item)
    void printFrequencies() const;

    // Print histogram (item then asterisks equal to frequency)
    void printHistogram() const;

private:
    std::map<std::string, size_t> freqMap;

    // helpers
    static std::string toLowerCopy(const std::string& s);
};

#endif
#pragma once
