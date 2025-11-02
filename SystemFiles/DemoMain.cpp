#include "PlantInventory.h"
#include "InventoryObserver.h"
#include "SalesFloorObserver.h"
#include "Plant.h"
#include "Rose.h"
#include "Oak.h"
#include "FloorEmployee.h"
#include "FloorManager.h"
#include "SalesEmployee.h"
#include "SalesManager.h"
#include "PlantLifeCycle.h"
#include "SeedState.h"
#include "DistressedState.h"
#include "WitheredState.h"
#include "Transaction.h"
#include "TransactionHistory.h"
#include "CreditCardPaymentStrategy.h"
#include "EWalletPaymentStrategy.h"
#include "EFTPaymentStrategy.h"
#include "Customer.h"
#include "Order.h"
#include "BasePlant.h"
#include "GiftWrap.h"
#include "DecorativePot.h"
#include "SpecialArrangement.h"
#include "MatureState.h"

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <limits>


// Factory function returning unique_ptr
std::unique_ptr<Plant> createSeedPlant(int option) {
    std::unique_ptr<Plant> p;

    if (option == 1) {
        p = std::make_unique<Rose>(10.0, "Red Rose");
        p->setCategory("Sunny");
    } else if (option == 2) {
        p = std::make_unique<Rose>(9.0, "Yellow Rose");
        p->setCategory("Shade");
    } else if (option == 3) {
        p = std::make_unique<Oak>(7.0, "Oak Tree");
        p->setCategory("Temperate");
    }

    if (p) p->setState(std::make_unique<SeedState>());
    return p;
}

// Simulate a day for plants

void simulateDay(std::vector<std::unique_ptr<Plant>>& growingPlants,
                 PlantInventory* inventory, std::vector<Staff*>& staff) {
    std::cout << "\n📅 --- Simulating a New Day in the Nursery ---\n";

    int watered = 0, fertilized = 0, matured = 0, died = 0;

    for (size_t i = 0; i < growingPlants.size(); ) {
        Plant* plant = growingPlants[i].get();
        if (!plant->getState()) {
            std::cout << "Error: Plant " << plant->getName() << " has no state!\n";
            growingPlants.erase(growingPlants.begin() + i);
            died++;
            continue;
        }

        // Initialize PlantLifeCycle with a cloned copy of the plant's current state
        PlantLifeCycle cycle(plant, std::unique_ptr<PlantState>(plant->getState()->clone()), plant->getName());

        // Attach staff
        for (auto* s : staff) {
            if (auto* floor = dynamic_cast<FloorStaff*>(s)) {
                cycle.attach(floor);
            }
        }

        auto routine = PlantCareRoutine::PlantCare(plant);
        if (!routine) {
            std::cout << "Error: No care routine for " << plant->getName() << "\n";
            growingPlants.erase(growingPlants.begin() + i);
            died++;
            continue;
        }

        // Apply care, simulate time, and evaluate state
        cycle.getStateObj()->applyCare(&cycle, plant, routine.get());
        cycle.simulateTimePassing();
        bool stateChanged = cycle.updatePlant(); // Evaluate state transitions

        // Transfer the updated state to the plant
        std::unique_ptr<PlantState> newState = cycle.releaseState();
        if (!newState) {
            std::cout << "Error: Plant " << plant->getName() << " state became null after update!\n";
            growingPlants.erase(growingPlants.begin() + i);
            died++;
            continue;
        }
        plant->setState(std::move(newState));

        // Check the plant's state after update
        std::string stateName = plant->getState()->getName();
        if (stateName == "Mature") {
            // Find existing plant in inventory by description
            auto& inventoryItems = inventory->getInventoryReference();
            bool found = false;
            for (auto& item : inventoryItems) {
                if (item.first->getDescription() == plant->getDescription()) {
                    item.second += 1; // Increment quantity
                    inventory->notify(); // Notify observers of stock change
                    found = true;
                    break;
                }
            }
            if (!found) {
                // If not found, create a new plant with the sale price
                std::unique_ptr<Plant> maturePlant;
                if (plant->getDescription() == "Red Rose") {
                    maturePlant = std::make_unique<Rose>(10.0, "Red Rose");
                } else if (plant->getDescription() == "Yellow Rose") {
                    maturePlant = std::make_unique<Rose>(9.0, "Yellow Rose");
                } else if (plant->getDescription() == "Oak Tree") {
                    maturePlant = std::make_unique<Oak>(7.0, "Oak Tree");
                }
                if (maturePlant) {
                    maturePlant->setCategory(plant->getCategory());
                    maturePlant->setState(std::make_unique<MatureState>());
                    inventory->addStock(maturePlant.release(), 1);
                }
            }
            growingPlants.erase(growingPlants.begin() + i);
            matured++;
            continue;
                } else if (stateName == "Withered") {
                    growingPlants.erase(growingPlants.begin() + i);
                    died++;
                    continue;
                }

        watered++;
        fertilized++;
        ++i;
    }

    std::cout << "\n✅ Daily Summary:\n";
    std::cout << "- " << watered << " watering actions\n";
    std::cout << "- " << fertilized << " fertilizer boosts\n";
    std::cout << "- " << matured << " plants matured and moved to inventory\n";
    std::cout << "- " << died << " plants withered and removed\n";
    std::cout << "\n🌱 End of day processing complete.\n";
}


