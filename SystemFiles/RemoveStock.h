#ifndef REMOVESTOCK_H
#define REMOVESTOCK_H
#include "PlantInventory.h"
#include "StockCommand.h"
#include <string>

/**
 * @class RemoveStock
 * @brief Concrete command for removing plant stock from inventory
 *
 * This class implements the Command pattern to remove a specified
 * quantity of plants from the target inventory.
 */
class RemoveStock : public StockCommand
{
  private:
    Plant *plant;
    int quantityToRemove;
    PlantInventory *targetInventory;

  public:
    /**
     * @brief Constructs a RemoveStock command
     * @param plant Plant to remove
     * @param quantityToRemove Quantity to remove
     * @param targetInventory Inventory to remove from
     */
    RemoveStock(Plant *plant, int quantityToRemove,
                PlantInventory *targetInventory);

    /**
     * @brief Executes the remove stock command
     * @return true if successful, false otherwise
     */
    bool execute() override;
};

#endif
