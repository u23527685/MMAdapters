#include "InventoryProxy.h"

InventoryProxy::InventoryProxy(SalesFloorObserver *observer)
    : inventory(PlantInventory::getInstance()), salesObserver(observer)
{
}

bool InventoryProxy::buyPlant(Plant *plant, int quantity)
{
    std::string desc = plant ? plant->getDescription() : "(unknown)";
    bool result = inventory->removeStock(plant, quantity);
    if (result)
    {
        std::cout << "Customer bought " << quantity << " " << desc
                  << (quantity == 1 ? " plant." : " plants.") << std::endl;
    }
    else
    {
        std::cout << "Purchase failed: Not enough stock or invalid request."
                  << std::endl;
    }
    return result;
}

void InventoryProxy::addStock(Plant *plant, int quantity)
{
    std::cout << "Exception: Access denied: Customers cannot add stock."
              << std::endl;
}

void InventoryProxy::removeStock(Plant *, int)
{
    std::cout
        << "Exception: Access denied: Customers cannot remove stock directly."
        << std::endl;
}