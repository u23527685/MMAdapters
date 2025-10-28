#include <iostream>
#include "Plant.h"
#include "PlantLifeCycle.h"
#include "SeedState.h"
#include "Staff.h"
#include "PlantCareRoutine.h"

int main() {

    Plant* myPlant = new Plant("Lavender");
    myPlant->setCurrentWater(5);
    myPlant->setCurrentSunlight(5);
    myPlant->setCurrentNutrients(5);


    PlantState* initialState = new SeedState();
    PlantLifeCycle* lifecycle = new PlantLifeCycle(myPlant, initialState, "LavenderLife");


    //Staff* alice = new Staff("Alice");
    //lifecycle->attach(alice);


    std::cout << "\n--- Initial Evaluation ---\n";
    lifecycle->isHealthy(); // This will call SeedState::evaluate and possibly change state


    for (int day = 1; day <= 3; ++day) {
        std::cout << "\n--- Day " << day << " ---\n";
        lifecycle->notify(); // Triggers Staff::update
        lifecycle->isHealthy(); // Re-evaluate after care
    }

    delete lifecycle;
    delete myPlant;
    //delete alice;

    return 0;
}
