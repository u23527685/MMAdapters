
#include "doctest.h"

#include "../PLantLifeCycle.h"
#include "../Plant.h"
#include "../PlantCareRoutine.h"
#include "../PlantLifeCycle.h"

#include "../DistressedState.h"
#include "../MatureState.h"
#include "../SeedlingState.h"
#include "../WitheredState.h"

#include "../Rose.h"
#include "../Sunny.h"

TEST_CASE("DistressedState: evaluate -> Withered when any resource < min")
{
    Rose *r = new Rose(10.0, "D1");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(-1);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);
    r->setGrowthProgress(5);

    PlantLifeCycle *plc =
        new PlantLifeCycle(r, std::make_unique<DistressedState>(), "D1 #1");

    bool healthy = plc->updatePlant();
    CHECK(healthy == false);
    CHECK(plc->getState() == "Withered");

    delete plc;
    delete r;
}

TEST_CASE("DistressedState: evaluate stays Distressed when not recovered")
{
    Rose *r = new Rose(10.0, "D2");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(12);
    r->setCurrentSunlight(12);
    r->setCurrentNutrients(12);
    r->setGrowthProgress(5);

    PlantLifeCycle *plc =
        new PlantLifeCycle(r, std::make_unique<DistressedState>(), "D2 #1");

    bool healthy = plc->updatePlant();
    CHECK(healthy == true);
    CHECK(plc->getState() == "Mature");

    delete plc;
    delete r;
}

TEST_CASE("DistressedState: applyCare recovers to Mature when resources >= "
          "healthy and growthProgress >=5")
{
    Rose *r = new Rose(10.0, "D3");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);
    r->setGrowthProgress(5);

    PlantLifeCycle *plc =
        new PlantLifeCycle(r, std::make_unique<DistressedState>(), "D3 #1");
    PlantCareRoutine *routine = new Sunny();

    plc->getStateObj()->applyCare(plc, r, routine);

    CHECK(plc->getState() == "Mature");

    delete routine;
    delete plc;
    delete r;
}

TEST_CASE("DistressedState: applyCare recovers to Seedling when resources >= "
          "healthy but growthProgress < 5")
{
    Rose *r = new Rose(10.0, "D4");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);
    r->setGrowthProgress(3);

    PlantLifeCycle *plc =
        new PlantLifeCycle(r, std::make_unique<DistressedState>(), "D4 #1");
    PlantCareRoutine *routine = new Sunny();

    plc->getStateObj()->applyCare(plc, r, routine);

    CHECK(plc->getState() == "Seedling");

    delete routine;
    delete plc;
    delete r;
}

TEST_CASE("DistressedState: edge case - exactly at min remains Distressed (not "
          "Withered)")
{
    Rose *r = new Rose(10.0, "D5");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(12);
    r->setCurrentSunlight(12);
    r->setCurrentNutrients(12);
    r->setGrowthProgress(5);

    PlantLifeCycle *plc =
        new PlantLifeCycle(r, std::make_unique<DistressedState>(), "D5 #1");

    bool healthy = plc->updatePlant();
    CHECK(healthy == true);
    CHECK(plc->getState() == "Mature");

    delete plc;
    delete r;
}

TEST_CASE("DistressedState: evaluate -> Withered when multiple resources < min")
{
    Rose *r = new Rose(10.0, "MultiWithered");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(-1);
    r->setCurrentSunlight(-1);
    r->setCurrentNutrients(-1);
    r->setGrowthProgress(5);

    PlantLifeCycle *plc = new PlantLifeCycle(
        r, std::make_unique<DistressedState>(), "MultiWithered #1");

    bool healthy = plc->updatePlant();
    CHECK(healthy == false);
    CHECK(plc->getState() == "Withered");

    delete plc;
    delete r;
}

TEST_CASE("DistressedState: evaluate stays Distressed when resources are "
          "exactly at healthy threshold but not above")
{
    Rose *r = new Rose(10.0, "ThresholdDistressed");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(12);
    r->setCurrentSunlight(12);
    r->setCurrentNutrients(12);
    r->setGrowthProgress(5);

    PlantLifeCycle *plc = new PlantLifeCycle(
        r, std::make_unique<DistressedState>(), "ThresholdDistressed #1");

    bool healthy = plc->updatePlant();
    CHECK(healthy == true);
    CHECK(plc->getState() == "Mature");

    delete plc;
    delete r;
}