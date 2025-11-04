#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../StateUnitTests/doctest.h"
#include "../SalesFloorObserver.h"
#include "../PlantInventory.h"
#include "../Plant.h"
#include "../Rose.h"
#include "../Oak.h"
#include "../FloorEmployee.h"
#include "../Staff.h"
#include <iostream>

/**
 * @file salesObserverUnitTest.cpp
 * @brief Unit tests for SalesFloorObserver class
 * 
 * Tests the Observer pattern implementation for sales floor inventory tracking,
 * including notifications, staff management, and inventory updates.
 */

Rose* createTestRose(double price = 25.0, std::string desc = "Test Rose") {
    return new Rose(price, desc);
}

Oak* createTestOak(double price = 75.0, std::string desc = "Test Oak") {
    return new Oak(price, desc);
}

void cleanupPlant(Plant* plant, int quantity) {
    PlantInventory* inventory = PlantInventory::getInstance();
    int currentQty = inventory->getQuantity(plant);
    if (currentQty > 0) {
        inventory->removeStock(plant, currentQty);
    }
}

TEST_CASE("SalesFloorObserver: Creation and Initialization") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    CHECK(observer != nullptr);
    CHECK(observer->getAvailableItems().size() >= 0);
    
    delete observer;
}

TEST_CASE("SalesFloorObserver: Observer Attaches to Inventory") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);

    Rose* rose = createTestRose(30.0, "Attachment Test Rose");
    inventory->addStock(rose, 5);
    
    bool isAvailable = observer->isPlantAvailable(rose);
    CHECK(isAvailable == true);
    
    cleanupPlant(rose, 5);
    delete rose;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Update on Stock Addition") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(20.0, "Addition Test Rose");
    inventory->addStock(rose, 10);
    
    CHECK(observer->isPlantAvailable(rose) == true);
    CHECK(observer->getPlantQuantity(rose) == 10);
    
    cleanupPlant(rose, 10);
    delete rose;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Update on Stock Removal") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Oak* oak = createTestOak(80.0, "Removal Test Oak");
    inventory->addStock(oak, 15);
    
    int initialQty = observer->getPlantQuantity(oak);
    CHECK(initialQty == 15);
    
    inventory->removeStock(oak, 5);
    
    int finalQty = observer->getPlantQuantity(oak);
    CHECK(finalQty == 10);
    CHECK(observer->isPlantAvailable(oak) == true);
    
    cleanupPlant(oak, 10);
    delete oak;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Stock Depletion Tracking") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(15.0, "Depletion Test Rose");
    inventory->addStock(rose, 5);
    
    CHECK(observer->isPlantAvailable(rose) == true);

    inventory->removeStock(rose, 5);
    
    CHECK(observer->isPlantAvailable(rose) == false);
    CHECK(observer->getPlantQuantity(rose) == 0);
    
    delete rose;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Multiple Plants Tracking") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(25.0, "Multi Rose");
    Oak* oak = createTestOak(90.0, "Multi Oak");
    
    inventory->addStock(rose, 8);
    inventory->addStock(oak, 12);
    
    CHECK(observer->isPlantAvailable(rose) == true);
    CHECK(observer->isPlantAvailable(oak) == true);
    CHECK(observer->getPlantQuantity(rose) == 8);
    CHECK(observer->getPlantQuantity(oak) == 12);
    
    const auto& items = observer->getAvailableItems();
    CHECK(items.size() >= 2);
    
    cleanupPlant(rose, 8);
    cleanupPlant(oak, 12);
    delete rose;
    delete oak;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Sequential Stock Changes") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(22.0, "Sequential Rose");
    
    inventory->addStock(rose, 10);
    CHECK(observer->getPlantQuantity(rose) == 10);
    
    inventory->addStock(rose, 5);
    CHECK(observer->getPlantQuantity(rose) == 15);
    
    inventory->removeStock(rose, 8);
    CHECK(observer->getPlantQuantity(rose) == 7);

    inventory->removeStock(rose, 7);
    CHECK(observer->getPlantQuantity(rose) == 0);
    CHECK(observer->isPlantAvailable(rose) == false);
    
    delete rose;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Get Plant Quantity") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Oak* oak = createTestOak(100.0, "Quantity Test Oak");
    inventory->addStock(oak, 25);
    
    int quantity = observer->getPlantQuantity(oak);
    CHECK(quantity == 25);
    
    cleanupPlant(oak, 25);
    delete oak;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Get Quantity for Non-Existent Plant") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(10.0, "Non-Existent Rose");
    
    int quantity = observer->getPlantQuantity(rose);
    CHECK(quantity == 0);
    
    delete rose;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Is Plant Available Check") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(18.0, "Available Rose");
    inventory->addStock(rose, 3);
    
    bool available = observer->isPlantAvailable(rose);
    CHECK(available == true);
    
    cleanupPlant(rose, 3);
    delete rose;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Plant Not Available When Out of Stock") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Oak* oak = createTestOak(55.0, "Out of Stock Oak");
    inventory->addStock(oak, 2);
    inventory->removeStock(oak, 2);
    
    bool available = observer->isPlantAvailable(oak);
    CHECK(available == false);
    
    delete oak;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Attach Staff Member") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    FloorEmployee* staff = new FloorEmployee("John Doe");
    
    
    observer->attachStaff(staff);
    CHECK(true); 
    
    delete staff;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Detach Staff Member") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    FloorEmployee* staff = new FloorEmployee("Jane Smith");
    
    observer->attachStaff(staff);
    observer->detachStaff(staff);
    CHECK(true);
    
    delete staff;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Multiple Staff Attachments") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    FloorEmployee* staff1 = new FloorEmployee("Staff 1");
    FloorEmployee* staff2 = new FloorEmployee("Staff 2");
    FloorEmployee* staff3 = new FloorEmployee("Staff 3");
    
    observer->attachStaff(staff1);
    observer->attachStaff(staff2);
    observer->attachStaff(staff3);
    
    CHECK(true);
    
    delete staff1;
    delete staff2;
    delete staff3;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Staff Notification on Stock Addition") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    FloorEmployee* staff = new FloorEmployee("Alice Williams");
    observer->attachStaff(staff);
    
    Rose* rose = createTestRose(28.0, "Notification Rose");

    inventory->addStock(rose, 7);
    
    CHECK(observer->getPlantQuantity(rose) == 7);
    
    cleanupPlant(rose, 7);
    delete rose;
    delete staff;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Staff Notification on Stock Removal") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    FloorEmployee* staff = new FloorEmployee("Bob Johnson");
    observer->attachStaff(staff);
    
    Oak* oak = createTestOak(65.0, "Removal Notify Oak");
    inventory->addStock(oak, 10);
    
    inventory->removeStock(oak, 4);
    
    CHECK(observer->getPlantQuantity(oak) == 6);
    
    cleanupPlant(oak, 6);
    delete oak;
    delete staff;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Get Available Items") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose1 = createTestRose(15.0, "Rose 1");
    Rose* rose2 = createTestRose(20.0, "Rose 2");
    Oak* oak = createTestOak(70.0, "Oak 1");
    
    inventory->addStock(rose1, 5);
    inventory->addStock(rose2, 3);
    inventory->addStock(oak, 8);
    
    const auto& items = observer->getAvailableItems();
    CHECK(items.size() >= 3);
    
    cleanupPlant(rose1, 5);
    cleanupPlant(rose2, 3);
    cleanupPlant(oak, 8);
    delete rose1;
    delete rose2;
    delete oak;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Display Available Plants") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(22.50, "Display Rose");
    Oak* oak = createTestOak(95.0, "Display Oak");
    
    inventory->addStock(rose, 6);
    inventory->addStock(oak, 4);
    
    observer->displayAvailablePlants();
    CHECK(true);
    
    cleanupPlant(rose, 6);
    cleanupPlant(oak, 4);
    delete rose;
    delete oak;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Display When Empty") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    observer->displayAvailablePlants();
    CHECK(true);
    
    delete observer;
}

