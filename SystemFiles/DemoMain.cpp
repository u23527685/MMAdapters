#include "PlantInventory.h"
#include "InventoryObserver.h"
#include "SalesFloorObserver.h"
#include "Plant.h"
#include "Rose.h"
#include "Oak.h"
#include "FloorEmployee.h"
#include "PlantLifeCycle.h"
#include "SeedState.h"
#include "DistressedState.h"
#include "WitheredState.h"
#include "PlantCareRoutine.h"


#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

#include "FullSunStrategy.h"
#include "HighWaterStrategy.h"
#include "InorganicFertilizer.h"
#include "LowWaterStrategy.h"
#include "OrganicFertilizer.h"
#include "ShadeStrategy.h"

#include "AskQuery.h"
#include "Staff.h"
#include"FloorEmployee.h"
#include"FloorManager.h"
#include"SalesEmployee.h"
#include"SalesManager.h"

#include <vector>
#include "Transaction.h"
#include "TransactionHistory.h"
#include "CreditCardPaymentStrategy.h"
#include "EWalletPaymentStrategy.h"
#include "EFTPaymentStrategy.h"
#include "BasePlant.h"
#include "GiftWrap.h"
#include "DecorativePot.h"
#include "SpecialArrangement.h"
#include "Customer.h"
#include "Order.h"
#include "Staff.h"

#include "Plant.h"
#include "PlantLifeCycle.h"
#include "SeedState.h"
#include "PlantCareRoutine.h"

#include <cstdlib>
#include <ctime>
#include <map>
#include <string>

void displayMenu() {
    std::cout << "\n=== Plant Nursery Simulator ===\n";
    std::cout << "1. Buy Plants\n";
    std::cout << "2. Hire Staff\n";
    std::cout << "3. Simulate Day\n";
    std::cout << "4. View Status\n";
    std::cout << "5. Quit\n";
    std::cout << "Enter choice: ";
}

void displayPlantBuyOptions() {
    std::cout << "\nAvailable Plants to Buy:\n";
    std::cout << "1. Red Rose - $10 each\n";
    std::cout << "2. Yellow Rose - $9 each\n";
    std::cout << "3. Alien Plant - $500 each\n";
    std::cout << "4. Oak Tree - $6 each\n";
    std::cout << "5. Maple Tree - $7 each\n";
    std::cout << "Enter plant number (0 to cancel): ";
}

