#include <iostream>

#include "Plant.h"

int main() {
    Plant plant("Rose");

    // Initial state is SeedState
    std::cout << "Initial state: " << plant.getCurrentState() << std::endl;

    // Simulate growth
    plant.setCurrentWater(50);
    plant.setCurrentSunlight(50);
    plant.setCurrentNutrients(50);
    plant.request();
    std::cout << "State after germination: " << plant.getCurrentState() << std::endl;

    // Simulate growth to maturity
    plant.setCurrentWater(70);
    plant.setCurrentSunlight(70);
    plant.setCurrentNutrients(70);
    plant.request();
    std::cout << "State after maturity: " << plant.getCurrentState() << std::endl;

    // Simulate distress
    plant.setCurrentWater(10);
    plant.setCurrentSunlight(10);
    plant.setCurrentNutrients(10);
    plant.request();
    std::cout << "State after distress: " << plant.getCurrentState() << std::endl;

    // Simulate withered
    plant.setCurrentWater(5);
    plant.setCurrentSunlight(5);
    plant.setCurrentNutrients(5);
    plant.request();
    std::cout << "State after withered: " << plant.getCurrentState() << std::endl;

    return 0;
}