int main() {
    srand(static_cast<unsigned>(time(0)));

    std::cout << "=============================================\n";
    std::cout << "🌿   Welcome to Plantopia: Terminal Edition   🌿\n";
    std::cout << "=============================================\n";

    // Core systems
    PlantInventory* inventory = PlantInventory::getInstance();
    std::unique_ptr<SalesFloorObserver> salesFloor = std::make_unique<SalesFloorObserver>(inventory);

    // Payment strategies
    CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
    EWalletPaymentStrategy ewallet("wallet123");
    EFTPaymentStrategy eft("9876543210");

    // Plants for sale (inventory display)
    auto redRose = std::make_unique<Rose>(10.0, "Red Rose");
    auto yellowRose = std::make_unique<Rose>(9.0, "Yellow Rose");
    auto oakTree = std::make_unique<Oak>(7.0, "Oak Tree");

    std::map<int, Plant*> plantOptions = {
        {1, redRose.get()}, {2, yellowRose.get()}, {3, oakTree.get()}
    };

    inventory->addStock(redRose.get(), 10);
    inventory->addStock(yellowRose.get(), 10);
    inventory->addStock(oakTree.get(), 8);

    // Memento / transactions
    std::vector<Transaction*> savedTransactions;

    // Staff and growing plants
    std::vector<Staff*> hiredStaff;
    std::vector<std::unique_ptr<Plant>> growingPlants;

    double balance = 1000.0;
    bool running = true;

    while (running) {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Staff menu\n2. Customer menu\n3. Simulate a day\n4. Exit\nSelect action: ";
        int roleChoice;
        std::cin >> roleChoice;

        if (roleChoice >= 4) break;

        // --- Staff Menu ---
        if (roleChoice == 1) {
            bool staffRunning = true;
            while (staffRunning) {
                std::cout << "\n--- Staff Menu ---\n";
                std::cout << "1. Hire Staff Member\n";
                std::cout << "2. View Hired Staff\n";
                std::cout << "3. Buy plant seeds\n";
                std::cout << "4. View nursery inventory\n";
                std::cout << "5. Back\nEnter choice: ";
                int sChoice; std::cin >> sChoice;
                if (sChoice >= 5) break;

                // Hire Staff
                if (sChoice == 1) {
                    std::cout << "Current Balance: R" << std::fixed << std::setprecision(2) << balance;
                    std::cout << "\nChoose staff type:\n1. Floor Employee (R200)\n2. Floor Manager (R400)\n3. Sales Employee (R300)\n4. Sales Manager (R500)\nEnter number: ";
                    int type; std::cin >> type;

                    Staff* newStaff = nullptr;
                    double cost = 0;
                    std::string name = "Staff_" + std::to_string(hiredStaff.size() + 1);
                    switch (type) {
                        case 1: newStaff = new FloorEmployee(name); cost = 200; break;
                        case 2: newStaff = new FloorManager(name); cost = 400; break;
                        case 3: newStaff = new SalesEmployee(name); cost = 300; break;
                        case 4: newStaff = new SalesManager(name); cost = 500; break;
                        default: std::cout << "Invalid.\n"; continue;
                    }

                    if (balance < cost) {
                        std::cout << "\nNot enough funds!\n";
                        delete newStaff;
                    } else {
                        hiredStaff.push_back(newStaff);
                        balance -= cost;
                        std::cout << "✅ Hired " << newStaff->getName() << " successfully!\n";
                    }
                }

                // View Staff
                else if (sChoice == 2) {
                    std::cout << "\n--- Hired Staff ---\n";
                    if (hiredStaff.empty()) std::cout << "None yet.\n";
                    else for (auto s : hiredStaff) std::cout << "- " << s->getName() << "\n";
                }

                // Buy seeds
                else if (sChoice == 3) {
                    std::cout << "\nAvailable seeds to buy:\n1. Red rose seed (R3.00)\n2. Yellow rose seed(R2.50)\n3. Oak tree seed(R1.50)\n4. Return to staff menu\n";
                    int type; std::cin >> type;
                    if (type == 4) continue;
                    if (type < 1 || type > 3) continue;

                    std::cout << "\nEnter quantity to buy: ";
                    int qty; std::cin >> qty;
                    if (qty <= 0) { std::cout << "Invalid quantity\n"; continue; }

                    double costPerSeed = (type == 1 ? 3 : (type == 2 ? 2.50 : 1.50));
                    double totalCost = costPerSeed * qty;
                    if (balance < totalCost) { std::cout << "❌ Not enough balance.\n"; continue; }

                    for (int i = 0; i < qty; ++i) {
                        growingPlants.push_back(createSeedPlant(type));
                    }

                    std::cout << "✅ Purchased " << qty << " seeds and added to nursery.(for R" << totalCost << ")\n";
                    balance -= totalCost;
                    std::cout << "Current Balance: R" << std::fixed << std::setprecision(2) << balance << "\n";
                }

                // View Nursery Inventory
                else if (sChoice == 4) {
                    std::cout << "\n=== Growing Nursery ===\n";
                    if (growingPlants.empty()) std::cout << "No plants currently growing.\n";
                    else for (auto& p : growingPlants) {
                                std::cout << "- " << p->getDescription();
                                if (p->getState())
                                    std::cout << " | State: " << p->getState()->getName();
                                else
                                    std::cout << " | State: None";

                                std::cout << " | Category: " << p->getCategory()
                                        << " | Water: " << p->getCurrentWater() << "/" << p->getMaxWater()
                                        << " | Sunlight: " << p->getCurrentSunlight() << "/" << p->getMaxSunlight()
                                        << " | Nutrients: " << p->getCurrentNutrients() << "/" << p->getMaxNutrients()
                                        << " | Growth: " << p->getGrowthProgress() << "\n";
                    }


                    std::cout << "\nPlants available for sale:\n";
                    for (auto& [num, p] : plantOptions)
                        std::cout << num << ". " << p->getDescription() << " - R" << p->getPrice()
                                  << " (Qty: " << inventory->getQuantity(p) << ")\n";
                }
            }
        }

        // --- Customer Menu ---
        else if (roleChoice == 2) {
            Customer customer("Walk-in Customer");
            bool custRunning = true;
            while (custRunning) {
                std::cout << "\n--- Customer Menu ---\n"
                        << "1. View Inventory\n"
                        << "2. Buy Plant\n"
                        << "3. Repurchase Last Order (Memento)\n"
                        << "4. View Receipt\n"
                        << "5. Back\n"
                        << "Choose: ";
                        int cChoice;
                        while (true) {
                            std::cin >> cChoice;
                            if (std::cin.fail()) {
                                std::cin.clear(); // clear error flags
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
                                std::cout << "Invalid input. Please enter a number: ";
                                continue;
                            }
                            break;
                        }

                        if (cChoice == 5) break;


                if (cChoice == 1) {
                    std::cout << "\n🌿 Available Plants 🌿\n";
                    for (auto& [num, p] : plantOptions) {
                        if (!p) continue; // ✅ skip null
                        int qty = inventory->getQuantity(p);
                        if (qty > 0)
                            std::cout << num << ". " << p->getDescription() << " - R" << p->getPrice()
                                    << " (Qty: " << qty << ")\n";
                        else
                            std::cout << num << ". " << p->getDescription() << " - ❌ Out of stock!\n";
                    }
                }


                else if (cChoice == 2) {
                    std::cout << "\nSelect plant to buy (0 to cancel): ";
                    int choice; std::cin >> choice;
                    if (choice == 0 || plantOptions.find(choice) == plantOptions.end()) continue;

                    Plant* plant = plantOptions[choice];
                    int available = inventory->getQuantity(plant);
                    if (available <= 0) { std::cout << "❌ Out of stock!\n"; continue; }

                    std::cout << "\nEnter quantity (max " << available << "): ";
                    int qty; std::cin >> qty;
                    if (qty <= 0 || qty > available) continue;

                    // Decorate plant
                    Plant* decorated = new BasePlant(plant->getPrice(), plant->getDescription());
                    bool addingDecor = true;
                    while (addingDecor) {
                        std::cout << "\nAdd decoration?\n"
                                << "1. Gift Wrap (+R5)\n"
                                << "2. Decorative Pot (+R7)\n"
                                << "3. Special Arrangement (+R10)\n"
                                << "4. Done\n"
                                << "Choose: ";
                        int decoChoice; std::cin >> decoChoice;
                        switch (decoChoice) {
                            case 1: decorated = new GiftWrap(decorated); std::cout << "🎁 Added Gift Wrap\n"; break;
                            case 2: decorated = new DecorativePot(decorated); std::cout << "🪴 Added Decorative Pot\n"; break;
                            case 3: decorated = new SpecialArrangement(decorated); std::cout << "💐 Added Special Arrangement\n"; break;
                            default: addingDecor = false; break;
                        }
                    }

                    // Payment
                    std::cout << "\nSelect payment method:\n1. Credit Card\n2. E-Wallet\n3. EFT\nChoose: ";
                    int pay; std::cin >> pay;
                    PaymentStrategy* strategy = nullptr;
                    if (pay == 1) strategy = &creditCard;
                    else if (pay == 2) strategy = &ewallet;
                    else strategy = &eft;

                    double total = decorated->getPrice() * qty;
                    Order order(&customer, "ORD-" + std::to_string(rand()));
                    Transaction* tx = new Transaction(order.getOrderId(), total, qty);
                    tx->setPaymentStrategy(strategy);
                    order.addTransaction(tx);
                    order.processOrder();

                    savedTransactions.push_back(tx);
                    inventory->removeStock(plant, qty);

                    // ✅ Print a neat receipt
                    std::cout << "\n=========================================\n";
                    std::cout << "             🧾 PURCHASE RECEIPT\n";
                    std::cout << "=========================================\n";
                    std::cout << "Order ID: " << order.getOrderId() << "\n";
                    std::cout << "Customer: " << customer.getName() << "\n";
                    std::cout << "Item: " << decorated->getDescription() << "\n";
                    std::cout << "Quantity: " << qty << "\n";
                    std::cout << "Payment Method: ";
                    if (pay == 1) std::cout << "Credit Card\n";
                    else if (pay == 2) std::cout << "E-Wallet\n";
                    else std::cout << "EFT\n";
                    std::cout << "-----------------------------------------\n";
                    std::cout << std::fixed << std::setprecision(2)
                            << "Total: R" << total << "\n";
                    std::cout << "=========================================\n";
                    std::cout << "     🌸 Thank you for shopping! 🌸\n";
                    std::cout << "=========================================\n";

                    delete decorated;
                }

                else if (cChoice == 3) {
                    if (savedTransactions.empty()) { std::cout << "\nNo previous orders found!\n"; continue; }
                    Transaction* last = savedTransactions.back()->clone();
                    std::cout << "\n🔁 Re-purchasing last order...\n";
                    last->processPayment();
                    savedTransactions.push_back(last);
                    std::cout << "✅ Order repeated successfully!\n";
                }

                else if (cChoice == 4) {
                    if (savedTransactions.empty()) { std::cout << "\nNo receipts to view yet.\n"; continue; }

                    Transaction* last = savedTransactions.back();
                    std::cout << "\n=========================================\n";
                    std::cout << "           📄 LAST PURCHASE RECEIPT\n";
                    std::cout << "=========================================\n";
                    std::cout << "Transaction ID: " << last->getTransactionId() << "\n";
                    std::cout << "Quantity: " << last->getQuantity() << "\n";
                    std::cout << std::fixed << std::setprecision(2)
                            << "Total Paid: R" << last->getAmount() << "\n";
                    std::cout << "=========================================\n";
                    std::cout << "      🌿 Come again soon! 🌿\n";
                    std::cout << "=========================================\n";
                }
            }
        }


        // --- Simulate Day ---
        else if (roleChoice == 3) {
            std::cout << "\n--- Simulating a Day at Plantopia ---\n";
            simulateDay(growingPlants, inventory, hiredStaff);
        }
    }

    // Cleanup
    for (auto s : hiredStaff) delete s;

    std::cout << "\n🌱 Thank you for visiting Plantopia! 🌱\n";
    return 0;
}



