#include "Staff.h"
#include "SalesFloorObserver.h"

Staff::Staff(std::string name){
    this->name=name;
    next=nullptr;
}

Staff::~Staff(){}

std::string Staff::getName(){
    return name;
}

void Staff::setNext(Staff* staff){
    next=staff;
}

Staff* Staff::getNext(){
    return next;
}

void Staff::getStock(){
    salesFloorObserver= new SalesFloorObserver(PlantInventory::getInstance());
    salesFloorObserver->displayAvailablePlants();
    delete salesFloorObserver;
}

/**
void Staff::update(PlantLifeCycle* p){
    Plant* plant = p->getPlant();
    std::string state = p->getState();

    std::cout<< "[Staff] " << name << " noticed " << p->getName() << " is now in state: " << state << std::endl;
    if(!p->isHealthy()){
        careRoutine = careRoutine->PlantCare(plant);
        std::cout << "[Staff] " << name;
        if(state == "Withered" && p->getCurrentWater() < 10  ){
            careRoutine->Watering(plant);
        } else if(state == "Withered" &&p->getCurrentSunlight() < 10){
            careRoutine->Sunlight(plant);
        } else if(state == "Withered" && p->getCurrentNutrients() < 10){
            careRoutine->Fertilizing(plant);
        }

        if(state == "Distressed" && p->getCurrentWater() < 20  ){
            careRoutine->Watering(plant);
        } else if(state == "Distressed" &&p->getCurrentSunlight() < 20){
            careRoutine->Sunlight(plant);
        } else if(state == "Distressed" && p->getCurrentNutrients() < 20){
            careRoutine->Fertilizing(plant);
        } 
    } else{
        std::cout << "[Staff] " << name << " continues regular maintenance of " << p->getName() << std::endl;
    }
}


void Staff::update(PlantLifeCycle* p) {
//     Plant* plant = p->getPlant();
//     std::string stateName = p->getState();

//     std::cout << "[Staff] " << name << " noticed " << p->getName() << " is now in state: " << stateName << std::endl;

//     careRoutine = careRoutine->PlantCare(plant);

//    if (!p->isHealthy()) {
//         std::cout << "[Staff] " << name << " is applying care..." << std::endl;
//         p->getStateObj()->applyCare(p, plant, careRoutine);
//         //delete careRoutine;
//     } else {
//         std::cout << "[Staff] " << name << " continues regular maintenance of "
//                   << p->getName() << std::endl;
//     }
    Plant* plant = p->getPlant();
    std::string stateName = p->getState();

    std::cout << "[Staff] " << name << " noticed " << p->getName() << " is now in state: " << stateName << std::endl;

    // Create care routine
    PlantCareRoutine* routine = PlantCareRoutine::PlantCare(plant);
    
    // Apply care through current state
    PlantState* currentState = p->getStateObj();
    if (currentState) {
        currentState->applyCare(p, plant, routine);
    }
    
    // **FIX: Delete the routine immediately after use**
    delete routine;
    
    std::cout << "[Staff] " << name << " continues regular maintenance of "
                   << p->getName() << std::endl;
}
**/
void Staff::isHealthy(PlantLifeCycle* p) {
    Plant* plant = p->getPlant();
    std::string stateName = p->getState();

    std::cout << "[Staff] " << name << " noticed " << p->getName() << " is now in state: " << stateName << std::endl;

    careRoutine = careRoutine->PlantCare(plant);

    if (!p->updatePlant()) {
        std::cout << "[Staff] " << name << " is applying care..." << std::endl;
        p->getStateObj()->applyCare(p, plant, careRoutine);
        delete careRoutine;
    } else {
        std::cout << "[Staff] " << name << " continues regular maintenance of "
                  << p->getName() << std::endl;
    }
}
