

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
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

TEST_CASE("SeedState: applyCare increments growthProgress")
{
    Rose *r = new Rose(10.0, "TestRose");
    r->setCategory("Sunny");
    PlantLifeCycle *roseCycle =
        new PlantLifeCycle(r, std::make_unique<SeedState>(), "Rose #001");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    r->setGrowthProgress(0);

    PlantCareRoutine *routine = new Sunny();
    roseCycle->getStateObj()->applyCare(roseCycle, r, routine);

    CHECK(r->getGrowthProgress() == 1);

    delete routine;
    delete roseCycle;
    delete r;
}

TEST_CASE("SeedState: applyCare transitions to Seedling after 3 cares "
          "(growthProgress-driven)")
{
    Rose *r = new Rose(12.0, "GrowRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    r->setGrowthProgress(0);

    PlantLifeCycle *plc =
        new PlantLifeCycle(r, std::make_unique<SeedState>(), "GrowRose #1");
    PlantCareRoutine *routine = new Sunny();

    for (int i = 0; i < 3; ++i)
    {
        plc->getStateObj()->applyCare(plc, r, routine);
    }

    CHECK(plc->getState() == "Seedling");

    delete routine;
    delete plc;
    delete r;
}

TEST_CASE("SeedState: evaluate transitions when growthProgress >= 3")
{
    Rose *r = new Rose(11.0, "EvalRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(40);
    r->setCurrentSunlight(40);
    r->setCurrentNutrients(40);

    r->setGrowthProgress(3);

    PlantLifeCycle *roseCycle =
        new PlantLifeCycle(r, std::make_unique<SeedState>(), "EvalRose #1");

    bool healthy = roseCycle->updatePlant();

    CHECK(healthy == true);
    CHECK(roseCycle->getState() == "Seedling");

    delete roseCycle;
    delete r;
}

TEST_CASE("SeedState: evaluate does NOT transition when growthProgress < 3")
{
    Rose *r = new Rose(11.0, "NoGrowRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(40);
    r->setCurrentSunlight(40);
    r->setCurrentNutrients(40);

    r->setGrowthProgress(2);

    PlantLifeCycle *roseCycle =
        new PlantLifeCycle(r, std::make_unique<SeedState>(), "NoGrowRose #1");

    bool healthy = roseCycle->updatePlant();

    CHECK(healthy == false);
    CHECK(roseCycle->getState() == "Seed");

    delete roseCycle;
    delete r;
}

TEST_CASE("SeedState: growthProgress >= 3 transitions regardless of resource "
          "bounds (edge case)")
{
    Rose *r = new Rose(11.0, "EdgeRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(40);
    r->setCurrentSunlight(40);
    r->setCurrentNutrients(40);

    r->setGrowthProgress(3);

    PlantLifeCycle *roseCycle =
        new PlantLifeCycle(r, std::make_unique<SeedState>(), "EdgeRose #1");

    bool healthy = roseCycle->updatePlant();

    CHECK(healthy == true);
    CHECK(roseCycle->getState() == "Seedling");

    delete roseCycle;
    delete r;
}