// JAYS CODE Below

/* Jerusha - I used your code as well as asked chat to do some validation i still need
to simulate the plant part of it and how it gets cared by the employees also the code looks good
Thank you so much!!! I did not want to mess or change something so its commented but i did use it above*/

// #include "PlantInventory.h"
// #include "InventoryObserver.h"
// #include "SalesFloorObserver.h"
// #include "Plant.h"
// #include "Rose.h"
// #include "Oak.h"
// #include "FloorEmployee.h"
// #include "PlantLifeCycle.h"
// #include "SeedState.h"
// #include "DistressedState.h"
// #include "WitheredState.h"
// #include "PlantCareRoutine.h"


// #include <iostream>
// #include <thread>
// #include <chrono>
// #include <iomanip>

// #include "FullSunStrategy.h"
// #include "HighWaterStrategy.h"
// #include "InorganicFertilizer.h"
// #include "LowWaterStrategy.h"
// #include "OrganicFertilizer.h"
// #include "ShadeStrategy.h"

// #include "AskQuery.h"
// #include "Staff.h"
// #include"FloorEmployee.h"
// #include"FloorManager.h"
// #include"SalesEmployee.h"
// #include"SalesManager.h"

// #include <vector>
// #include "Transaction.h"
// #include "TransactionHistory.h"
// #include "CreditCardPaymentStrategy.h"
// #include "EWalletPaymentStrategy.h"
// #include "EFTPaymentStrategy.h"
// #include "BasePlant.h"
// #include "GiftWrap.h"
// #include "DecorativePot.h"
// #include "SpecialArrangement.h"
// #include "Customer.h"
// #include "Order.h"
// #include "Staff.h"

