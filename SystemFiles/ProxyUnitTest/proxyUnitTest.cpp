#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Customer.h"
#include "../InventoryProxy.h"
#include "../Oak.h"
#include "../Plant.h"
#include "../PlantInventory.h"
#include "../Rose.h"
#include "../SalesFloorObserver.h"
#include "../StateUnitTests/doctest.h"
#include <iostream>

/**
 * @file proxyUnitTest.cpp
 * @brief Unit tests for InventoryProxy class
 *
 * Tests the Proxy pattern implementation for controlled access to inventory,
 * including customer purchases, access control, and display functionality.
 */

Rose *createTestRose(double price = 25.0, std::string desc = "Test Rose")
{
    return new Rose(price, desc);
}

Oak *createTestOak(double price = 75.0, std::string desc = "Test Oak")
{
    return new Oak(price, desc);
}

void cleanupPlant(Plant *plant)
{
    PlantInventory *inventory = PlantInventory::getInstance();
    int currentQty = inventory->getQuantity(plant);
    if (currentQty > 0)
    {
        inventory->removeStock(plant, currentQty);
    }
}

TEST_CASE("InventoryProxy: Creation with SalesFloorObserver")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    CHECK(proxy != nullptr);

    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Creation with null observer")
{
    InventoryProxy *proxy = new InventoryProxy(nullptr);

    CHECK(proxy != nullptr);

    delete proxy;
}

TEST_CASE("InventoryProxy: buyPlant - Successful Purchase")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(30.0, "Purchase Rose");
    inventory->addStock(rose, 10);

    bool result = proxy->buyPlant(rose, 5);

    CHECK(result == true);
    CHECK(inventory->getQuantity(rose) == 5);

    cleanupPlant(rose);
    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Purchase All Stock")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(80.0, "All Stock Oak");
    inventory->addStock(oak, 7);

    bool result = proxy->buyPlant(oak, 7);

    CHECK(result == true);
    CHECK(inventory->getQuantity(oak) == 0);

    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Insufficient Stock")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(20.0, "Insufficient Rose");
    inventory->addStock(rose, 3);

    bool result = proxy->buyPlant(rose, 5);

    CHECK(result == false);
    CHECK(inventory->getQuantity(rose) == 3);

    cleanupPlant(rose);
    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Out of Stock")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(50.0, "Out of Stock Oak");
    inventory->addStock(oak, 2);
    inventory->removeStock(oak, 2);

    bool result = proxy->buyPlant(oak, 1);

    CHECK(result == false);
    CHECK(inventory->getQuantity(oak) == 0);

    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Buy Single Item")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(15.0, "Single Rose");
    inventory->addStock(rose, 10);

    bool result = proxy->buyPlant(rose, 1);

    CHECK(result == true);
    CHECK(inventory->getQuantity(rose) == 9);

    cleanupPlant(rose);
    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Multiple Sequential Purchases")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(100.0, "Sequential Oak");
    inventory->addStock(oak, 20);

    bool result1 = proxy->buyPlant(oak, 5);
    CHECK(result1 == true);
    CHECK(inventory->getQuantity(oak) == 15);

    bool result2 = proxy->buyPlant(oak, 7);
    CHECK(result2 == true);
    CHECK(inventory->getQuantity(oak) == 8);

    bool result3 = proxy->buyPlant(oak, 3);
    CHECK(result3 == true);
    CHECK(inventory->getQuantity(oak) == 5);

    cleanupPlant(oak);
    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Zero Quantity")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(25.0, "Zero Qty Rose");
    inventory->addStock(rose, 5);

    bool result = proxy->buyPlant(rose, 0);

    CHECK(result == false);
    CHECK(inventory->getQuantity(rose) == 5);

    cleanupPlant(rose);
    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Negative Quantity")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(60.0, "Negative Qty Oak");
    inventory->addStock(oak, 10);

    bool result = proxy->buyPlant(oak, -5);

    CHECK(result == false);
    CHECK(inventory->getQuantity(oak) == 10);

    cleanupPlant(oak);
    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: buyPlant - Null Plant")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    bool result = proxy->buyPlant(nullptr, 5);

    CHECK(result == false);

    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: addStock - Access Denied for Customers")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(20.0, "Add Stock Rose");
    int initialQty = inventory->getQuantity(rose);

    proxy->addStock(rose, 10);

    int finalQty = inventory->getQuantity(rose);
    CHECK(finalQty == initialQty);

    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: removeStock - Access Denied for Customers")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(75.0, "Remove Stock Oak");
    inventory->addStock(oak, 15);

    proxy->removeStock(oak, 5);

    CHECK(inventory->getQuantity(oak) == 15);

    cleanupPlant(oak);
    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: displayAvailablePlants - With Observer")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(22.0, "Display Rose");
    Oak *oak = createTestOak(88.0, "Display Oak");

    inventory->addStock(rose, 5);
    inventory->addStock(oak, 3);

    proxy->displayAvailablePlants();
    CHECK(true);

    cleanupPlant(rose);
    cleanupPlant(oak);
    delete rose;
    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: displayAvailablePlants - Without Observer")
{
    InventoryProxy *proxy = new InventoryProxy(nullptr);

    proxy->displayAvailablePlants();
    CHECK(true);

    delete proxy;
}

