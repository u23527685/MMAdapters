#include "PlantInventory.h"
#include "InventoryObserver.h"
#include "SalesFloorObserver.h"
#include "Plant.h"
#include "Rose.h"
#include "Oak.h"
#include "FloorEmployee.h"

#include <iostream>
void printSeparator(const std::string& title = "") {
    std::cout << "\n";
    if (!title.empty()) {
        std::cout << "========== " << title << " ==========\n";
    } else {
        std::cout << "================================================\n";
    }
}

int main() {
    
    printSeparator("INVENTORY OBSERVER SYSTEM TEST");
    std::cout << "Testing PlantInventory with SalesFloorObserver\n";
    printSeparator();
    
    // 1. Initialize Singleton Inventory
    printSeparator("Step 1: Initialize Inventory System");
    PlantInventory* inventory = PlantInventory::getInstance();
    std::cout << "PlantInventory singleton created\n";
    
    // 2. Create Sales Floor Observer
    SalesFloorObserver* salesFloor = new SalesFloorObserver(inventory);
    std::cout << "SalesFloorObserver attached to inventory\n";
    
    // 2.5 Create and attach staff members
    printSeparator("Step 1.5: Attach Staff to Sales Floor Observer");
    FloorEmployee* john = new FloorEmployee("John");
    FloorEmployee* sarah = new FloorEmployee("Sarah");
    FloorEmployee* mike = new FloorEmployee("Mike");
    
    salesFloor->attachStaff(john);
    salesFloor->attachStaff(sarah);
    salesFloor->attachStaff(mike);
    
    std::cout << "3 staff members attached and ready for notifications\n";
    
    // 3. Create some plants
    printSeparator("Step 2: Create Plant Products");
    Rose* redRose = new Rose(25.99, "Beautiful Red Rose");
    Rose* yellowRose = new Rose(22.99, "Bright Yellow Rose");
    Plant* alienPlant = new Plant(999.99, "Mysterious Alien Plant");
    Oak* oak = new Oak(12.50, "Majestic Oak Tree");
    Oak* maple = new Oak(14.75, "Vibrant Maple Tree");


    std::cout << "Created 5 plant products\n";
    
    // 4. Add initial stock
    printSeparator("Step 3: Add Initial Stock to Inventory");
    std::cout << "Adding stock via Command Pattern...\n";
    std::cout << "(Watch staff get notified!)\n\n";

    inventory->addStock(redRose, 50);
    inventory->addStock(yellowRose, 30);
    inventory->addStock(alienPlant, 20);
    inventory->addStock(oak, 15);
    inventory->addStock(maple, 100);

    std::cout << "\nAll stock added successfully\n";
    
    // 5. Display current sales floor
    printSeparator("Step 4: View Sales Floor Inventory");
    salesFloor->displayAvailablePlants();
    
    // 6. Test individual plant queries
    printSeparator("Step 5: Query Individual Plants");
    std::cout << "Checking Red Rose availability...\n";
    if (salesFloor->isPlantAvailable(redRose)) {
        std::cout << "Red Roses are available!\n";
        std::cout << "  Quantity on sales floor: " << salesFloor->getPlantQuantity(redRose) << "\n";
    }
    
    std::cout << "\nChecking Oak availability...\n";
    if (salesFloor->isPlantAvailable(oak)) {
        std::cout << "Oaks are available!\n";
        std::cout << "  Quantity on sales floor: " << salesFloor->getPlantQuantity(oak) << "\n";
    }
    
    // 7. Simulate customer purchases (removing stock)
    printSeparator("Step 6: Simulate Customer Purchases");
    std::cout << "Customer buys 10 red roses...\n";
    inventory->removeStock(redRose, 10);
    std::cout << "Removed 10 red roses from inventory\n";
    
    std::cout << "\nCustomer buys 5 oaks...\n";
    inventory->removeStock(oak, 5);
    std::cout << "Removed 5 oaks from inventory\n";
    
    std::cout << "\nCustomer buys 50 maple trees...\n";
    inventory->removeStock(maple, 50);
    std::cout << "Removed 50 maple trees from inventory\n";
    
    // 8. Display updated sales floor
    printSeparator("Step 7: View Updated Sales Floor");
    salesFloor->displayAvailablePlants();
    
    // 8.5 Test staff detachment
    printSeparator("Step 7.5: Remove Sarah from Notifications");
    std::cout << "Detaching Sarah from notifications...\n";
    salesFloor->detachStaff(sarah);
    std::cout << "Sarah removed. Only John and Mike will be notified now.\n\n";
    
    std::cout << "Testing with one more stock removal...\n";
    inventory->removeStock(redRose, 5);
    std::cout << "Notice: Only John and Mike get notified (not Sarah)\n";
    
    // 9. Test selling out a product
    printSeparator("Step 8: Test Selling Out Alien Plants");
    std::cout << "Selling all " << salesFloor->getPlantQuantity(alienPlant) << " alien plants...\n";
    inventory->removeStock(alienPlant, 20);
    std::cout << "All alien plants sold!\n\n";
    
    std::cout << "Checking if Alien Plants are still available...\n";
    if (!salesFloor->isPlantAvailable(alienPlant)) {
        std::cout << "Alien Plants correctly show as unavailable (quantity = 0)\n";
    }
    
    // 10. Display final state
    printSeparator("Step 9: Final Sales Floor State");
    salesFloor->displayAvailablePlants();
    
    // 11. Test restocking
    printSeparator("Step 10: Restock Sold-Out Items");
    std::cout << "Restocking 25 alien plants...\n";
    // Note: alienPlant was deleted when stock reached 0, so we need to create a new one
    alienPlant = new Plant(999.99, "Mysterious Alien Plant");
    inventory->addStock(alienPlant, 25);
    std::cout << "Alien Plants restocked\n\n";

    std::cout << "Restocking 30 red roses...\n";
    inventory->addStock(redRose, 30);
    std::cout << "Red Roses restocked\n";

    // 12. Final display
    printSeparator("Step 11: Final Inventory After Restock");
    salesFloor->displayAvailablePlants();
    
    // 13. Test getAvailableItems()
    printSeparator("Step 12: Test Direct Access Method");
    const auto& items = salesFloor->getAvailableItems();
    std::cout << "Using getAvailableItems() for external processing:\n";
    std::cout << "Total plant types available: " << items.size() << "\n";
    std::cout << "List of available plants:\n";
    for (const auto& item : items) {
        std::cout << "  - " << item.first->getDescription() 
                  << " (Qty: " << item.second << ")\n";
    }
    
    // 14. Test observer auto-detachment
    printSeparator("Step 13: Test Observer Cleanup");
    std::cout << "Deleting SalesFloorObserver...\n";
    delete salesFloor;
    std::cout << "Observer automatically detached from inventory\n";
    
    // 15. Clean up staff
    printSeparator("Step 14: Clean Up Staff Objects");
    delete john;
    delete sarah;
    delete mike;
    std::cout << "All staff objects deleted\n";

    delete redRose;
    delete yellowRose;
    delete alienPlant;
    delete oak;
    delete maple;
    
    return 0;
}