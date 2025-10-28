#include "PlantInventory.h"
#include "InventoryObserver.h"
#include "SalesFloorObserver.h"
#include "Plant.h"
#include "Rose.h"
#include "Oak.h"
#include "FloorEmployee.h"
#include "PlantLifeCycle.h"
#include "SeedState.h"
#include "DistressedState.h"
#include "WitheredState.h"
#include "PlantCareRoutine.h"

#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "\n========== INVENTORY + PLANT CARE SYSTEM TEST ==========\n";
    std::cout << "Testing PlantInventory with SalesFloorObserver + Staff Care\n";
    std::cout << "======================================================\n\n";

    // ==========================================
    // Step 1: Initialize Inventory System
    // ==========================================
    std::cout << "========== Step 1: Initialize Inventory System ==========\n";
    PlantInventory* inventory = PlantInventory::getInstance();
    std::cout << "PlantInventory singleton created\n";

    SalesFloorObserver* salesFloor = new SalesFloorObserver(inventory);
    std::cout << "SalesFloorObserver attached to inventory\n\n";

    // ==========================================
    // Step 1.5: Attach Staff to Sales Floor Observer
    // ==========================================
    std::cout << "========== Step 1.5: Attach Staff to Sales Floor Observer ==========\n";
    FloorEmployee* john = new FloorEmployee("John");
    FloorEmployee* sarah = new FloorEmployee("Sarah");
    FloorEmployee* mike = new FloorEmployee("Mike");

    salesFloor->attachStaff(john);
    salesFloor->attachStaff(sarah);
    salesFloor->attachStaff(mike);

    std::cout << "3 staff members attached and ready for notifications\n\n";

    // ==========================================
    // Step 2: Create Plant Products
    // ==========================================
    std::cout << "========== Step 2: Create Plant Products ==========\n";
    Rose* redRose = new Rose(25.99, "Beautiful Red Rose");
    Rose* yellowRose = new Rose(22.99, "Bright Yellow Rose");
    Plant* alienPlant = new Plant(999.99, "Mysterious Alien Plant");
    Oak* oak = new Oak(12.50, "Majestic Oak Tree");
    Oak* maple = new Oak(14.75, "Vibrant Maple Tree");

    // Set categories (critical for care routine!)
    redRose->setCategory("Sunny");
    yellowRose->setCategory("Sunny");
    alienPlant->setCategory("Tropical");
    oak->setCategory("Temperate");
    maple->setCategory("Temperate");

    std::cout << "Created 5 plant products with categories\n\n";

    // ==========================================
    // Step 3: Add Initial Stock to Inventory
    // ==========================================
    std::cout << "========== Step 3: Add Initial Stock to Inventory ==========\n";
    inventory->addStock(redRose, 50);
    inventory->addStock(yellowRose, 30);
    inventory->addStock(alienPlant, 20);
    inventory->addStock(oak, 15);
    inventory->addStock(maple, 100);
    std::cout << "All stock added successfully\n\n";

    // ==========================================
    // Step 4: View Sales Floor Inventory
    // ==========================================
    std::cout << "========== Step 4: View Sales Floor Inventory ==========\n";
    salesFloor->displayAvailablePlants();
    std::cout << "\n";

    // ==========================================
    // Step 5: Query Individual Plants
    // ==========================================
    std::cout << "========== Step 5: Query Individual Plants ==========\n";
    std::cout << "Checking Red Rose availability...\n";
    if (salesFloor->isPlantAvailable(redRose)) {
        std::cout << "Red Roses are available! Qty: " << salesFloor->getPlantQuantity(redRose) << "\n";
    }
    std::cout << "\n";

    // ==========================================
    // Step 6: Simulate Customer Purchases
    // ==========================================
    std::cout << "========== Step 6: Simulate Customer Purchases ==========\n";
    inventory->removeStock(redRose, 10);
    inventory->removeStock(oak, 5);
    inventory->removeStock(maple, 50);
    std::cout << "Purchases completed\n\n";

    // ==========================================
    // Step 7: View Updated Sales Floor
    // ==========================================
    std::cout << "========== Step 7: View Updated Sales Floor ==========\n";
    salesFloor->displayAvailablePlants();
    std::cout << "\n";

    // ==========================================
    // Step 7.5: Detach Staff
    // ==========================================
    std::cout << "========== Step 7.5: Remove Sarah from Notifications ==========\n";
    salesFloor->detachStaff(sarah);
    std::cout << "Sarah removed. Only John and Mike will be notified now.\n\n";

    // ==========================================
    // Step 8: PLANT CARE & LIFECYCLE TEST
    // ==========================================
    std::cout << "========== Step 8: PLANT CARE & LIFECYCLE TEST ==========\n";
    std::cout << "Creating lifecycle for one Red Rose and one Oak...\n";

    // Create lifecycle for one specific plant instance
    PlantLifeCycle* roseCycle = new PlantLifeCycle(redRose, new SeedState(), "Red Rose #001");
    PlantLifeCycle* oakCycle  = new PlantLifeCycle(oak,     new WitheredState(), "Oak #001");

    // Attach staff to lifecycle
    roseCycle->attach(john);
    roseCycle->attach(mike);
    oakCycle->attach(john);

    std::cout << "Staff attached to plant lifecycle. Simulating neglect...\n\n";

    // Simulate neglect
    redRose->setCurrentWater(5);
    redRose->setCurrentSunlight(3);
    redRose->setCurrentNutrients(8);

    oak->setCurrentWater(15);
    oak->setCurrentSunlight(25);
    oak->setCurrentNutrients(35);

    // ============ BEFORE CARE ============
    std::cout << "============ BEFORE CARE ============\n";
    std::cout << "Red Rose #001:\n";
    std::cout << "  Water: " << redRose->getCurrentWater() << "\n";
    std::cout << "  Sunlight: " << redRose->getCurrentSunlight() << "\n";
    std::cout << "  Nutrients: " << redRose->getCurrentNutrients() << "\n";
    std::cout << "  State: " << roseCycle->getState() << "\n\n";

    std::cout << "Oak #001:\n";
    std::cout << "  Water: " << oak->getCurrentWater() << "\n";
    std::cout << "  Sunlight: " << oak->getCurrentSunlight() << "\n";
    std::cout << "  Nutrients: " << oak->getCurrentNutrients() << "\n";
    std::cout << "  State: " << oakCycle->getState() << "\n";
    std::cout << "=====================================\n\n";

    // ============ TRIGGER CARE ============
    std::cout << "Triggering care routine via isHealthy()...\n\n";
    roseCycle->isHealthy();  // Triggers state change + care
    oakCycle->isHealthy();   // Triggers care

    // ============ AFTER CARE ============
    std::cout << "============ AFTER CARE =============\n";
    std::cout << "Red Rose #001:\n";
    std::cout << "  Water: " << redRose->getCurrentWater() << "\n";
    std::cout << "  Sunlight: " << redRose->getCurrentSunlight() << "\n";
    std::cout << "  Nutrients: " << redRose->getCurrentNutrients() << "\n";
    std::cout << "  State: " << roseCycle->getState() << "\n\n";

    std::cout << "Oak #001:\n";
    std::cout << "  Water: " << oak->getCurrentWater() << "\n";
    std::cout << "  Sunlight: " << oak->getCurrentSunlight() << "\n";
    std::cout << "  Nutrients: " << oak->getCurrentNutrients() << "\n";
    std::cout << "  State: " << oakCycle->getState() << "\n";
    std::cout << "=====================================\n\n";

    // ==========================================
    // Step 9: Sell Out Alien Plants
    // ==========================================
    std::cout << "========== Step 9: Test Selling Out Alien Plants ==========\n";
    int alienQty = salesFloor->getPlantQuantity(alienPlant);
    std::cout << "Selling all " << alienQty << " alien plants...\n";
    inventory->removeStock(alienPlant, alienQty);
    std::cout << "All alien plants sold!\n\n";

    if (!salesFloor->isPlantAvailable(alienPlant)) {
        std::cout << "Alien Plants correctly show as unavailable\n\n";
    }

    // ==========================================
    // Step 10: Final Sales Floor State
    // ==========================================
    std::cout << "========== Step 10: Final Sales Floor State ==========\n";
    salesFloor->displayAvailablePlants();
    std::cout << "\n";

    // ==========================================
    // Step 11: Restock Sold-Out Items
    // ==========================================
    std::cout << "========== Step 11: Restock Sold-Out Items ==========\n";
    Plant* newAlien = new Plant(999.99, "Mysterious Alien Plant");
    newAlien->setCategory("Tropical");
    inventory->addStock(newAlien, 25);
    inventory->addStock(redRose, 30);
    std::cout << "Restocked 25 Alien Plants and 30 Red Roses\n\n";

    // ==========================================
    // Step 12: Final Inventory After Restock
    // ==========================================
    std::cout << "========== Step 12: Final Inventory After Restock ==========\n";
    salesFloor->displayAvailablePlants();
    std::cout << "\n";

    // ==========================================
    // Step 13: Test Direct Access Method
    // ==========================================
    std::cout << "========== Step 13: Test Direct Access Method ==========\n";
    const auto& items = salesFloor->getAvailableItems();
    std::cout << "Total plant types available: " << items.size() << "\n";
    for (const auto& item : items) {
        std::cout << "  - " << item.first->getDescription()
                  << " (Qty: " << item.second << ")\n";
    }
    std::cout << "\n";

    // ==========================================
    // Cleanup
    // ==========================================
    std::cout << "========== Cleanup ==========\n";
    delete roseCycle;
    delete oakCycle;
    delete salesFloor;
    delete john;
    delete sarah;
    delete mike;
    delete redRose;
    delete yellowRose;
    delete alienPlant;
    delete newAlien;
    delete oak;
    delete maple;

    std::cout << "Test completed successfully!\n";
    return 0;
}