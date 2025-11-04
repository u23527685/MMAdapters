/**
 * @file RemoveStock.h
 * @brief Defines the RemoveStock command for decreasing inventory.
 *
 * Implements the Command pattern to remove a specified quantity
 * of a given plant from the PlantInventory.
 *
 * @see StockCommand
 * @see PlantInventory
 * @see AddStock
 *
 */

#ifndef REMOVESTOCK_H
#define REMOVESTOCK_H
#include "StockCommand.h"
#include "PlantInventory.h"
#include <string>

/**
 * @class RemoveStock
 * @brief Concrete command that removes plant stock from the inventory.
 */
class RemoveStock : public StockCommand {
private:
    Plant* plant; ///< The plant to remove.
    int quantityToRemove; ///< Quantity to remove from inventory.
    PlantInventory* targetInventory; ///< The inventory target for removal.
public:
    /**
     * @brief Constructs a RemoveStock command
     * @param plant Plant to remove
     * @param quantityToRemove Quantity to remove
     * @param targetInventory Inventory to remove from
     */
    RemoveStock(Plant* plant, int quantityToRemove, PlantInventory* targetInventory);
    
    /**
     * @brief Executes the remove stock command
     * @return true if successful, false otherwise
     */
    bool execute() override;
};

#endif
