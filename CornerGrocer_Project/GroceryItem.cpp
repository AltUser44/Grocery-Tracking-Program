#include "GroceryItem.h"

GroceryItem::GroceryItem(const std::string& itemName)
    : name(itemName), quantity(0), aisleLocation(""), barcodeId(-1) {
}

GroceryItem::~GroceryItem() {}

void GroceryItem::setName(const std::string& itemName) {
    name = itemName;
}

std::string GroceryItem::getName() const {
    return name;
}

void GroceryItem::setQuantity(int q) {
    quantity = q;
}

int GroceryItem::getQuantity() const {
    return quantity;
}

void GroceryItem::incrementQuantity(int delta) {
    quantity += delta;
}

void GroceryItem::setAisle(const std::string& aisle) {
    aisleLocation = aisle;
}

std::string GroceryItem::getAisle() const {
    return aisleLocation;
}

void GroceryItem::setBarcode(int id) {
    barcodeId = id;
}

int GroceryItem::getBarcode() const {
    return barcodeId;
}