// #include "Plant.h"
// #include "PlantLifeCycle.h"
// #include "SeedState.h"
// #include "PlantCareRoutine.h"

// #include <cstdlib>
// #include <ctime>
// #include <map>
// #include <string>

// void displayMenu() {
//     std::cout << "\n=== Plant Nursery Simulator ===\n";
//     std::cout << "1. Buy Plants\n";
//     std::cout << "2. Hire Staff\n";
//     std::cout << "3. Simulate Day\n";
//     std::cout << "4. View Status\n";
//     std::cout << "5. Quit\n";
//     std::cout << "Enter choice: ";
// }

// void displayPlantBuyOptions() {
//     std::cout << "\nAvailable Plants to Buy:\n";
//     std::cout << "1. Red Rose - $10 each\n";
//     std::cout << "2. Yellow Rose - $9 each\n";
//     std::cout << "3. Alien Plant - $500 each\n";
//     std::cout << "4. Oak Tree - $6 each\n";
//     std::cout << "5. Maple Tree - $7 each\n";
//     std::cout << "Enter plant number (0 to cancel): ";
// }

// void displayHireOptions() {
//     std::cout << "\nAvailable Staff to Hire:\n";
//     std::cout << "1. Floor Employee - $200\n";
//     std::cout << "2. Floor Manager - $400\n";
//     std::cout << "3. Sales Employee - $300\n";
//     std::cout << "4. Sales Manager - $500\n";
//     std::cout << "Enter staff number (0 to cancel): ";
// }

