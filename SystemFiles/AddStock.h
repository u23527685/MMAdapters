#ifndef ADDSTOCK_H
#define ADDSTOCK_H
#include "StockCommand.h"
#include "PlantInventory.h"
#include <string>

class AddStock : public StockCommand {
private:
    Plant* plant;
    int quantityToAdd;
    PlantInventory* targetInventory;
public:
    AddStock(Plant* plant, int quantityToAdd, PlantInventory* targetInventory);
    bool execute() override;
};

#endif
