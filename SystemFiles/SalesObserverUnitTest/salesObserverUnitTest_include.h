// This file includes salesObserverUnitTest without
// DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN So it can be included in TestingMain.cpp

#include "../FloorEmployee.h"
#include "../Oak.h"
#include "../Plant.h"
#include "../PlantInventory.h"
#include "../Rose.h"
#include "../SalesFloorObserver.h"
#include "../Staff.h"
#include <iostream>

/**
 * @file salesObserverUnitTest_include.h
 * @brief Unit tests for SalesFloorObserver class (include version)
 */

Rose *createSalesTestRose(double price = 25.0, std::string desc = "Test Rose")
{
    return new Rose(price, desc);
}

Oak *createSalesTestOak(double price = 75.0, std::string desc = "Test Oak")
{
    return new Oak(price, desc);
}

void cleanupSalesPlant(Plant *plant, int quantity)
{
    PlantInventory *inventory = PlantInventory::getInstance();
    int currentQty = inventory->getQuantity(plant);
    if (currentQty > 0)
    {
        inventory->removeStock(plant, currentQty);
    }
}

TEST_CASE("SalesFloorObserver: Creation and Initialization")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);

    CHECK(observer != nullptr);
    CHECK(observer->getAvailableItems().size() >= 0);

    inventory->detach(observer);
    delete observer;
}

TEST_CASE("SalesFloorObserver: Observer Attaches to Inventory")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);

    Rose *rose = createSalesTestRose(30.0, "Attachment Test Rose");
    inventory->addStock(rose, 5);

    bool isAvailable = observer->isPlantAvailable(rose);
    CHECK(isAvailable == true);

    cleanupSalesPlant(rose, 5);
    delete rose;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("SalesFloorObserver: Update on Stock Addition")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);

    Rose *rose = createSalesTestRose(20.0, "Addition Test Rose");
    inventory->addStock(rose, 10);

    CHECK(observer->isPlantAvailable(rose) == true);
    CHECK(observer->getPlantQuantity(rose) == 10);

    cleanupSalesPlant(rose, 10);
    delete rose;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("SalesFloorObserver: Update on Stock Removal")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);

    Oak *oak = createSalesTestOak(80.0, "Removal Test Oak");
    inventory->addStock(oak, 15);

    int initialQty = observer->getPlantQuantity(oak);
    CHECK(initialQty == 15);

    inventory->removeStock(oak, 5);

    int finalQty = observer->getPlantQuantity(oak);
    CHECK(finalQty == 10);
    CHECK(observer->isPlantAvailable(oak) == true);

    cleanupSalesPlant(oak, 10);
    delete oak;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("SalesFloorObserver: Stock Depletion Tracking")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);

    Rose *rose = createSalesTestRose(15.0, "Depletion Rose");
    inventory->addStock(rose, 8);

    CHECK(observer->isPlantAvailable(rose) == true);

    inventory->removeStock(rose, 8);

    CHECK(observer->isPlantAvailable(rose) == false);
    CHECK(observer->getPlantQuantity(rose) == 0);

    delete rose;
    inventory->detach(observer);
    delete observer;
}

TEST_CASE("SalesFloorObserver: Multiple Plant Types Tracking")
{
    PlantInventory *inventory = PlantInventory::getInstance();
    SalesFloorObserver *observer = new SalesFloorObserver(inventory);

    Rose *rose = createSalesTestRose(25.0, "Multi Rose");
    Oak *oak = createSalesTestOak(90.0, "Multi Oak");

    inventory->addStock(rose, 12);
    inventory->addStock(oak, 7);

    CHECK(observer->isPlantAvailable(rose) == true);
    CHECK(observer->isPlantAvailable(oak) == true);
    CHECK(observer->getPlantQuantity(rose) == 12);
    CHECK(observer->getPlantQuantity(oak) == 7);

    cleanupSalesPlant(rose, 12);
    cleanupSalesPlant(oak, 7);
    delete rose;
    delete oak;
    inventory->detach(observer);
    delete observer;
}