// int main() {
//     srand(static_cast<unsigned>(time(0)));

    
//     PlantInventory* inventory = PlantInventory::getInstance();
//     SalesFloorObserver* salesFloor = new SalesFloorObserver(inventory);

    
//     Rose* redRose = new Rose(9.99, "Beautiful Red Rose");
//     redRose->setCategory("Sunny");
//     redRose->setMaxWater(100);
//     redRose->setMaxSunlight(100);
//     redRose->setMaxNutrients(100);
//     Rose* yellowRose = new Rose(8.99, "Bright Yellow Rose");
//     yellowRose->setCategory("Sunny");
//     yellowRose->setMaxWater(100);
//     yellowRose->setMaxSunlight(100);
//     yellowRose->setMaxNutrients(100);
//     Plant* alienPlant = new Plant(499.99, "Mysterious Alien Plant");
//     alienPlant->setCategory("Tropical");
//     alienPlant->setMaxWater(100);
//     alienPlant->setMaxSunlight(100);
//     alienPlant->setMaxNutrients(100);
//     Oak* oak = new Oak(5.99, "Majestic Oak Tree");
//     oak->setCategory("Temperate");
//     oak->setMaxWater(100);
//     oak->setMaxSunlight(100);
//     oak->setMaxNutrients(100);
//     Oak* maple = new Oak(6.99, "Vibrant Maple Tree");
//     maple->setCategory("Temperate");
//     maple->setMaxWater(100);
//     maple->setMaxSunlight(100);
//     maple->setMaxNutrients(100);

