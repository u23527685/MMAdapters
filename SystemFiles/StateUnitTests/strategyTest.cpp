
#include "doctest.h"

#include "../Plant.h"
#include "../HighWaterStrategy.h"
#include "../LowWaterStrategy.h"
#include "../MediumWaterStrategy.h"
#include "../ShadeStrategy.h" 
#include "../FullSunStrategy.h"
#include "../PartialSunStrategy.h"
#include "../OrganicFertilizer.h"
#include "../InorganicFertilizer.h"

TEST_CASE("Plant: set water above max") {
    Plant p(10.0, "Test Plant");
    p.setMaxWater(100);
    p.setCurrentWater(150);

    CHECK(p.getCurrentWater() == 100);
}

TEST_CASE("Plant: set nutrients above max") {
    Plant p(10.0, "Test Plant");
    p.setMaxNutrients(100);
    p.setCurrentNutrients(150);

    CHECK(p.getCurrentNutrients() == 100);
}

TEST_CASE("Plant: set sunlight above max") {
    Plant p(10.0, "Test Plant");
    p.setMaxSunlight(100);
    p.setCurrentSunlight(150);

    CHECK(p.getCurrentSunlight() == 100);
}

// Water strategy tests
TEST_CASE("HighWaterStrategy: apply water") {
    Plant p(10.0, "Test Plant");
    p.setMaxWater(100);
    p.setCurrentWater(0);

    HighWaterStrategy strategy;
    strategy.applyWater(&p);

    CHECK(p.getCurrentWater() == 100);
}

TEST_CASE("LowWaterStrategy: apply water") {
    Plant p(10.0, "Test Plant");
    p.setMaxWater(100);
    p.setCurrentWater(0);

    LowWaterStrategy strategy;
    strategy.applyWater(&p);

    CHECK(p.getCurrentWater() == 20);
}

TEST_CASE("MediumWaterStrategy: apply water") {
    Plant p(10.0, "Test Plant");
    p.setMaxWater(100);
    p.setCurrentWater(0);

    MediumWaterStrategy strategy;
    strategy.applyWater(&p);

    CHECK(p.getCurrentWater() == 50);
}

// Sunlight strategy tests
TEST_CASE("FullSunStrategy: apply sunlight") {
    Plant p(10.0, "Test Plant");
    p.setMaxSunlight(100);
    p.setCurrentSunlight(0);

    FullSunStrategy strategy;
    strategy.applySunlight(&p);

    CHECK(p.getCurrentSunlight() == 60);
}

TEST_CASE("PartialSunStrategy: apply sunlight") {
    Plant p(10.0, "Test Plant");
    p.setMaxSunlight(100);
    p.setCurrentSunlight(0);

    PartialSunStrategy strategy;
    strategy.applySunlight(&p);

    CHECK(p.getCurrentSunlight() == 40);
}

// Fertilizer strategy tests
TEST_CASE("InorganicFertilizer: apply fertilizer") {
    Plant p(10.0, "Test Plant");
    p.setMaxNutrients(100);
    p.setCurrentNutrients(0);

    InorganicFertilizer strategy;
    strategy.applyFertilizer(&p);

    CHECK(p.getCurrentNutrients() == 40);
}

TEST_CASE("OrganicFertilizer: apply fertilizer") {
    Plant p(10.0, "Test Plant");
    p.setMaxNutrients(100);
    p.setCurrentNutrients(0);

    OrganicFertilizer strategy;
    strategy.applyFertilizer(&p);

    CHECK(p.getCurrentNutrients() == 80);
}

// Edge cases
TEST_CASE("Plant: negative price") {
    Plant p(-10.0, "Test Plant");
    CHECK(p.getPrice() == -10.0); // Note: This might not be the desired behavior
}

TEST_CASE("Plant: zero price") {
    Plant p(0.0, "Test Plant");
    CHECK(p.getPrice() == 0.0);
}

TEST_CASE("Plant: negative growth progress") {
    Plant p(10.0, "Test Plant");
    p.setGrowthProgress(-5);
    CHECK(p.getGrowthProgress() == -5); // Note: This might not be the desired behavior
}

TEST_CASE("Water strategy: water above max") {
    Plant p(10.0, "Test Plant");
    p.setMaxWater(100);
    p.setCurrentWater(150);

    HighWaterStrategy strategy;
    strategy.applyWater(&p);

    CHECK(p.getCurrentWater() == 100);
}

TEST_CASE("Sunlight strategy: sunlight above max") {
    Plant p(10.0, "Test Plant");
    p.setMaxSunlight(100);
    p.setCurrentSunlight(150);

    FullSunStrategy strategy;
    strategy.applySunlight(&p);

    CHECK(p.getCurrentSunlight() == 100);
}

TEST_CASE("Fertilizer strategy: fertilizer above max") {
    Plant p(10.0, "Test Plant");
    p.setMaxNutrients(100);
    p.setCurrentNutrients(150);

    InorganicFertilizer strategy;
    strategy.applyFertilizer(&p);

    CHECK(p.getCurrentNutrients() == 100);
}