void displayHireOptions() {
    std::cout << "\nAvailable Staff to Hire:\n";
    std::cout << "1. Floor Employee - $200\n";
    std::cout << "2. Floor Manager - $400\n";
    std::cout << "3. Sales Employee - $300\n";
    std::cout << "4. Sales Manager - $500\n";
    std::cout << "Enter staff number (0 to cancel): ";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    
    PlantInventory* inventory = PlantInventory::getInstance();
    SalesFloorObserver* salesFloor = new SalesFloorObserver(inventory);

    
    Rose* redRose = new Rose(9.99, "Beautiful Red Rose");
    redRose->setCategory("Sunny");
    redRose->setMaxWater(100);
    redRose->setMaxSunlight(100);
    redRose->setMaxNutrients(100);
    Rose* yellowRose = new Rose(8.99, "Bright Yellow Rose");
    yellowRose->setCategory("Sunny");
    yellowRose->setMaxWater(100);
    yellowRose->setMaxSunlight(100);
    yellowRose->setMaxNutrients(100);
    Plant* alienPlant = new Plant(499.99, "Mysterious Alien Plant");
    alienPlant->setCategory("Tropical");
    alienPlant->setMaxWater(100);
    alienPlant->setMaxSunlight(100);
    alienPlant->setMaxNutrients(100);
    Oak* oak = new Oak(5.99, "Majestic Oak Tree");
    oak->setCategory("Temperate");
    oak->setMaxWater(100);
    oak->setMaxSunlight(100);
    oak->setMaxNutrients(100);
    Oak* maple = new Oak(6.99, "Vibrant Maple Tree");
    maple->setCategory("Temperate");
    maple->setMaxWater(100);
    maple->setMaxSunlight(100);
    maple->setMaxNutrients(100);

    std::map<int, std::pair<Plant*, double>> plantOptions = {
        {1, {redRose, 10.0}},
        {2, {yellowRose, 9.0}},
        {3, {alienPlant, 500.0}},
        {4, {oak, 6.0}},
        {5, {maple, 7.0}}
    };

    
    double money = 1000.0;
    std::vector<Staff*> hiredStaff;
    std::map<Plant*, PlantLifeCycle*> lifecycles;
    FloorEmployee* floorEmployee = nullptr;
    FloorManager* floorManager = nullptr;
    SalesEmployee* salesEmployee = nullptr;
    SalesManager* salesManager = nullptr;

    
    CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
    EWalletPaymentStrategy ewallet("wallet123");
    EFTPaymentStrategy eft("9876543210");

    
    AskQuery askQuery;

    bool running = true;
    while (running) {
        displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: { 
                displayPlantBuyOptions();
                int plantChoice;
                std::cin >> plantChoice;
                if (plantChoice == 0) break;
                if (plantOptions.find(plantChoice) == plantOptions.end()) {
                    std::cout << "Invalid choice.\n";
                    break;
                }
                Plant* plant = plantOptions[plantChoice].first;
                double buyPrice = plantOptions[plantChoice].second;
                std::cout << "Enter quantity: \n";
                int qty;
                std::cin >> qty;
                if (qty <= 0) break;
                double cost = buyPrice * qty;
                if (money < cost) {
                    std::cout << "Not enough money! (" << money << ") Cost: $" << cost << "\n";
                    break;
                }
                money -= cost;
                inventory->addStock(plant, qty);
                std::cout << "Bought " << qty << " " << plant->getDescription() << "(s).\n";


                if (lifecycles.find(plant) == lifecycles.end()) {
                    PlantLifeCycle* cycle = new PlantLifeCycle(plant, new SeedState(), plant->getDescription() + " Cycle");
                    lifecycles[plant] = cycle;
                    plant->setCurrentWater(plant->getMaxWater());
                    plant->setCurrentSunlight(plant->getMaxSunlight());
                    plant->setCurrentNutrients(plant->getMaxNutrients());
                    for (auto staff : hiredStaff) {
                        cycle->attach(staff);
                    }
                }
                break;
            }
            case 2: { 
                displayHireOptions();
                int staffChoice;
                std::cin >> staffChoice;
                if (staffChoice == 0) break;
                Staff* newStaff = nullptr;
                double hireCost = 0.0;
                std::string name = "Staff" + std::to_string(hiredStaff.size() + 1);
                switch (staffChoice) {
                    case 1:
                        if (floorEmployee) {
                            std::cout << "Already hired a Floor Employee.\n";
                            continue;
                        }
                        floorEmployee = new FloorEmployee(name);
                        newStaff = floorEmployee;
                        hireCost = 200.0;
                        break;
                    case 2:
                        if (floorManager) {
                            std::cout << "Already hired a Floor Manager.\n";
                            continue;
                        }
                        floorManager = new FloorManager(name);
                        newStaff = floorManager;
                        hireCost = 400.0;
                        break;
                    case 3:
                        if (salesEmployee) {
                            std::cout << "Already hired a Sales Employee. ("<< name << "\n";
                            continue;
                        }
                        salesEmployee = new SalesEmployee(name);
                        newStaff = salesEmployee;
                        hireCost = 300.0;
                        break;
                    case 4:
                        if (salesManager) {
                            std::cout << "Already hired a Sales Manager.\n";
                            continue;
                        }
                        salesManager = new SalesManager(name);
                        newStaff = salesManager;
                        hireCost = 500.0;
                        break;
                    default:
                        std::cout << "Invalid choice.\n";
                        continue;
                }
                if (money < hireCost) {
                    std::cout << "Not enough money! Cost: $" << hireCost << "\n";
                    delete newStaff;
                    continue;
                }
                money -= hireCost;
                hiredStaff.push_back(newStaff);
                salesFloor->attachStaff(newStaff);
                for (auto& pair : lifecycles) {
                    pair.second->attach(newStaff);
                }
                std::cout << "Hired " << newStaff->getName() << ".\n";

                
                Staff* chainStart = nullptr;

                if (floorEmployee) {
                    chainStart = floorEmployee;
                    Staff* nxt = nullptr;
                    if (floorManager)      nxt = floorManager;
                    else if (salesEmployee) nxt = salesEmployee;
                    else if (salesManager)  nxt = salesManager;
                    floorEmployee->setNext(nxt);
                }

                if (floorManager) {
                    if (!chainStart) chainStart = floorManager;
                    Staff* nxt = nullptr;
                    if (salesEmployee) nxt = salesEmployee;
                    else if (salesManager) nxt = salesManager;
                    floorManager->setNext(nxt);
                }

                if (salesEmployee) {
                    if (!chainStart) chainStart = salesEmployee;
                    salesEmployee->setNext(salesManager ? static_cast<Staff*>(salesManager) : nullptr);
                }

                if (salesManager) {
                    if (!chainStart) chainStart = salesManager;
                    salesManager->setNext(nullptr);
                }

                std::cout << "Hired " << newStaff->getName() << ".\n";
                break;
            }
            case 3: { 
                std::cout << "\nSimulating a day...\n";

                
                for (auto& pair : lifecycles) {
                    Plant* p = pair.first;
                    PlantLifeCycle* cycle = pair.second;
                    double decay = rand() % 20 + 10.0;
                    p->setCurrentWater(std::max(0.0, p->getCurrentWater() - decay));
                    p->setCurrentSunlight(std::max(0.0, p->getCurrentSunlight() - decay));
                    p->setCurrentNutrients(std::max(0.0, p->getCurrentNutrients() - decay));
                    cycle->updatePlant();
                }

                
                int numCustomers = rand() % 5 + 1;
                std::cout << numCustomers << " customers visited today.\n";
                Staff* chainStart = floorEmployee ? static_cast<Staff*>(floorEmployee) :
                    floorManager ? static_cast<Staff*>(floorManager) :
                    salesEmployee ? static_cast<Staff*>(salesEmployee) :
                    salesManager ? static_cast<Staff*>(salesManager) : nullptr;

                for (int i = 0; i < numCustomers; ++i) {
                    Customer customer("Customer" + std::to_string(i + 1));
                    int action = rand() % 2; 
                    if (action == 0) {
                        if (!chainStart) {
                            std::cout << customer.getName() << " asked a query but no staff available.\n";
                            continue;
                        }
                        
                        int queryType = rand() % 3;
                        Query* q = nullptr;
                        if (!lifecycles.empty()) {
                            
                            auto it = lifecycles.begin();
                            std::advance(it, rand() % lifecycles.size());
                            Plant* randPlant = it->first;
                            if (queryType == 0) {
                                q = askQuery.careRoutine(randPlant);
                                std::cout << customer.getName() << " asking about care routine.\n";
                            } else if (queryType == 1) {
                                q = askQuery.describe(randPlant);
                                std::cout << customer.getName() << " asking about description.\n";
                            } else {
                                q = askQuery.stockInfo();
                                std::cout << customer.getName() << " asking about stock info.\n";
                            }
                        } else {
                            q = askQuery.stockInfo();
                            std::cout << customer.getName() << " asking about stock info.\n";
                        }
                        chainStart->handleQuery(q);
                        delete q;
                    } else {
                        
                        if (lifecycles.empty()) {
                            std::cout << customer.getName() << " wanted to buy but no plants available.\n";
                            continue;
                        }

                        auto it = lifecycles.begin();
                        std::advance(it, rand() % lifecycles.size());
                        Plant* buyPlant = it->first;
                        PlantLifeCycle* cycle = it->second;
                        std::string state = cycle->getState();
                        if (state == "Withered" || state == "Distressed") {
                            std::cout << customer.getName() << " didn't buy " << buyPlant->getDescription() << " because it's " << state << ".\n";
                            continue;
                        }
                        int buyQty = rand() % 3 + 1;
                        int available = salesFloor->getPlantQuantity(buyPlant);
                        if (available < buyQty) {
                            std::cout << customer.getName() << " wanted " << buyQty << " but only " << available << " available.\n";
                            buyQty = available;
                        }
                        if (buyQty == 0) continue;

                        
                        Plant* decorated = new BasePlant(buyPlant->getPrice(), buyPlant->getDescription());
                        int deco = rand() % 4; 
                        if (deco == 0) {
                            decorated = new GiftWrap(decorated);
                        } else if (deco == 1) {
                            decorated = new DecorativePot(decorated);
                        } else if (deco == 2) {
                            decorated = new SpecialArrangement(decorated);
                        }

                        double totalPrice = decorated->getPrice() * buyQty;
                        Order order(&customer, "ORD-" + std::to_string(rand()));
                        Transaction* tx = new Transaction(order.getOrderId(), totalPrice, buyQty);
                        int payType = rand() % 3;
                        if (payType == 0) tx->setPaymentStrategy(&creditCard);
                        else if (payType == 1) tx->setPaymentStrategy(&ewallet);
                        else tx->setPaymentStrategy(&eft);
                        order.addTransaction(tx);
                        order.processOrder();

                        inventory->removeStock(buyPlant, buyQty);
                        money += totalPrice;
                        std::cout << customer.getName() << " bought " << buyQty << " " << decorated->getDescription() << " for $" << totalPrice << ".\n";

                        customer.placeOrder(order);
                        delete decorated;
                    }
                }
                break;
            }
            case 4: { 
                std::cout << "\nCurrent Money: $" << std::fixed << std::setprecision(2) << money << "\n";
                std::cout << "Hired Staff:\n";
                for (auto staff : hiredStaff) {
                    std::cout << "- " << staff->getName() << "\n";
                }
                std::cout << "Inventory:\n";
                salesFloor->displayAvailablePlants();
                std::cout << "Plant States:\n";
                for (auto& pair : lifecycles) {
                    Plant* p = pair.first;
                    PlantLifeCycle* cycle = pair.second;
                    std::cout << p->getDescription() << ":\n";
                    std::cout << "  State: " << cycle->getState() << "\n";
                    std::cout << "  Water: " << p->getCurrentWater() << "/" << p->getMaxWater() << "\n";
                    std::cout << "  Sunlight: " << p->getCurrentSunlight() << "/" << p->getMaxSunlight() << "\n";
                    std::cout << "  Nutrients: " << p->getCurrentNutrients() << "/" << p->getMaxNutrients() << "\n";
                }
                break;
            }
            case 5: 
                running = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }

    delete salesFloor;
    for (auto staff : hiredStaff) {
        delete staff;
    }
    for (auto& pair : lifecycles) {
        delete pair.second;
    }
    delete redRose;
    delete yellowRose;
    delete alienPlant;
    delete oak;
    delete maple;

    std::cout << "Game ended.\n";
    return 0;
}