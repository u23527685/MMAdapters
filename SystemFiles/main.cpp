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
#include <iomanip>

#include "FullSunStrategy.h"
#include "HighWaterStrategy.h"
#include "InorganicFertilizer.h"
#include "LowWaterStrategy.h"
#include "OrganicFertilizer.h"
#include "ShadeStrategy.h"

#include "AskQuery.h"
#include "Staff.h"
#include"FloorEmployee.h"
#include"FloorManager.h"
#include"SalesEmployee.h"
#include"SalesManager.h"

#include <vector>
#include "Transaction.h"
#include "TransactionHistory.h"
#include "CreditCardPaymentStrategy.h"
#include "EWalletPaymentStrategy.h"
#include "EFTPaymentStrategy.h"
#include "BasePlant.h"
#include "GiftWrap.h"
#include "DecorativePot.h"
#include "SpecialArrangement.h"
#include "Customer.h"
#include "Order.h"
#include "Staff.h"

#include "Plant.h"
#include "PlantLifeCycle.h"
#include "SeedState.h"
#include "PlantCareRoutine.h"


/*
void testChainofResp(){
    #pragma region 
    std::cout << "\n========== Chain Of Responsibility and Builder test ==========\n";
    std::cout << "Testing Staff and builder and ask query\n";
    std::cout << "======================================================\n\n";

    FloorEmployee FE("Jeffery Dahmer");
    FloorManager FM("Ted Bundy");
    SalesEmployee SE("Jack The Ripper");
    SalesManager SM("Hanibal Lecter");
    PlantInventory* inventory1 = PlantInventory::getInstance();

     // ==========================================
    // Step 2: Create Plant Products
    // ==========================================
    std::cout << "========== Step 2: Create Plant Products ==========\n";
    Rose* redRose1 = new Rose(25.99, "Beautiful Red Rose");
    Rose* yellowRose1 = new Rose(22.99, "Bright Yellow Rose");
    Plant* alienPlant1 = new Plant(999.99, "Mysterious Alien Plant");
    Oak* oak1 = new Oak(12.50, "Majestic Oak Tree");
    Oak* maple1 = new Oak(14.75, "Vibrant Maple Tree");

    // Set categories (critical for care routine!)
    redRose1->setCategory("Sunny");
    yellowRose1->setCategory("Sunny");
    alienPlant1->setCategory("Tropical");
    oak1->setCategory("Temperate");
    maple1->setCategory("Temperate");

    std::cout << "Created 5 plant products with categories\n\n";

    // ==========================================
    // Step 3: Add Initial Stock to Inventory
    // ==========================================
    std::cout << "========== Step 3: Add Initial Stock to Inventory ==========\n";
    inventory1->addStock(redRose1, 50);
    inventory1->addStock(yellowRose1, 30);
    inventory1->addStock(alienPlant1, 20);
    inventory1->addStock(oak1, 15);
    inventory1->addStock(maple1, 100);
    std::cout << "All stock added successfully\n\n";

    AskQuery a;

    FE.setNext(&FM);
    FM.setNext(&SE);
    SE.setNext(&SM);

    Plant* asky = new Rose(22,"A beautiful red rose");
    asky->setCategory("Sunny");

    Query* q=a.careRoutine(asky);

    FE.handleQuery(q);
    q=a.describe(asky);
    FE.handleQuery(q);
    q=a.stockInfo();
    FE.handleQuery(q);

    std::cout << "Test completed successfully!\n";

    delete asky;
    delete q;
    delete redRose1;
    delete yellowRose1;
    delete alienPlant1;
    delete oak1;
    delete maple1;
    //delete inventory1;

    #pragma endregion
}


int main() {
    testChainofResp();
    /*
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

    //Test PlantCareRoutine print method
    PlantCareRoutine* PCR;
    PCR = PCR->PlantCare(redRose);
    PCR->printCareRoutine();

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

    std::cout << "Test completed successfully!\n";

    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║         STRATEGY PATTERN TEST - PLANT CARE SYSTEM          ║\n";
    std::cout << "║    Testing Dynamic Strategy Selection for Plant Care       ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";

    // Create plants
    Rose* desertRose = new Rose(29.99, "Desert Rose (Drought Tolerant)");
    Rose* rainforestRose = new Rose(34.99, "Rainforest Rose (Water Loving)");

    // Set initial low water, sunlight, and nutrients for both
    desertRose->setCurrentWater(10);
    desertRose->setCurrentSunlight(20);
    desertRose->setCurrentNutrients(5);

    rainforestRose->setCurrentWater(10);
    rainforestRose->setCurrentSunlight(20);
    rainforestRose->setCurrentNutrients(5);

    // Create strategies
    LowWaterStrategy* lowWater = new LowWaterStrategy();
    HighWaterStrategy* highWater = new HighWaterStrategy();
    FullSunStrategy* fullSun = new FullSunStrategy();
    ShadeStrategy* shade = new ShadeStrategy();
    OrganicFertilizer* organic = new OrganicFertilizer();
    InorganicFertilizer* inorganic = new InorganicFertilizer();

    // Apply strategies
    std::cout << "\n Applying strategies to Desert Rose:\n";
    std::cout << std::string(60, '-') << "\n";
    lowWater->applyWater(desertRose);
    fullSun->applySunlight(desertRose);
    organic->applyFertilizer(desertRose);

    // Print plant status
    std::cout << "\n--- Desert Rose Status ---\n";
    std::cout << "Plant: " << desertRose->getName() << "\n";
    std::cout << "Water: " << desertRose->getCurrentWater() << "/" << desertRose->getMaxWater()
              << " ml (" << std::fixed << std::setprecision(1)
              << (desertRose->getCurrentWater() * 100.0 / desertRose->getMaxWater()) << "%)\n";
    std::cout << "Sunlight: " << desertRose->getCurrentSunlight() << "/" << desertRose->getMaxSunlight()
              << " hrs (" << (desertRose->getCurrentSunlight() * 100.0 / desertRose->getMaxSunlight()) << "%)\n";
    std::cout << "Nutrients: " << desertRose->getCurrentNutrients() << "/" << desertRose->getMaxNutrients()
              << " ppm (" << (desertRose->getCurrentNutrients() * 100.0 / desertRose->getMaxNutrients()) << "%)\n";
    std::cout << std::string(40, '-') << "\n";

    std::cout << "\n ================================================ \n";

    std::cout << "\n Applying strategies to Rainforest Rose:\n";
    std::cout << std::string(60, '-') << "\n";
    highWater->applyWater(rainforestRose);
    shade->applySunlight(rainforestRose);
    inorganic->applyFertilizer(rainforestRose);

    std::cout << "\n--- Rainforest Rose Status ---\n";
    std::cout << "Plant: " << rainforestRose->getName() << "\n";
    std::cout << "Water: " << rainforestRose->getCurrentWater() << "/" << rainforestRose->getMaxWater()
              << " ml (" << std::fixed << std::setprecision(1)
              << (rainforestRose->getCurrentWater() * 100.0 / rainforestRose->getMaxWater()) << "%)\n";
    std::cout << "Sunlight: " << rainforestRose->getCurrentSunlight() << "/" << rainforestRose->getMaxSunlight()
              << " hrs (" << (rainforestRose->getCurrentSunlight() * 100.0 / rainforestRose->getMaxSunlight()) << "%)\n";
    std::cout << "Nutrients: " << rainforestRose->getCurrentNutrients() << "/" << rainforestRose->getMaxNutrients()
              << " ppm (" << (rainforestRose->getCurrentNutrients() * 100.0 / rainforestRose->getMaxNutrients()) << "%)\n";
    std::cout << std::string(40, '-') << "\n";

    // Cleanup
    delete desertRose;
    delete rainforestRose;
    delete lowWater;
    delete highWater;
    delete fullSun;
    delete shade;
    delete organic;
    delete inorganic;

    std::cout << "All objects deleted successfully!\n";
    std::cout << "\n"
                 "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║ STRATEGY PATTERN TEST COMPLETE                             ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n\n";
    
    */
    /*
    std::cout << "=== Transaction System Test ===\n\n";

    Transaction tx("ORD-1001", 25.50, 2);
    tx.processPayment();

    std::cout << "\n--- Testing Credit Card Payment ---\n";
    CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
    tx.setPaymentStrategy(&creditCard);
    tx.processPayment();

    std::cout << "\n--- Testing E-Wallet Payment ---\n";
    EWalletPaymentStrategy ewallet("wallet123");
    tx.setPaymentStrategy(&ewallet);
    tx.processPayment();

    std::cout << "\n--- Testing EFT Payment ---\n";
    EFTPaymentStrategy eft("9876543210");
    tx.setPaymentStrategy(&eft);
    tx.processPayment();

    std::cout << "\n=== Testing Transaction Snapshots (Memento Pattern) ===\n";
    TransactionHistory history;
    history.addSnapshot(tx.createSnapshot());

    std::cout << "\nUpdating Transaction...\n";
    tx.setTransaction("ORD-1002", 40.75, 3);
    tx.processPayment();
    history.addSnapshot(tx.createSnapshot());

    std::cout << "\nUpdating Transaction again...\n";
    tx.setTransaction("ORD-1003", 15.99, 5);
    tx.processPayment();
    history.addSnapshot(tx.createSnapshot());

    std::cout << "\n--- Restoring Previous Snapshot ---\n";
    tx.restoreSnapshot(history.getSnapshot(1));
    tx.processPayment();

    std::cout << "\n--- Restoring Original Snapshot ---\n";
    tx.restoreSnapshot(history.getSnapshot(0));
    tx.processPayment();

    std::cout << "\nTransaction history count: " << history.getHistorySize() << std::endl;

    std::cout << "\n=== Plant Decorator Test ===\n\n";

    std::vector<Plant*> plants;
    plants.push_back(new GiftWrap(new BasePlant()));
    plants.push_back(new DecorativePot(new GiftWrap(new BasePlant())));
    plants.push_back(new SpecialArrangement(new DecorativePot(new GiftWrap(new BasePlant()))));

    for (const auto& plant : plants) {
        std::cout << plant->getDescription() << " | R" << plant->getPrice() << std::endl;
    }
    for (auto& plant : plants) {
        delete plant;
    }

 
    std::cout << "\n=== Customer and Order Test ===\n\n";

    Customer customer("Alice Green");

    Order order1(&customer, "ORD-CUST-2001");

    Transaction* t1 = new Transaction("ORD-CUST-2001", 100.00, 1);
    Transaction* t2 = new Transaction("ORD-CUST-2001", 250.00, 3);

    t1->setPaymentStrategy(&creditCard);
    t2->setPaymentStrategy(&ewallet);

    order1.addTransaction(t1);
    order1.addTransaction(t2);

    order1.processOrder();

    order1.displayOrderDetails();

 
    customer.placeOrder(order1);

    customer.viewOrders();

    Staff staff;
    customer.makeQuery(staff, "Can I add a gift wrap to my next order?");
  
  
  
  
  
  
  
  
  // Greenhouse testing code


    Plant* myPlant = new Plant("Lavender");
    myPlant->setCurrentWater(5);
    myPlant->setCurrentSunlight(5);
    myPlant->setCurrentNutrients(5);


    PlantState* initialState = new SeedState();
    PlantLifeCycle* lifecycle = new PlantLifeCycle(myPlant, initialState, "LavenderLife");


    //Staff* alice = new Staff("Alice");
    //lifecycle->attach(alice);


    std::cout << "\n--- Initial Evaluation ---\n";
    lifecycle->isHealthy(); // This will call SeedState::evaluate and possibly change state


    for (int day = 1; day <= 3; ++day) {
        std::cout << "\n--- Day " << day << " ---\n";
        lifecycle->notify(); // Triggers Staff::update
        lifecycle->isHealthy(); // Re-evaluate after care
    }

    delete lifecycle;
    delete myPlant;
  
    return 0;

}
    */

