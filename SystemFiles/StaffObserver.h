#ifndef STAFFOBSERVER_H
#define STAFFOBSERVER_H

#include "InventoryObserver.h"
#include "PlantInventory.h"
#include <string>
#include <utility>
#include <vector>

/**
 * @class StaffObserver
 * @brief Concrete observer that tracks inventory for staff
 *
 * This observer monitors inventory changes and maintains
 * internal tracking for staff members.
 */
class StaffObserver : public InventoryObserver
{
  private:
  public:
    /**
     * @brief Constructs a staff observer
     * @param inventory Inventory to observe
     */
    StaffObserver(PlantInventory *inventory);

    /**
     * @brief Updates when inventory changes
     */
    void update() override;
};
#endif
