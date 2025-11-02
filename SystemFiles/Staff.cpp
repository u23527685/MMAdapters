#include "Staff.h"
#include "SalesFloorObserver.h"
#include <iomanip>

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
    PlantInventory* inventory = PlantInventory::getInstance();
        if (!inventory) {
            std::cout << "Error: Inventory not initialized.\n";
            return;
        }
        auto inventoryItems = inventory->getInventoryView();
        if (inventoryItems.empty()) {
            std::cout << "\n=============== SALES FLOOR INVENTORY ===============\n";
            std::cout << "No plants currently available on sales floor.\n";
            std::cout <<  "====================================================\n";
            return;
        }
        std::cout << "\n=============== SALES FLOOR INVENTORY ===============\n";
        int totalCount = 0;
        double totalValue = 0.0;
        std::cout << std::left << "----------------------------------------------------\n";
        for (const auto& item : inventoryItems) {
            if (item.first && item.second > 0) { // Check for valid Plant* and quantity
                int quantity = item.second;
                double itemValue = item.first->getPrice() * quantity;
                totalCount += quantity;
                totalValue += itemValue;
                std::cout << item.first->getDescription() << "\n";
                std::cout << "   Price: R" << std::fixed << std::setprecision(2) << item.first->getPrice()
                          << " | Quantity: " << quantity << " | Subtotal: R" << itemValue << "\n";
                std::cout << "----------------------------------------------------\n";
            }
        }
        std::cout << "SUMMARY:\n";
        std::cout << "   Total Plant Types: " << inventoryItems.size() << "\n";
        std::cout << "   Total Plants: " << totalCount << "\n";
        std::cout << "   Inventory Value: R" << std::fixed << std::setprecision(2) << totalValue << "\n";
        std::cout << "====================================================\n";
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

    std::unique_ptr<PlantCareRoutine> careRoutine = PlantCareRoutine::PlantCare(plant);

    if (!p->updatePlant()) {
        std::cout << "[Staff] " << name << " is applying care..." << std::endl;
        p->getStateObj()->applyCare(p, plant, careRoutine.get());
    } else {
        std::cout << "[Staff] " << name << " continues regular maintenance of "
                  << p->getName() << std::endl;
    }
}
