#include "SalesFloorObserver.h"
#include "PlantInventory.h"
#include <iostream>

SalesFloorObserver::SalesFloorObserver(Staff* staff) 
    : salesStaff(staff) {
    if (staff != nullptr) {
        observerName = staff->getName();
    } else {
        observerName = "Unassigned Sales Floor Observer";
    }
}

SalesFloorObserver::SalesFloorObserver(const std::string& name) 
    : salesStaff(nullptr), observerName(name) {
}

SalesFloorObserver::~SalesFloorObserver() {
}

void SalesFloorObserver::update(PlantInventory* inventory, const std::string& plantType, int quantity) {
    std::cout << "[" << observerName << "] Sales floor notification received:" << std::endl;
    std::cout << "Plant Type: " << plantType << std::endl;
    std::cout << "Greenhouse Change: " << (quantity > 0 ? "+" : "") << quantity << std::endl;
    std::cout << "Total in Greenhouse: " << inventory->getQuantity(plantType) << std::endl;
    
    if (quantity > 0) {
        std::cout << "Action: New plants ready from greenhouse!" << std::endl;
        int moveToFloor = (quantity > 10) ? 10 : (quantity / 2);
        if (moveToFloor > 0) {
            updateSalesFloorDisplay(plantType, moveToFloor);
            std::cout << "Moving " << moveToFloor << " " << plantType << "(s) to sales floor display." << std::endl;
        }
        
        if (salesStaff != nullptr) {
            std::cout << "Sales staff " << salesStaff->getName() << " will arrange the new display." << std::endl;
        }
    } else if (quantity < 0) {
        std::cout << "Action: Plants removed from greenhouse inventory." << std::endl;
        std::cout << "Current sales floor has " << getSalesFloorStock(plantType) << " " << plantType << "(s) on display." << std::endl;

        int remainingInGreenhouse = inventory->getQuantity(plantType);
        int onFloor = getSalesFloorStock(plantType);
        
        if (onFloor < 3 && remainingInGreenhouse > 0) {
            int needToRestock = 5 - onFloor;
            int canRestock = (needToRestock > remainingInGreenhouse) ? remainingInGreenhouse : needToRestock;
            
            if (canRestock > 0) {
                updateSalesFloorDisplay(plantType, canRestock);
                std::cout << "Restocking " << canRestock << " more " << plantType << "(s) to sales floor." << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

std::string SalesFloorObserver::getObserverName() const {
    return observerName;
}

Staff* SalesFloorObserver::getSalesStaff() const {
    return salesStaff;
}

void SalesFloorObserver::updateSalesFloorDisplay(const std::string& plantType, int quantity) {
    salesFloorStock[plantType] += quantity;
    
    if (salesFloorStock[plantType] < 0) {
        salesFloorStock[plantType] = 0;
    }
    
    std::cout << "Sales floor updated: " << plantType << " display now has " << salesFloorStock[plantType] << " units." << std::endl;
}

int SalesFloorObserver::getSalesFloorStock(const std::string& plantType) const {
    auto it = salesFloorStock.find(plantType);
    if (it != salesFloorStock.end()) {
        return it->second;
    }
    return 0;
}

void SalesFloorObserver::displaySalesFloor() const {
    std::cout << "\nSales Floor Display:" << std::endl;
    if (salesFloorStock.empty()) {
        std::cout << "Sales floor is empty." << std::endl;
    } else {
        for (const auto& item : salesFloorStock) {
            std::cout << item.first << ": " << item.second << " on display" << std::endl;
        }
    }
}
