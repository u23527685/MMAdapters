// This file includes test_core_components without
// DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN So it can be included in TestingMain.cpp

#include "../FloorEmployee.h"
#include "../PLantLifeCycle.h"
#include "../Plant.h"
#include "../PlantCareRoutine.h"
#include "../SeedState.h"
#include "../Shade.h"
#include "../Staff.h"
#include "../Sunny.h"
#include "../Temperate.h"
#include "../Tropical.h"

Plant *createPLCOTestPlant(double price = 10.0, std::string desc = "Test Plant",
                           int maxWater = 200, int maxSunlight = 200,
                           int maxNutrients = 200)
{
    Plant *p = new Plant(price, desc);
    p->setMaxWater(maxWater);
    p->setMaxSunlight(maxSunlight);
    p->setMaxNutrients(maxNutrients);
    p->setCurrentWater(0);
    p->setCurrentSunlight(0);
    p->setCurrentNutrients(0);
    p->setCategory("Tropical");
    return p;
}

TEST_CASE("PLCO: Plant Resource Limits and Getters")
{
    Plant *plant = createPLCOTestPlant(10.0, "Test Plant", 200, 200, 200);
    plant->setCurrentWater(150);
    CHECK(plant->getCurrentWater() == 150);

    plant->setCurrentSunlight(150);
    CHECK(plant->getCurrentSunlight() == 150);

    plant->setCurrentNutrients(150);
    CHECK(plant->getCurrentNutrients() == 150);

    CHECK(plant->getMaxWater() == 200);
    CHECK(plant->getMaxSunlight() == 200);
    CHECK(plant->getMaxNutrients() == 200);

    delete plant;
}

TEST_CASE("PLCO: PlantLifeCycle Observer Attachment and Detachment")
{
    Plant *plant = createPLCOTestPlant();
    std::unique_ptr<PlantState> initialState = std::make_unique<SeedState>();
    PlantLifeCycle cycle(plant, std::move(initialState), "TestCycle");

    FloorEmployee observer("TestStaff");
    cycle.attach(&observer);

    CHECK(cycle.getState() == "Seed");
    CHECK(cycle.getPlant() == plant);
    CHECK(std::find(cycle.observersBegin(), cycle.observersEnd(), &observer) !=
          cycle.observersEnd());

    cycle.detach(&observer);
    CHECK(std::find(cycle.observersBegin(), cycle.observersEnd(), &observer) ==
          cycle.observersEnd());

    delete plant;
}

TEST_CASE("PLCO: PlantLifeCycle Simulate Time Passing and Update")
{
    Plant *plant = createPLCOTestPlant();
    std::unique_ptr<PlantState> initialState = std::make_unique<SeedState>();
    PlantLifeCycle cycle(plant, std::move(initialState), "TestCycle");
    plant->setCurrentNutrients(200);
    plant->setCurrentWater(200);
    plant->setCurrentSunlight(200);

    cycle.simulateTimePassing();
    CHECK(plant->getCurrentWater() == 190);
    CHECK(plant->getCurrentSunlight() == 190);
    CHECK(plant->getCurrentNutrients() == 190);

    plant->increaseGrowthProgress();
    plant->increaseGrowthProgress();
    plant->increaseGrowthProgress();
    plant->increaseGrowthProgress();
    plant->increaseGrowthProgress();

    bool updated = cycle.updatePlant();
    CHECK(updated == true);

    plant->setCurrentWater(180);
    updated = cycle.updatePlant();
    CHECK(updated == true);

    delete plant;
}

