#ifndef GREENHOUSE_UNIT_TEST_H
#define GREENHOUSE_UNIT_TEST_H

#include "Plant.h"
#include "PlantInventory.h"
#include "AddStock.h"
#include "RemoveStock.h"
#include "PlantStock.h"
#include "PlantFactory.h"
#include "TreeFactory.h"
#include "FlowerFactory.h"
#include "Oak.h"
#include "Rose.h"
#include <iostream>

/**
 * @class GreenhouseUnitTest
 * @brief Unit tests for greenhouse plant system (singleton, factories and commands design patterns)
 */
class GreenhouseUnitTest {
public:
    /**
     * @brief Runs all tests
     */
    static void run();
    
private:
    static void testPlant();
    static void testPlantInventory();
    static void testAddStock();
    static void testRemoveStock();
    static void testPlantStock();
    static void testPlantFactory();
    static void testTreeFactory();
    static void testFlowerFactory();
    static void testOak();
    static void testRose();
};

#endif
