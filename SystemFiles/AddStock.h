#ifndef ADDSTOCK_H
#define ADDSTOCK_H
#include "PlantInventory.h"
#include "StockCommand.h"
#include <string>

/**
 * @class AddStock
 * @brief Concrete command for adding plant stock to inventory
 *
 * This class implements the Command pattern to add a specified
 * quantity of plants to the target inventory.
 */
class AddStock : public StockCommand
{
  private:
    Plant *plant;
    int quantityToAdd;
    PlantInventory *targetInventory;

  public:
    /**
     * @brief Constructs an AddStock command
     * @param plant Plant to add
     * @param quantityToAdd Quantity to add
     * @param targetInventory Inventory to add to
     */
    AddStock(Plant *plant, int quantityToAdd, PlantInventory *targetInventory);

    /**
     * @brief Executes the add stock command
     * @return true if successful, false otherwise
     */
    bool execute() override;
};

#endif
