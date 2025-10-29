#include "Staff.h"
#include <iostream>

Staff::Staff() : staffName("Unnamed Staff"), role("General") {
  this->name = "Unnamed Staff"; // update to resolve merge conflicts
  next=nullptr;// update to resolve merge conflicts
}

Staff::Staff(const std::string& name, const std::string& role)
    : staffName(name), role(role) {
      this->name = name; // update to resolve merge conflicts
      next=nullptr;// update to resolve merge conflicts
    }

std::string Staff::getName() const {
    return staffName;
}

std::string Staff::getRole() const {
    return role;
}

void Staff::setName(const std::string& name) {
    staffName = name;
}

void Staff::setRole(const std::string& newRole) {
    role = newRole;
}

void Staff::respondToQuery(const std::string& queryMessage) const {
    std::cout << "[Staff: " << staffName << "] Received customer query: \""
              << queryMessage << "\"\n";
    std::cout << "Response: We'll review your request and get back to you shortly.\n";
}

void Staff::checkOrderStatus(const Order& order) const {
    std::cout << "[Staff: " << staffName << "] Checking status for Order ID: "
              << order.getOrderId() << std::endl;
    std::cout << "Current status: " << order.getStatus() << "\n";
}
#include "Staff.h"

Staff::Staff(std::string name){
    this->name=name;
    next=nullptr;
  
    this->staffName = name;// update to resolve merge conflicts
    this->role = "General";// update to resolve merge conflicts
}

Staff::~Staff(){}

/* this is commented out to resolve merge conflicts
std::string Staff::getName(){
    return name;
}
*/

void Staff::setNext(Staff* staff){
    next=staff;
}

Staff* Staff::getNext(){
    return next;
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
**/

void Staff::update(PlantLifeCycle* p) {
    Plant* plant = p->getPlant();
    std::string stateName = p->getState();

    std::cout << "[Staff] " << name << " noticed " << p->getName() << " is now in state: " << stateName << std::endl;

    careRoutine = careRoutine->PlantCare(plant);

   if (!p->isHealthy()) {
        std::cout << "[Staff] " << name << " is applying care..." << std::endl;
        p->getStateObj()->applyCare(p, plant, careRoutine);
    } else {
        std::cout << "[Staff] " << name << " continues regular maintenance of "
                  << p->getName() << std::endl;
    }
}
