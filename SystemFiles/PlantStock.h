#ifndef PLANTSTOCK_H
#define PLANTSTOCK_H
#include "AddStock.h"
#include "Plant.h"
#include "PlantInventory.h"
#include "RemoveStock.h"
#include "StockCommand.h"
#include <string>

/**
 * @class PlantStock
 * @brief Acts as the Invoker in the Command pattern
 *
 * This class creates and executes stock commands for adding
 * and removing plants from inventory.
 */
class PlantStock
{
  private:
    PlantInventory *inventory;

  public:
    /**
     * @brief Constructs a PlantStock invoker
     * @param inventory Pointer to the inventory to manage
     */
    PlantStock(PlantInventory *inventory);

    ~PlantStock();

    /**
     * @brief Adds stock to inventory via command
     * @param plant Plant to add
     * @param quantity Quantity to add
     * @return true if successful
     */
    bool addStock(Plant *plant, int quantity);

    /**
     * @brief Removes stock from inventory via command
     * @param plant Plant to remove
     * @param quantity Quantity to remove
     * @return true if successful
     */
    bool removeStock(Plant *plant, int quantity);
};

#endif
