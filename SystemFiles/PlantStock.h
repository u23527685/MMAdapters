#ifndef PLANT_STOCK_H
#define PLANT_STOCK_H

#include <string>
#include <iostream>
#include <map>

class PlantStock {
public:
    bool addStock(std::string plantName, int quantity);
    bool removeStock(std::string plantName, int quantity);
    int getQuantity(std::string plantName) const;
    void displayInventory() const;

private:
    std::map<std::string, int> inventory;
};

#endif