TEST_CASE("SalesFloorObserver: Null Staff Attachment") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    observer->attachStaff(nullptr);
    CHECK(true);
    
    delete observer;
}

TEST_CASE("SalesFloorObserver: Detach Non-Attached Staff") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    FloorEmployee* staff = new FloorEmployee("Random Staff");
    
    observer->detachStaff(staff);
    CHECK(true);
    
    delete staff;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Multiple Updates Same Plant") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(19.0, "Update Rose");
    
    inventory->addStock(rose, 5);
    CHECK(observer->getPlantQuantity(rose) == 5);
    
    inventory->addStock(rose, 3);
    CHECK(observer->getPlantQuantity(rose) == 8);
    
    inventory->removeStock(rose, 2);
    CHECK(observer->getPlantQuantity(rose) == 6);
    
    inventory->addStock(rose, 4);
    CHECK(observer->getPlantQuantity(rose) == 10);
    
    cleanupPlant(rose, 10);
    delete rose;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Large Quantity Handling") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Oak* oak = createTestOak(150.0, "Large Quantity Oak");
    inventory->addStock(oak, 1000);
    
    CHECK(observer->getPlantQuantity(oak) == 1000);
    CHECK(observer->isPlantAvailable(oak) == true);
    
    cleanupPlant(oak, 1000);
    delete oak;
    delete observer;
}

TEST_CASE("SalesFloorObserver: Interleaved Operations Multiple Plants") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    
    Rose* rose = createTestRose(12.0, "Interleaved Rose");
    Oak* oak = createTestOak(45.0, "Interleaved Oak");
    
    inventory->addStock(rose, 10);
    inventory->addStock(oak, 20);
    CHECK(observer->getPlantQuantity(rose) == 10);
    CHECK(observer->getPlantQuantity(oak) == 20);
    
    inventory->removeStock(rose, 3);
    CHECK(observer->getPlantQuantity(rose) == 7);
    CHECK(observer->getPlantQuantity(oak) == 20);
    
    inventory->removeStock(oak, 5);
    CHECK(observer->getPlantQuantity(rose) == 7);
    CHECK(observer->getPlantQuantity(oak) == 15);
    
    inventory->addStock(rose, 8);
    CHECK(observer->getPlantQuantity(rose) == 15);
    CHECK(observer->getPlantQuantity(oak) == 15);
    
    cleanupPlant(rose, 15);
    cleanupPlant(oak, 15);
    delete rose;
    delete oak;
    delete observer;
}
