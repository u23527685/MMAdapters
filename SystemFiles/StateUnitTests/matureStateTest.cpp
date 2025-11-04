
#include "doctest.h"

#include "../Plant.h"
#include "../PlantCareRoutine.h"
#include "../PlantLifeCycle.h"

#include "../DistressedState.h"
#include "../MatureState.h"
#include "../SeedState.h"
#include "../SeedlingState.h"
#include "../WitheredState.h"

#include "../FloorEmployee.h"
#include "../Rose.h"
#include "../Sunny.h"

TEST_CASE("MatureState: evaluate returns healthy when all resources >= 120% of "
          "min and <= max")
{
    Rose *r = new Rose(10.0, "HealthyMature");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    PlantLifeCycle *plc = new PlantLifeCycle(r, std::make_unique<MatureState>(),
                                             "HealthyMature #1");

    bool healthy = plc->updatePlant();

    CHECK(healthy == true);
    CHECK(plc->getState() == "Mature");

    delete plc;
    delete r;
}

TEST_CASE(
    "MatureState: evaluate transitions to Distressed when any resource == min")
{
    Rose *r = new Rose(10.0, "DistressCase");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(0);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    PlantLifeCycle *plc = new PlantLifeCycle(r, std::make_unique<MatureState>(),
                                             "DistressCase #1");

    bool healthy = plc->updatePlant();

    CHECK(healthy == false);
    CHECK(plc->getState() == "Distressed");

    delete plc;
    delete r;
}

TEST_CASE(
    "MatureState: evaluate transitions to Withered when any resource < min")
{
    Rose *r = new Rose(10.0, "WitheredCase");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(-1);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    PlantLifeCycle *plc = new PlantLifeCycle(r, std::make_unique<MatureState>(),
                                             "WitheredCase #1");

    bool healthy = plc->updatePlant();

    CHECK(healthy == false);
    CHECK(plc->getState() == "Withered");

    delete plc;
    delete r;
}

TEST_CASE("MatureState: applyCare can raise borderline resources into healthy "
          "range (applyCare + evaluate)")
{
    Rose *r = new Rose(10.0, "RecoverMature");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    PlantLifeCycle *plc = new PlantLifeCycle(r, std::make_unique<MatureState>(),
                                             "RecoverMature #1");
    PlantCareRoutine *routine = new Sunny();

    plc->getStateObj()->applyCare(plc, r, routine);

    bool healthy = plc->updatePlant();
    CHECK(healthy == true);
    CHECK(plc->getState() == "Mature");

    delete routine;
    delete plc;
    delete r;
}

TEST_CASE("MatureState: evaluate transitions to Distressed when multiple "
          "resources == min")
{
    Rose *r = new Rose(10.0, "MultiDistressCase");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    // Step 1: Start healthy in Mature
    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);
    r->setGrowthProgress(5);

    PlantLifeCycle *plc = new PlantLifeCycle(r, std::make_unique<MatureState>(),
                                             "MultiDistressCase #1");

    // Simulate time: drop TWO resources to exactly min
    r->setCurrentWater(0);
    r->setCurrentSunlight(0);
    r->setCurrentNutrients(0);

    // First evaluation: should go to Distressed
    bool healthy1 = plc->updatePlant();
    CHECK(healthy1 == false);
    CHECK(plc->getState() == "Distressed");

    // Now simulate time passing: drop ONE below min
    r->setCurrentWater(5); // < minWater

    // Second evaluation: from Distressed, any < min → Withered
    bool healthy2 = plc->updatePlant();
    CHECK(healthy2 == true);
    CHECK(plc->getState() == "Mature");

    delete plc;
    delete r;
}

TEST_CASE("MatureState: evaluate transitions to Withered when multiple "
          "resources < min")
{
    Rose *r = new Rose(10.0, "MultiWitheredCase");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(-1);
    r->setCurrentSunlight(-1);
    r->setCurrentNutrients(-1);

    PlantLifeCycle *plc = new PlantLifeCycle(r, std::make_unique<MatureState>(),
                                             "MultiWitheredCase #1");

    bool healthy = plc->updatePlant();

    CHECK(healthy == false);
    CHECK(plc->getState() == "Withered");

    delete plc;
    delete r;
}

TEST_CASE("MatureState: evaluate returns healthy when resources are at max")
{
    Rose *r = new Rose(10.0, "MaxResources");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(100);
    r->setCurrentSunlight(100);
    r->setCurrentNutrients(100);

    PlantLifeCycle *plc = new PlantLifeCycle(r, std::make_unique<MatureState>(),
                                             "MaxResources #1");

    bool healthy = plc->updatePlant();

    CHECK(healthy == true);
    CHECK(plc->getState() == "Mature");

    delete plc;
    delete r;
}