//     std::map<int, std::pair<Plant*, double>> plantOptions = {
//         {1, {redRose, 10.0}},
//         {2, {yellowRose, 9.0}},
//         {3, {alienPlant, 500.0}},
//         {4, {oak, 6.0}},
//         {5, {maple, 7.0}}
//     };

    
//     double money = 1000.0;
//     std::vector<Staff*> hiredStaff;
//     std::map<Plant*, PlantLifeCycle*> lifecycles;
//     FloorEmployee* floorEmployee = nullptr;
//     FloorManager* floorManager = nullptr;
//     SalesEmployee* salesEmployee = nullptr;
//     SalesManager* salesManager = nullptr;

    
//     CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
//     EWalletPaymentStrategy ewallet("wallet123");
//     EFTPaymentStrategy eft("9876543210");

    
//     AskQuery askQuery;

//     bool running = true;
//     while (running) {
//         displayMenu();
//         int choice;
//         std::cin >> choice;

//         switch (choice) {
//             case 1: { 
//                 displayPlantBuyOptions();
//                 int plantChoice;
//                 std::cin >> plantChoice;
//                 if (plantChoice == 0) break;
//                 if (plantOptions.find(plantChoice) == plantOptions.end()) {
//                     std::cout << "Invalid choice.\n";
//                     break;
//                 }
//                 Plant* plant = plantOptions[plantChoice].first;
//                 double buyPrice = plantOptions[plantChoice].second;
//                 std::cout << "Enter quantity: \n";
//                 int qty;
//                 std::cin >> qty;
//                 if (qty <= 0) break;
//                 double cost = buyPrice * qty;
//                 if (money < cost) {
//                     std::cout << "Not enough money! (" << money << ") Cost: $" << cost << "\n";
//                     break;
//                 }
//                 money -= cost;
//                 inventory->addStock(plant, qty);
//                 std::cout << "Bought " << qty << " " << plant->getDescription() << "(s).\n";


//                 if (lifecycles.find(plant) == lifecycles.end()) {
//                     PlantLifeCycle* cycle = new PlantLifeCycle(plant, new SeedState(), plant->getDescription() + " Cycle");
//                     lifecycles[plant] = cycle;
//                     plant->setCurrentWater(plant->getMaxWater());
//                     plant->setCurrentSunlight(plant->getMaxSunlight());
//                     plant->setCurrentNutrients(plant->getMaxNutrients());
//                     for (auto staff : hiredStaff) {
//                         cycle->attach(staff);
//                     }
//                 }
//                 break;
//             }
//             case 2: { 
//                 displayHireOptions();
//                 int staffChoice;
//                 std::cin >> staffChoice;
//                 if (staffChoice == 0) break;
//                 Staff* newStaff = nullptr;
//                 double hireCost = 0.0;
//                 std::string name = "Staff" + std::to_string(hiredStaff.size() + 1);
//                 switch (staffChoice) {
//                     case 1:
//                         if (floorEmployee) {
//                             std::cout << "Already hired a Floor Employee.\n";
//                             continue;
//                         }
//                         floorEmployee = new FloorEmployee(name);
//                         newStaff = floorEmployee;
//                         hireCost = 200.0;
//                         break;
//                     case 2:
//                         if (floorManager) {
//                             std::cout << "Already hired a Floor Manager.\n";
//                             continue;
//                         }
//                         floorManager = new FloorManager(name);
//                         newStaff = floorManager;
//                         hireCost = 400.0;
//                         break;
//                     case 3:
//                         if (salesEmployee) {
//                             std::cout << "Already hired a Sales Employee. ("<< name << "\n";
//                             continue;
//                         }
//                         salesEmployee = new SalesEmployee(name);
//                         newStaff = salesEmployee;
//                         hireCost = 300.0;
//                         break;
//                     case 4:
//                         if (salesManager) {
//                             std::cout << "Already hired a Sales Manager.\n";
//                             continue;
//                         }
//                         salesManager = new SalesManager(name);
//                         newStaff = salesManager;
//                         hireCost = 500.0;
//                         break;
//                     default:
//                         std::cout << "Invalid choice.\n";
//                         continue;
//                 }
//                 if (money < hireCost) {
//                     std::cout << "Not enough money! Cost: $" << hireCost << "\n";
//                     delete newStaff;
//                     continue;
//                 }
//                 money -= hireCost;
//                 hiredStaff.push_back(newStaff);
//                 salesFloor->attachStaff(newStaff);
//                 for (auto& pair : lifecycles) {
//                     pair.second->attach(newStaff);
//                 }
//                 std::cout << "Hired " << newStaff->getName() << ".\n";

                
//                 Staff* chainStart = nullptr;

