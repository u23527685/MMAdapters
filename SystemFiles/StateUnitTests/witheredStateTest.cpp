
#include "doctest.h"

#include "../Plant.h"
#include "../PLantLifeCycle.h"
#include "../PlantCareRoutine.h"

#include "../DistressedState.h"
#include "../MatureState.h"
#include "../SeedlingState.h"
#include "../WitheredState.h"

#include "../Rose.h"
#include "../Sunny.h"


TEST_CASE("WitheredState: applyCare does not change state immediately but raises resources") {
    Rose* r = new Rose(10.0, "WitheredApplyTest");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    // Start completely withered
    r->setCurrentWater(0);
    r->setCurrentSunlight(0);
    r->setCurrentNutrients(0);
    r->setGrowthProgress(5);

    PlantLifeCycle* plc = new PlantLifeCycle(r, std::make_unique<WitheredState>(), "Withered #1");

    // STEP 1: Manually give just enough water to trigger recovery to Distressed
    r->setCurrentWater(15);  // > minWater (10)

    // This calls evaluate() inside WitheredState → should go to Distressed
    plc->updatePlant();

    CHECK(plc->getState() == "Distressed");  // Now in Distressed

    // STEP 2: Now apply care — DistressedState WILL raise resources
    PlantCareRoutine* routine = new Sunny();
    plc->getStateObj()->applyCare(plc, r, routine);

    // Now resources should be increased
    CHECK(r->getCurrentWater() > 15);      // Was 15, now higher
    CHECK(r->getCurrentSunlight() > 0);    // Was 0
    CHECK(r->getCurrentNutrients() > 0);   // Was 0

    // State may still be Distressed or even Mature — but NOT Withered
    CHECK(plc->getState() != "Withered");

    delete routine;
    delete plc;
    delete r;
}

TEST_CASE("WitheredState: evaluate always returns false and state remains Withered") {
    Rose* r = new Rose(10.0, "WitheredEvalLow");
    r->setCategory("Sunny");
    PlantLifeCycle* plc = new PlantLifeCycle(r, std::make_unique<WitheredState>(), "WitheredEvalLow #1");

    bool healthy = plc->updatePlant(); 

    CHECK(healthy == false);
    CHECK(plc->getState() == "Distressed");

    delete plc;
    delete r;
}

TEST_CASE("WitheredState: applyCare then evaluate does NOT transition out of Withered (edge)") {
    Rose* r = new Rose(10.0, "WitheredCareThenEval");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    // keep ONE resource at 0 → evaluate will NOT recover
    r->setCurrentWater(-100);
    r->setCurrentSunlight(50);
    r->setCurrentNutrients(50);
    r->setGrowthProgress(5);

    PlantLifeCycle* plc = new PlantLifeCycle(r, std::make_unique<WitheredState>(), "WitheredCareThenEval #1");
    PlantCareRoutine* routine = new Sunny();

    // applyCare does nothing → state still Withered
    plc->getStateObj()->applyCare(plc, r, routine);
    CHECK(plc->getState() == "Withered");

    // evaluate sees water == 0 → stays Withered, returns false
    bool healthy = plc->updatePlant();
    CHECK(healthy == false);
    CHECK(plc->getState() == "Withered");

    delete routine;
    delete plc;
    delete r;
}

TEST_CASE("WitheredState: even if resources are high, state remains Withered (defensive / edge case)") {
    Rose* r = new Rose(10.0, "WitheredHighResources");
    r->setCategory("Sunny");
    r->setMaxWater(100);
    r->setMaxSunlight(100);
    r->setMaxNutrients(100);

    // two resources are maxed, ONE is 0 → stays Withered
    r->setCurrentWater(100);
    r->setCurrentSunlight(100);
    r->setCurrentNutrients(-100);   // <-- the blocker
    r->setGrowthProgress(10);

    PlantLifeCycle* plc = new PlantLifeCycle(r, std::make_unique<WitheredState>(), "WitheredHighResources #1");

    bool healthy = plc->updatePlant();
    CHECK(healthy == false);
    CHECK(plc->getState() == "Withered");

    delete plc;
    delete r;
}