TEST_CASE("InventoryProxy: displayAvailablePlants - Empty Inventory")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    proxy->displayAvailablePlants();
    CHECK(true);

    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Access Control - Only buyPlant Works")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(30.0, "Access Control Rose");
    inventory->addStock(rose, 10);

    bool buyResult = proxy->buyPlant(rose, 3);
    CHECK(buyResult == true);
    CHECK(inventory->getQuantity(rose) == 7);

    int qtyBeforeAdd = inventory->getQuantity(rose);
    proxy->addStock(rose, 10);
    CHECK(inventory->getQuantity(rose) == qtyBeforeAdd);

    int qtyBeforeRemove = inventory->getQuantity(rose);
    proxy->removeStock(rose, 5);
    CHECK(inventory->getQuantity(rose) == qtyBeforeRemove);

    cleanupPlant(rose);
    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Large Quantity Purchase")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(150.0, "Large Qty Oak");
    inventory->addStock(oak, 1000);

    bool result = proxy->buyPlant(oak, 500);

    CHECK(result == true);
    CHECK(inventory->getQuantity(oak) == 500);

    cleanupPlant(oak);
    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Buy Until Depletion")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(18.0, "Depletion Rose");
    inventory->addStock(rose, 10);

    CHECK(proxy->buyPlant(rose, 3) == true);
    CHECK(inventory->getQuantity(rose) == 7);

    CHECK(proxy->buyPlant(rose, 4) == true);
    CHECK(inventory->getQuantity(rose) == 3);

    CHECK(proxy->buyPlant(rose, 3) == true);
    CHECK(inventory->getQuantity(rose) == 0);

    CHECK(proxy->buyPlant(rose, 1) == false);
    CHECK(inventory->getQuantity(rose) == 0);

    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Different Plant Types Simultaneously")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(20.0, "Multi Type Rose");
    Oak *oak = createTestOak(70.0, "Multi Type Oak");

    inventory->addStock(rose, 15);
    inventory->addStock(oak, 10);

    CHECK(proxy->buyPlant(rose, 5) == true);
    CHECK(inventory->getQuantity(rose) == 10);
    CHECK(inventory->getQuantity(oak) == 10);

    CHECK(proxy->buyPlant(oak, 3) == true);
    CHECK(inventory->getQuantity(rose) == 10);
    CHECK(inventory->getQuantity(oak) == 7);

    CHECK(proxy->buyPlant(rose, 7) == true);
    CHECK(inventory->getQuantity(rose) == 3);
    CHECK(inventory->getQuantity(oak) == 7);

    cleanupPlant(rose);
    cleanupPlant(oak);
    delete rose;
    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Observer Updates After Purchase")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(25.0, "Observer Update Rose");
    inventory->addStock(rose, 20);

    CHECK(observer->getPlantQuantity(rose) == 20);
    CHECK(observer->isPlantAvailable(rose) == true);

    proxy->buyPlant(rose, 8);

    CHECK(observer->getPlantQuantity(rose) == 12);
    CHECK(observer->isPlantAvailable(rose) == true);

    proxy->buyPlant(rose, 12);

    CHECK(observer->getPlantQuantity(rose) == 0);
    CHECK(observer->isPlantAvailable(rose) == false);

    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Exact Stock Match Purchase")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(90.0, "Exact Match Oak");
    inventory->addStock(oak, 15);

    bool result = proxy->buyPlant(oak, 15);

    CHECK(result == true);
    CHECK(inventory->getQuantity(oak) == 0);

    delete oak;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: One Over Stock Purchase")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Rose *rose = createTestRose(12.0, "One Over Rose");
    inventory->addStock(rose, 10);

    bool result = proxy->buyPlant(rose, 11);

    CHECK(result == false);
    CHECK(inventory->getQuantity(rose) == 10);

    cleanupPlant(rose);
    delete rose;
    delete proxy;
    delete observer;
}

TEST_CASE("InventoryProxy: Proxy Pattern - Controlled Access Verification")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);
    InventoryProxy *proxy = new InventoryProxy(observer);

    Oak *oak = createTestOak(65.0, "Control Access Oak");

    inventory->addStock(oak, 50);
    CHECK(inventory->getQuantity(oak) == 50);

    CHECK(proxy->buyPlant(oak, 10) == true);
    CHECK(inventory->getQuantity(oak) == 40);

    proxy->addStock(oak, 100);
    CHECK(inventory->getQuantity(oak) == 40);

    proxy->removeStock(oak, 20);
    CHECK(inventory->getQuantity(oak) == 40);

    inventory->addStock(oak, 10);
    CHECK(inventory->getQuantity(oak) == 50);

    cleanupPlant(oak);
    delete oak;
    delete proxy;
    delete observer;
}
