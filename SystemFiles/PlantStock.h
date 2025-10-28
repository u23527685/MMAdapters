#ifndef PLANTSTOCK_H
#define PLANTSTOCK_H
#include "StockCommand.h"
#include "AddStock.h"
#include "RemoveStock.h"
#include "Plant.h"
#include "PlantInventory.h"
#include <string>

// PlantStock acts as the Invoker in the Command pattern
class PlantStock {
private:
    PlantInventory* inventory;

public:
    PlantStock(PlantInventory* inventory);
    ~PlantStock();

    // Command execution methods
    bool addStock(Plant* plant, int quantity);
    bool removeStock(Plant* plant, int quantity);
};

#endif