//                 if (floorEmployee) {
//                     chainStart = floorEmployee;
//                     Staff* nxt = nullptr;
//                     if (floorManager)      nxt = floorManager;
//                     else if (salesEmployee) nxt = salesEmployee;
//                     else if (salesManager)  nxt = salesManager;
//                     floorEmployee->setNext(nxt);
//                 }

//                 if (floorManager) {
//                     if (!chainStart) chainStart = floorManager;
//                     Staff* nxt = nullptr;
//                     if (salesEmployee) nxt = salesEmployee;
//                     else if (salesManager) nxt = salesManager;
//                     floorManager->setNext(nxt);
//                 }

//                 if (salesEmployee) {
//                     if (!chainStart) chainStart = salesEmployee;
//                     salesEmployee->setNext(salesManager ? static_cast<Staff*>(salesManager) : nullptr);
//                 }

//                 if (salesManager) {
//                     if (!chainStart) chainStart = salesManager;
//                     salesManager->setNext(nullptr);
//                 }

//                 std::cout << "Hired " << newStaff->getName() << ".\n";
//                 break;
//             }
//             case 3: { 
//                 std::cout << "\nSimulating a day...\n";

                
//                 for (auto& pair : lifecycles) {
//                     Plant* p = pair.first;
//                     PlantLifeCycle* cycle = pair.second;
//                     double decay = rand() % 20 + 10.0;
//                     p->setCurrentWater(std::max(0.0, p->getCurrentWater() - decay));
//                     p->setCurrentSunlight(std::max(0.0, p->getCurrentSunlight() - decay));
//                     p->setCurrentNutrients(std::max(0.0, p->getCurrentNutrients() - decay));
//                     cycle->updatePlant();
//                 }

                
//                 int numCustomers = rand() % 5 + 1;
//                 std::cout << numCustomers << " customers visited today.\n";
//                 Staff* chainStart = floorEmployee ? static_cast<Staff*>(floorEmployee) :
//                     floorManager ? static_cast<Staff*>(floorManager) :
//                     salesEmployee ? static_cast<Staff*>(salesEmployee) :
//                     salesManager ? static_cast<Staff*>(salesManager) : nullptr;

//                 for (int i = 0; i < numCustomers; ++i) {
//                     Customer customer("Customer" + std::to_string(i + 1));
//                     int action = rand() % 2; 
//                     if (action == 0) {
//                         if (!chainStart) {
//                             std::cout << customer.getName() << " asked a query but no staff available.\n";
//                             continue;
//                         }
                        
//                         int queryType = rand() % 3;
//                         Query* q = nullptr;
//                         if (!lifecycles.empty()) {
                            
//                             auto it = lifecycles.begin();
//                             std::advance(it, rand() % lifecycles.size());
//                             Plant* randPlant = it->first;
//                             if (queryType == 0) {
//                                 q = askQuery.careRoutine(randPlant);
//                                 std::cout << customer.getName() << " asking about care routine.\n";
//                             } else if (queryType == 1) {
//                                 q = askQuery.describe(randPlant);
//                                 std::cout << customer.getName() << " asking about description.\n";
//                             } else {
//                                 q = askQuery.stockInfo();
//                                 std::cout << customer.getName() << " asking about stock info.\n";
//                             }
//                         } else {
//                             q = askQuery.stockInfo();
//                             std::cout << customer.getName() << " asking about stock info.\n";
//                         }
//                         chainStart->handleQuery(q);
//                         delete q;
//                     } else {
                        
