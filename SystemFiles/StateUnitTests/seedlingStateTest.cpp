
#include "doctest.h"

#include "../Plant.h"
#include "../PLantLifeCycle.h"
#include "../PlantCareRoutine.h"

#include "../SeedState.h"
#include "../SeedlingState.h"
#include "../MatureState.h"
#include "../DistressedState.h"
#include "../WitheredState.h"

#include "../Rose.h"
#include "../Sunny.h"
#include "../FloorEmployee.h"


TEST_CASE("SeedlingState: applyCare increments growthProgress") {
    Rose* r = new Rose(10.0, "SeedlingTestRose");
    r->setCategory("Sunny");
    PlantLifeCycle* cycle = new PlantLifeCycle(r, std::make_unique<SeedlingState>(), "Seedling #1");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    r->setGrowthProgress(0);

    PlantCareRoutine* routine = new Sunny();
    cycle->getStateObj()->applyCare(cycle, r, routine);

    CHECK(r->getGrowthProgress() == 1);

    delete routine;
    delete cycle;
    delete r;
}

TEST_CASE("SeedlingState: applyCare transitions to Mature when growthProgress reaches 5 and within min..max") {
    Rose* r = new Rose(12.0, "GrowToMatureRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    r->setGrowthProgress(4);

    PlantLifeCycle* cycle = new PlantLifeCycle(r, std::make_unique<SeedlingState>(), "GrowToMature #1");
    PlantCareRoutine* routine = new Sunny();

    cycle->getStateObj()->applyCare(cycle, r, routine);

    CHECK(r->getGrowthProgress() == 5);
    CHECK(cycle->getState() == "Mature");

    delete routine;
    delete cycle;
    delete r;
}

TEST_CASE("SeedlingState: evaluate transitions to Mature when growthProgress >= 5 (evaluate path)") {
    Rose* r = new Rose(11.0, "EvalSeedlingRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    r->setGrowthProgress(5);

    PlantLifeCycle* cycle = new PlantLifeCycle(r, std::make_unique<SeedlingState>(), "EvalSeedling #1");

    bool healthy = cycle->updatePlant(); 

    CHECK(healthy == true);
    CHECK(cycle->getState() == "Mature");

    delete cycle;
    delete r;
}

TEST_CASE("SeedlingState: evaluate does NOT transition when growthProgress < 5") {
    Rose* r = new Rose(11.0, "NoMatureRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(50);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);

    r->setGrowthProgress(3);

    PlantLifeCycle* cycle = new PlantLifeCycle(r, std::make_unique<SeedlingState>(), "NoMature #1");

    bool healthy = cycle->updatePlant();

    CHECK(healthy == false);
    CHECK(cycle->getState() == "Seedling");

    delete cycle;
    delete r;
}

TEST_CASE("SeedlingState: applyCare sets Distressed when levels are below min (edge case)") {
    Rose* r = new Rose(11.0, "DistressEdgeRose");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(0);
    r->setCurrentSunlight(0);
    r->setCurrentNutrients(0);

    r->setGrowthProgress(2);

    PlantLifeCycle* cycle = new PlantLifeCycle(r, std::make_unique<SeedlingState>(), "DistressEdge #1");
    PlantCareRoutine* routine = new Sunny();

    cycle->getStateObj()->applyCare(cycle, r, routine);

    CHECK(cycle->getState() == "Distressed");

    delete routine;
    delete cycle;
    delete r;
}

TEST_CASE("SeedlingState: growthProgress >=5 but resources below min should NOT transition to Mature via evaluate") {
    Rose* r = new Rose(11.0, "BadResourceButGrown");
    r->setCategory("Sunny");

    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    r->setCurrentWater(0);
    r->setCurrentSunlight(0);
    r->setCurrentNutrients(0);

    r->setGrowthProgress(5);

    PlantLifeCycle* cycle = new PlantLifeCycle(r, std::make_unique<SeedlingState>(), "BadResourceButGrown #1");

    bool healthy = cycle->updatePlant(); 

    CHECK(healthy == false);
    CHECK(cycle->getState() == "Seedling");

    delete cycle;
    delete r;
}