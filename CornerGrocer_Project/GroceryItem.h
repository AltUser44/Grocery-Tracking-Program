#ifndef GROCERYITEM_H
#define GROCERYITEM_H

#include <string>

class GroceryItem {
private:
    std::string name;
    int quantity;
    // Future-proof fields  (included for encapsulation)
    std::string aisleLocation;
    int barcodeId;

public:
    GroceryItem(const std::string& itemName);
    ~GroceryItem();

    // Data accessors and mutators - NO I/O here
    void setName(const std::string& itemName);
    std::string getName() const;

    void setQuantity(int q);
    int getQuantity() const;
    void incrementQuantity(int delta = 1);

    void setAisle(const std::string& aisle);
    std::string getAisle() const;

    void setBarcode(int id);
    int getBarcode() const;
};

#endif // GROCERYITEM_H#pragma once
