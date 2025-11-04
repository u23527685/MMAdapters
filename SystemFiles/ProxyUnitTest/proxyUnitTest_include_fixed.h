// This file includes proxyUnitTest without DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// So it can be included in TestingMain.cpp

#include "../InventoryProxy.h"
#include "../PlantInventory.h"
#include "../SalesFloorObserver.h"
#include "../Plant.h"
#include "../Rose.h"
#include "../Oak.h"
#include "../Customer.h"
#include <iostream>

/**
 * @file proxyUnitTest_include.h
 * @brief Unit tests for InventoryProxy class (include version)
 */

Rose* createTestRose(double price = 25.0, std::string desc = "Test Rose") {
    return new Rose(price, desc);
}

Oak* createTestOak(double price = 75.0, std::string desc = "Test Oak") {
    return new Oak(price, desc);
}

void cleanupPlant(Plant* plant) {
    PlantInventory* inventory = PlantInventory::getInstance();
    int currentQty = inventory->getQuantity(plant);
    if (currentQty > 0) {
        inventory->removeStock(plant, currentQty);
    }
}

TEST_CASE("InventoryProxy: Creation with SalesFloorObserver") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    CHECK(proxy != nullptr);
    
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: Creation with null observer") {
    InventoryProxy* proxy = new InventoryProxy(nullptr);
    
    CHECK(proxy != nullptr);
    
    delete proxy;
}

TEST_CASE("InventoryProxy: buyPlant - Successful Purchase") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Rose* rose = createTestRose(30.0, "Purchase Rose");
    inventory->addStock(rose, 10);
    
    bool result = proxy->buyPlant(rose, 5);
    
    CHECK(result == true);
    CHECK(inventory->getQuantity(rose) == 5);
    
    cleanupPlant(rose);
    delete rose;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Purchase All Stock") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Oak* oak = createTestOak(80.0, "All Stock Oak");
    inventory->addStock(oak, 7);
    
    bool result = proxy->buyPlant(oak, 7);
    
    CHECK(result == true);
    CHECK(inventory->getQuantity(oak) == 0);
    
    delete oak;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Insufficient Stock") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Rose* rose = createTestRose(20.0, "Insufficient Rose");
    inventory->addStock(rose, 3);
    
    bool result = proxy->buyPlant(rose, 5);
    
    CHECK(result == false);
    CHECK(inventory->getQuantity(rose) == 3);
    
    cleanupPlant(rose);
    delete rose;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Zero Quantity") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Oak* oak = createTestOak(60.0, "Zero Qty Oak");
    inventory->addStock(oak, 5);
    
    bool result = proxy->buyPlant(oak, 0);
    
    CHECK(result == false);
    CHECK(inventory->getQuantity(oak) == 5);
    
    cleanupPlant(oak);
    delete oak;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Negative Quantity") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Rose* rose = createTestRose(15.0, "Negative Qty Rose");
    inventory->addStock(rose, 10);
    
    bool result = proxy->buyPlant(rose, -2);
    
    CHECK(result == false);
    CHECK(inventory->getQuantity(rose) == 10);
    
    cleanupPlant(rose);
    delete rose;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Null Plant") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    bool result = proxy->buyPlant(nullptr, 1);
    
    CHECK(result == false);
    
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: displayInventory - With Observer") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Rose* rose = createTestRose(25.0, "Display Rose");
    inventory->addStock(rose, 4);
    
    // Should not crash
    proxy->displayAvailablePlants();
    
    cleanupPlant(rose);
    delete rose;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: displayAvailablePlants - Without Observer") {
    InventoryProxy* proxy = new InventoryProxy(nullptr);
    
    // Should not crash even without observer
    proxy->displayAvailablePlants();
    
    delete proxy;
}

TEST_CASE("InventoryProxy: addStock - Access Denied") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Rose* rose = createTestRose(30.0, "Add Stock Rose");
    
    // Proxy should deny addStock for customers
    proxy->addStock(rose, 5);
    
    // Verify stock was not added through proxy
    CHECK(inventory->getQuantity(rose) == 0);
    
    delete rose;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("InventoryProxy: removeStock - Access Denied") {
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* observer = new SalesFloorObserver(inventory);
    InventoryProxy* proxy = new InventoryProxy(observer);
    
    Oak* oak = createTestOak(70.0, "Remove Stock Oak");
    inventory->addStock(oak, 10);
    
    // Proxy should deny removeStock for customers
    proxy->removeStock(oak, 3);
    
    // Verify stock was not removed through proxy
    CHECK(inventory->getQuantity(oak) == 10);
    
    cleanupPlant(oak);
    delete oak;
    delete proxy;
    inventory->detach(observer);
    delete observer;
}
