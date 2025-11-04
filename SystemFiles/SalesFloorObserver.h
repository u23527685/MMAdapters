#ifndef SALESFLOOROBSERVER_H
#define SALESFLOOROBSERVER_H

#include "InventoryObserver.h"
#include "PlantInventory.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

class Staff;

/**
 * @class SalesFloorObserver
 * @brief Concrete observer that manages sales floor inventory display
 *
 * This observer tracks available plants on the sales floor and
 * notifies staff members of inventory changes.
 */
class SalesFloorObserver : public InventoryObserver
{
  private:
    std::vector<std::pair<Plant *, int>> availableItems;
    std::vector<Staff *> notifiedStaff;
    std::map<Plant *, std::string> plantDescriptions;
    std::vector<std::string>
        notificationHistory; // Stores all past notifications

  public:
    /**
     * @brief Constructs a sales floor observer
     * @param inventory Inventory to observe
     */
    SalesFloorObserver(PlantInventory *inventory);

    /**
     * @brief Updates sales floor when inventory changes
     */
    void update() override;

    /**
     * @brief Displays all available plants on sales floor
     */
    void displayAvailablePlants() const;

    /**
     * @brief Checks if a plant is available
     * @param plant Plant to check
     * @return true if plant is available (quantity > 0)
     */
    bool isPlantAvailable(Plant *plant) const;

    /**
     * @brief Gets available items on sales floor
     * @return Const reference to available items
     */
    const std::vector<std::pair<Plant *, int>> &getAvailableItems() const
    {
        return availableItems;
    }

    /**
     * @brief Gets quantity of a specific plant
     * @param plant Plant to query
     * @return Quantity available
     */
    int getPlantQuantity(Plant *plant) const;

    /**
     * @brief Attaches a staff member for notifications
     * @param staff Staff member to attach
     */
    void attachStaff(Staff *staff);

    /**
     * @brief Detaches a staff member from notifications
     * @param staff Staff member to detach
     */
    void detachStaff(Staff *staff);

    /**
     * @brief Notifies all staff members with a message
     * @param message Message to send to staff
     */
    void notifyStaff(const std::string &message);

    /**
     * @brief Gets all past notifications
     * @return Const reference to notification history
     */
    const std::vector<std::string> &getNotificationHistory() const
    {
        return notificationHistory;
    }
};

#endif
