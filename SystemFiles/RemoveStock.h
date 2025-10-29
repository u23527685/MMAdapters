#ifndef REMOVESTOCK_H
#define REMOVESTOCK_H
#include "StockCommand.h"
#include "PlantInventory.h"
#include <string>

class RemoveStock : public StockCommand {
private:
    Plant* plant;
    int quantityToRemove;
    PlantInventory* targetInventory;
public:
    RemoveStock(Plant* plant, int quantityToRemove, PlantInventory* targetInventory);
    bool execute() override;
};

#endif
