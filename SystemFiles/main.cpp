#include "PlantInventory.h"
#include "InventoryObserver.h"
#include "SalesFloorObserver.h"
#include "Plant.h"
#include "Rose.h"
#include "Oak.h"
#include "FloorEmployee.h"

#include <iostream>

int main() {
    std::cout << "\n========== INVENTORY OBSERVER SYSTEM TEST ==========\n";
    std::cout << "Testing PlantInventory with SalesFloorObserver\n";
    std::cout << "================================================\n";
    
    std::cout << "\n========== Step 1: Initialize Inventory System ==========\n";
    PlantInventory* inventory = PlantInventory::getInstance();
    std::cout << "PlantInventory singleton created\n";
    
    SalesFloorObserver* salesFloor = new SalesFloorObserver(inventory);
    std::cout << "SalesFloorObserver attached to inventory\n";
    
    std::cout << "\n========== Step 1.5: Attach Staff to Sales Floor Observer ==========\n";
    FloorEmployee* john = new FloorEmployee("John");
    FloorEmployee* sarah = new FloorEmployee("Sarah");
    FloorEmployee* mike = new FloorEmployee("Mike");
    
    salesFloor->attachStaff(john);
    salesFloor->attachStaff(sarah);
    salesFloor->attachStaff(mike);
    
    std::cout << "3 staff members attached and ready for notifications\n";
    
    std::cout << "\n========== Step 2: Create Plant Products ==========\n";
    Rose* redRose = new Rose(25.99, "Beautiful Red Rose");
    Rose* yellowRose = new Rose(22.99, "Bright Yellow Rose");
    Plant* alienPlant = new Plant(999.99, "Mysterious Alien Plant");
    Oak* oak = new Oak(12.50, "Majestic Oak Tree");
    Oak* maple = new Oak(14.75, "Vibrant Maple Tree");

    std::cout << "Created 5 plant products\n";
    
    std::cout << "\n========== Step 3: Add Initial Stock to Inventory ==========\n";
    std::cout << "Adding stock via Command Pattern...\n";

    inventory->addStock(redRose, 50);
    inventory->addStock(yellowRose, 30);
    inventory->addStock(alienPlant, 20);
    inventory->addStock(oak, 15);
    inventory->addStock(maple, 100);

    std::cout << "\nAll stock added successfully\n";
    
    std::cout << "\n========== Step 4: View Sales Floor Inventory ==========\n";
    salesFloor->displayAvailablePlants();
    
    std::cout << "\n========== Step 5: Query Individual Plants ==========\n";
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
    
    std::cout << "\n========== Step 6: Simulate Customer Purchases ==========\n";
    std::cout << "Customer buys 10 red roses\n";
    inventory->removeStock(redRose, 10);
    std::cout << "Removed 10 red roses from inventory\n";
    
    std::cout << "\nCustomer buys 5 oaks...\n";
    inventory->removeStock(oak, 5);
    std::cout << "Removed 5 oaks from inventory\n";
    
    std::cout << "\nCustomer buys 50 maple trees\n";
    inventory->removeStock(maple, 50);
    std::cout << "Removed 50 maple trees from inventory\n";
    
    std::cout << "\n========== Step 7: View Updated Sales Floor ==========\n";
    salesFloor->displayAvailablePlants();
    
    std::cout << "\n========== Step 7.5: Remove Sarah from Notifications ==========\n";
    std::cout << "Detaching Sarah from notifications\n";
    salesFloor->detachStaff(sarah);
    std::cout << "Sarah removed. Only John and Mike will be notified now.\n\n";
    
    std::cout << "Testing with one more stock removal\n";
    inventory->removeStock(redRose, 5);
    
    std::cout << "\n========== Step 8: Test Selling Out Alien Plants ==========\n";
    std::cout << "Selling all " << salesFloor->getPlantQuantity(alienPlant) << " alien plants...\n";
    inventory->removeStock(alienPlant, 20);
    std::cout << "All alien plants sold!\n\n";
    
    std::cout << "Checking if Alien Plants are still available\n";
    if (!salesFloor->isPlantAvailable(alienPlant)) {
        std::cout << "Alien Plants correctly show as unavailable\n";
    }
    
    std::cout << "\n========== Step 9: Final Sales Floor State ==========\n";
    salesFloor->displayAvailablePlants();
    
    std::cout << "\n========== Step 10: Restock Sold-Out Items ==========\n";
    std::cout << "Restocking 25 alien plants...\n";
    alienPlant = new Plant(999.99, "Mysterious Alien Plant");
    inventory->addStock(alienPlant, 25);
    std::cout << "Alien Plants restocked\n\n";

    std::cout << "Restocking 30 red roses...\n";
    inventory->addStock(redRose, 30);
    std::cout << "Red Roses restocked\n";

    std::cout << "\n========== Step 11: Final Inventory After Restock ==========\n";
    salesFloor->displayAvailablePlants();
    
    std::cout << "\n========== Step 12: Test Direct Access Method ==========\n";
    const auto& items = salesFloor->getAvailableItems();
    std::cout << "Using getAvailableItems() for external processing:\n";
    std::cout << "Total plant types available: " << items.size() << "\n";
    std::cout << "List of available plants:\n";
    for (const auto& item : items) {
        std::cout << "  - " << item.first->getDescription() << " (Qty: " << item.second << ")\n";
    }
    
    delete salesFloor;
    
    delete john;
    delete sarah;
    delete mike;

    delete redRose;
    delete yellowRose;
    delete alienPlant;
    delete oak;
    delete maple;
    
    return 0;
}