TEST_CASE("PLCO: PlantCareRoutine Factory Method")
{
    Plant *tropicalPlant = createPLCOTestPlant();
    tropicalPlant->setCategory("Tropical");
    std::unique_ptr<PlantCareRoutine> routine =
        PlantCareRoutine::PlantCare(tropicalPlant);
    CHECK(dynamic_cast<Tropical *>(routine.get()) != nullptr);

    Plant *sunnyPlant = createPLCOTestPlant();
    sunnyPlant->setCategory("Sunny");
    routine = PlantCareRoutine::PlantCare(sunnyPlant);
    CHECK(dynamic_cast<Sunny *>(routine.get()) != nullptr);

    Plant *shadePlant = createPLCOTestPlant();
    shadePlant->setCategory("Shade");
    routine = PlantCareRoutine::PlantCare(shadePlant);
    CHECK(dynamic_cast<Shade *>(routine.get()) != nullptr);

    Plant *temperatePlant = createPLCOTestPlant();
    temperatePlant->setCategory("Temperate");
    routine = PlantCareRoutine::PlantCare(temperatePlant);
    CHECK(dynamic_cast<Temperate *>(routine.get()) != nullptr);

    Plant *invalidPlant = createPLCOTestPlant();
    invalidPlant->setCategory("Unknown");
    routine = PlantCareRoutine::PlantCare(invalidPlant);
    CHECK(routine == nullptr);

    delete tropicalPlant;
    delete sunnyPlant;
    delete shadePlant;
    delete temperatePlant;
    delete invalidPlant;
}

TEST_CASE("PLCO: Tropical Care Application")
{
    Plant *plant = createPLCOTestPlant();
    plant->setCategory("Tropical");
    std::unique_ptr<PlantCareRoutine> routine =
        PlantCareRoutine::PlantCare(plant);
    Tropical *tropical = dynamic_cast<Tropical *>(routine.get());
    CHECK(tropical != nullptr);

    tropical->Watering(plant);
    CHECK(plant->getCurrentWater() == 50);

    tropical->Sunlight(plant);
    CHECK(plant->getCurrentSunlight() == 40);

    tropical->Fertilizing(plant);
    CHECK(plant->getCurrentNutrients() == 80);

    delete plant;
}

TEST_CASE("PLCO: Sunny Care Application")
{
    Plant *plant = createPLCOTestPlant();
    plant->setCategory("Sunny");
    std::unique_ptr<PlantCareRoutine> routine =
        PlantCareRoutine::PlantCare(plant);
    Sunny *sunny = dynamic_cast<Sunny *>(routine.get());
    CHECK(sunny != nullptr);

    sunny->Watering(plant);
    CHECK(plant->getCurrentWater() == 100);

    sunny->Sunlight(plant);
    CHECK(plant->getCurrentSunlight() == 60);

    sunny->Fertilizing(plant);
    CHECK(plant->getCurrentNutrients() == 40);

    delete plant;
}

TEST_CASE("PLCO: Shade Care Application")
{
    Plant *plant = createPLCOTestPlant();
    plant->setCategory("Shade");
    std::unique_ptr<PlantCareRoutine> routine =
        PlantCareRoutine::PlantCare(plant);
    Shade *shade = dynamic_cast<Shade *>(routine.get());
    CHECK(shade != nullptr);

    shade->Watering(plant);
    CHECK(plant->getCurrentWater() == 20);

    shade->Sunlight(plant);
    CHECK(plant->getCurrentSunlight() == 0);

    shade->Fertilizing(plant);
    CHECK(plant->getCurrentNutrients() == 80);

    delete plant;
}

TEST_CASE("PLCO: Temperate Care Application")
{
    Plant *plant = createPLCOTestPlant();
    plant->setCategory("Temperate");
    std::unique_ptr<PlantCareRoutine> routine =
        PlantCareRoutine::PlantCare(plant);
    Temperate *temperate = dynamic_cast<Temperate *>(routine.get());
    CHECK(temperate != nullptr);

    temperate->Watering(plant);
    CHECK(plant->getCurrentWater() == 20);

    temperate->Sunlight(plant);
    CHECK(plant->getCurrentSunlight() == 60);

    temperate->Fertilizing(plant);
    CHECK(plant->getCurrentNutrients() == 40);

    delete plant;
}