//                         if (lifecycles.empty()) {
//                             std::cout << customer.getName() << " wanted to buy but no plants available.\n";
//                             continue;
//                         }

//                         auto it = lifecycles.begin();
//                         std::advance(it, rand() % lifecycles.size());
//                         Plant* buyPlant = it->first;
//                         PlantLifeCycle* cycle = it->second;
//                         std::string state = cycle->getState();
//                         if (state == "Withered" || state == "Distressed") {
//                             std::cout << customer.getName() << " didn't buy " << buyPlant->getDescription() << " because it's " << state << ".\n";
//                             continue;
//                         }
//                         int buyQty = rand() % 3 + 1;
//                         int available = salesFloor->getPlantQuantity(buyPlant);
//                         if (available < buyQty) {
//                             std::cout << customer.getName() << " wanted " << buyQty << " but only " << available << " available.\n";
//                             buyQty = available;
//                         }
//                         if (buyQty == 0) continue;

                        
//                         Plant* decorated = new BasePlant(buyPlant->getPrice(), buyPlant->getDescription());
//                         int deco = rand() % 4; 
//                         if (deco == 0) {
//                             decorated = new GiftWrap(decorated);
//                         } else if (deco == 1) {
//                             decorated = new DecorativePot(decorated);
//                         } else if (deco == 2) {
//                             decorated = new SpecialArrangement(decorated);
//                         }

//                         double totalPrice = decorated->getPrice() * buyQty;
//                         Order order(&customer, "ORD-" + std::to_string(rand()));
//                         Transaction* tx = new Transaction(order.getOrderId(), totalPrice, buyQty);
//                         int payType = rand() % 3;
//                         if (payType == 0) tx->setPaymentStrategy(&creditCard);
//                         else if (payType == 1) tx->setPaymentStrategy(&ewallet);
//                         else tx->setPaymentStrategy(&eft);
//                         order.addTransaction(tx);
//                         order.processOrder();

//                         inventory->removeStock(buyPlant, buyQty);
//                         money += totalPrice;
//                         std::cout << customer.getName() << " bought " << buyQty << " " << decorated->getDescription() << " for $" << totalPrice << ".\n";

//                         customer.placeOrder(order);
//                         delete decorated;
//                     }
//                 }
//                 break;
//             }
//             case 4: { 
//                 std::cout << "\nCurrent Money: $" << std::fixed << std::setprecision(2) << money << "\n";
//                 std::cout << "Hired Staff:\n";
//                 for (auto staff : hiredStaff) {
//                     std::cout << "- " << staff->getName() << "\n";
//                 }
//                 std::cout << "Inventory:\n";
//                 salesFloor->displayAvailablePlants();
//                 std::cout << "Plant States:\n";
//                 for (auto& pair : lifecycles) {
//                     Plant* p = pair.first;
//                     PlantLifeCycle* cycle = pair.second;
//                     std::cout << p->getDescription() << ":\n";
//                     std::cout << "  State: " << cycle->getState() << "\n";
//                     std::cout << "  Water: " << p->getCurrentWater() << "/" << p->getMaxWater() << "\n";
//                     std::cout << "  Sunlight: " << p->getCurrentSunlight() << "/" << p->getMaxSunlight() << "\n";
//                     std::cout << "  Nutrients: " << p->getCurrentNutrients() << "/" << p->getMaxNutrients() << "\n";
//                 }
//                 break;
//             }
//             case 5: 
//                 running = false;
//                 break;
//             default:
//                 std::cout << "Invalid choice.\n";
//         }
//     }

//     delete salesFloor;
//     for (auto staff : hiredStaff) {
//         delete staff;
//     }
//     for (auto& pair : lifecycles) {
//         delete pair.second;
//     }
//     delete redRose;
//     delete yellowRose;
//     delete alienPlant;
//     delete oak;
//     delete maple;

//     std::cout << "Game ended.\n";
//     return 0;
// }