#include "PlantStock.h"

PlantStock::PlantStock(PlantInventory *inventory) : inventory(inventory) {}

PlantStock::~PlantStock() {}

bool PlantStock::addStock(Plant *plant, int quantity)
{
    if (!plant || quantity <= 0)
    {
        return false;
    }
    AddStock *addCommand = new AddStock(plant, quantity, inventory);

    if (inventory)
    {
        inventory->executeCommand(addCommand);
    }
    else
    {
        delete addCommand;
    }
    return true;
}

bool PlantStock::removeStock(Plant *plant, int quantity)
{
    if (!plant || quantity <= 0)
    {
        return false;
    }
    RemoveStock *removeCommand = new RemoveStock(plant, quantity, inventory);
    if (inventory)
    {
        inventory->executeCommand(removeCommand);
    }
    else
    {
        delete removeCommand;
    }
    return true;
}
