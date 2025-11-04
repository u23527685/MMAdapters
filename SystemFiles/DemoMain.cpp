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
#include "AskQuery.h"
#include "InventoryProxy.h"


#define RESET        "\033[0m"
#define PASTEL_PINK    "\033[38;2;255;182;193m"  // Light Pink
#define PASTEL_PEACH   "\033[38;2;255;218;185m"  // Peach Puff
#define PASTEL_ORANGE  "\033[38;2;255;204;153m"  // Soft Orange
#define PASTEL_YELLOW  "\033[38;2;255;255;204m"  // Lemon Chiffon
#define PASTEL_MINT    "\033[38;2;189;252;201m"  // Mint Green
#define PASTEL_GREEN   "\033[38;2;152;251;152m"  // Pale Green
#define PASTEL_AQUA    "\033[38;2;175;238;238m"  // Pale Turquoise
#define PASTEL_BLUE    "\033[38;2;173;216;230m"  // Baby Blue
#define PASTEL_LAVENDER "\033[38;2;230;230;250m" // Lavender Mist
#define PASTEL_PURPLE  "\033[38;2;216;191;216m"  // Thistle
#define PASTEL_ROSE    "\033[38;2;255;228;225m"  // Misty Rose
#define PASTEL_GRAY    "\033[38;2;220;220;220m"  // Light Gray
#define PASTEL_CYAN  "\033[38;2;176;224;230m"
#define PASTEL_SALMON    "\033[38;2;255;170;160m" 



#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <limits>

CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
EWalletPaymentStrategy ewallet("wallet123");
EFTPaymentStrategy eft("9876543210");

double balance = 1000.0;
int day = 1;

std::vector<Transaction*> savedTransactions;



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


static std::string getStaffRole(Staff* s) {
    if (!s) return "Unknown";
    if (dynamic_cast<FloorEmployee*>(s)) return "Floor Employee";
    if (dynamic_cast<FloorManager*>(s)) return "Floor Manager";
    if (dynamic_cast<SalesEmployee*>(s)) return "Sales Employee";
    if (dynamic_cast<SalesManager*>(s)) return "Sales Manager";
    return "Staff";
}

void simulateDay(std::vector<std::unique_ptr<Plant>>& growingPlants,
                PlantInventory* inventory, std::vector<Staff*>& staff) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════╗\n";
    std::cout << "📅   SIMULATING A NEW DAY IN THE NURSERY\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n\n";

    int watered = 0, fertilized = 0, matured = 0, died = 0, neglected = 0;

    
    size_t initialSize = growingPlants.size();
    growingPlants.erase(std::remove_if(growingPlants.begin(), growingPlants.end(),
        [&died](const auto& p) {
            if (!p || !p->getState()) {
                std::cout << PASTEL_GRAY << "💀 Removing invalid plant (Ptr: " << p.get() << ", State: " 
                          << (p && p->getState() ? p->getState()->getName() : "null") << ")\n" << RESET;
                died++;
                return true;
            }
            return false;
        }), growingPlants.end());
    if (initialSize != growingPlants.size()) {
        std::cout << PASTEL_YELLOW << "Removed " << (initialSize - growingPlants.size()) 
                  << " invalid plants from growingPlants\n" << RESET;
    }

    
    std::vector<FloorEmployee*> floorEmployees;
    const int MAX_TASKS_PER_EMPLOYEE = 10;
    std::map<FloorEmployee*, int> tasksAssigned;
    for (auto* s : staff) {
        if (auto* fe = dynamic_cast<FloorEmployee*>(s)) {
            floorEmployees.push_back(fe);
            tasksAssigned[fe] = 0;
        }
    }

    if (floorEmployees.empty()) {
        std::cout << PASTEL_SALMON << "⚠️ No Floor Employees available to care for plants! All plants will be neglected.\n" << RESET;
    }

    
    std::vector<std::unique_ptr<Plant>*> distressedOrWithered;
    std::vector<std::unique_ptr<Plant>*> otherPlants;
    for (auto& plant : growingPlants) {
        if (plant && plant->getState() && (plant->getState()->getName() == "Distressed" || plant->getState()->getName() == "Withered")) {
            distressedOrWithered.push_back(&plant);
        } else if (plant) {
            otherPlants.push_back(&plant);
        }
    }

    std::vector<std::unique_ptr<Plant>*> allPlants = distressedOrWithered;
    allPlants.insert(allPlants.end(), otherPlants.begin(), otherPlants.end());

    
    std::vector<size_t> plantsToRemove;
    for (size_t i = 0; i < allPlants.size(); ++i) {
        Plant* plant = allPlants[i] ? allPlants[i]->get() : nullptr;
        if (!plant || !plant->getState()) {
            std::cout << PASTEL_GRAY << "💀 Plant " << (plant ? plant->getName() : "Unknown") 
                      << " has no state or is null and died!\n" << RESET;
            plantsToRemove.push_back(i);
            died++;
            continue;
        }

        FloorEmployee* assignedEmployee = nullptr;
        for (auto* fe : floorEmployees) {
            if (tasksAssigned[fe] < MAX_TASKS_PER_EMPLOYEE) {
                assignedEmployee = fe;
                tasksAssigned[fe]++;
                break;
            }
        }

        if (!assignedEmployee) {
            std::cout << PASTEL_YELLOW << "⚠️ No Floor Employee available for " << plant->getName()
                      << " (" << plant->getState()->getName() << "). Plant neglected!\n" << RESET;
            neglected++;
            continue;
        }

        PlantLifeCycle cycle(plant, std::unique_ptr<PlantState>(plant->getState()->clone()), plant->getName());
        cycle.attach(assignedEmployee);

        auto routine = PlantCareRoutine::PlantCare(plant);
        if (!routine) {
            std::cout << PASTEL_SALMON << "❌ No care routine for " << plant->getName() << "\n" << RESET;
            plantsToRemove.push_back(i);
            died++;
            continue;
        }

        std::cout << PASTEL_GREEN << "📋 [" << assignedEmployee->getName() << "] noticed " << plant->getName()
                  << " in " << plant->getState()->getName() << " state. Applying care: ";
        cycle.getStateObj()->applyCare(&cycle, plant, routine.get());

        
        watered++;
        fertilized++;

        cycle.simulateTimePassing();
        bool stateChanged = cycle.updatePlant();
        std::unique_ptr<PlantState> newState = cycle.releaseState();
        if (!newState) {
            std::cout << PASTEL_SALMON << "❌ Plant " << plant->getName() << " state became null!\n" << RESET;
            plantsToRemove.push_back(i);
            died++;
            continue;
        }
        std::cout << PASTEL_GREEN << "Updating state for " << plant->getName() 
                  << " to " << newState->getName() << "\n" << RESET;
        plant->setState(std::move(newState));

        std::string stateName = plant->getState()->getName();
        if (stateName == "Mature") {
            std::cout << PASTEL_GREEN << "🌸 Plant " << plant->getName() << " has matured. Moving to inventory.\n" << RESET;

            
            Plant* inventoryPlant = nullptr;
            if (plant->getDescription() == "Red Rose") {
                inventoryPlant = new Rose(10.0, "Red Rose");
                inventoryPlant->setCategory("Sunny");
                inventoryPlant->setState(std::make_unique<MatureState>());
                std::cout << PASTEL_GREEN << "Created new Red Rose for inventory (Ptr: " << inventoryPlant << ")\n" << RESET;
            } else if (plant->getDescription() == "Yellow Rose") {
                inventoryPlant = new Rose(9.0, "Yellow Rose");
                inventoryPlant->setCategory("Shade");
                inventoryPlant->setState(std::make_unique<MatureState>());
                std::cout << PASTEL_GREEN << "Created new Yellow Rose for inventory (Ptr: " << inventoryPlant << ")\n" << RESET;
            } else if (plant->getDescription() == "Oak Tree") {
                inventoryPlant = new Oak(7.0, "Oak Tree");
                inventoryPlant->setCategory("Temperate");
                inventoryPlant->setState(std::make_unique<MatureState>());
                std::cout << PASTEL_GREEN << "Created new Oak Tree for inventory (Ptr: " << inventoryPlant << ")\n" << RESET;
            }

            if (inventoryPlant) {
                std::cout << PASTEL_GREEN << "Adding " << inventoryPlant->getDescription() 
                          << " to inventory (Ptr: " << inventoryPlant << ").\n" << RESET;
                inventory->addStock(inventoryPlant, 1);
                plantsToRemove.push_back(i);
                matured++;
            } else {
                std::cout << PASTEL_SALMON << "❌ Failed to create new plant for inventory: " 
                          << plant->getDescription() << "\n" << RESET;
            }
        } else if (stateName == "Withered") {
            std::cout << PASTEL_GRAY << "💀 Plant " << plant->getName() << " has withered and died!\n" << RESET;
            plantsToRemove.push_back(i);
            died++;
        }
    }

    
    std::sort(plantsToRemove.begin(), plantsToRemove.end(), std::greater<size_t>());
    for (size_t idx : plantsToRemove) {
        if (idx < growingPlants.size()) {
            growingPlants.erase(growingPlants.begin() + idx);
        }
    }

    
    int numCustomers = rand() % 5 + 1;
    std::cout << "\n📈 " << numCustomers << " customers visited today.\n" << RESET;

    Staff* chainStart = nullptr;
    for (size_t i = 0; i < staff.size(); ++i) {
        if (i == 0) chainStart = staff[i];
        if (i < staff.size() - 1) {
            staff[i]->setNext(staff[i + 1]);
        } else {
            staff[i]->setNext(nullptr);
        }
    }

    for (int i = 0; i < numCustomers; ++i) {
        Customer customer("Customer_" + std::to_string(i + 1));
        int action = rand() % 2; 
        if (action == 0) {
            if (!chainStart) {
                std::cout << PASTEL_SALMON << "❌ " << customer.getName() << " tried to ask a query, but no staff available.\n" << RESET;
                continue;
            }

            auto inventoryItems = inventory->getInventoryView();
            if (inventoryItems.empty()) {
                std::cout << PASTEL_SALMON << "❌ " << customer.getName() << " tried to ask a query, but no plants available.\n" << RESET;
                continue;
            }

            Plant* randPlant = nullptr;
            auto it = inventoryItems.begin();
            std::advance(it, rand() % inventoryItems.size());
            randPlant = it->first;

            if (!randPlant) {
                std::cout << PASTEL_SALMON << "❌ " << customer.getName() << " tried to ask a query, but no valid plant found.\n" << RESET;
                continue;
            }

            int queryType = rand() % 2;
            AskQuery queryBuilder;
            Query* q = nullptr;
            if (queryType == 0) {
                q = queryBuilder.careRoutine(randPlant);
                std::cout << PASTEL_AQUA << customer.getName() << " asking about care routine for " << randPlant->getDescription() << ".\n" << RESET;
            } else {
                q = queryBuilder.describe(randPlant);
                std::cout << PASTEL_AQUA << customer.getName() << " asking for description of " << randPlant->getDescription() << ".\n" << RESET;
            }

            if (q) {
                std::cout << PASTEL_GREEN << "\nHandling query for " << randPlant->getDescription() << " by " << chainStart->getName() << "\n" << RESET;
                chainStart->handleQuery(q);
                delete q;
                q = nullptr;
            } else {
                std::cout << PASTEL_SALMON << "❌ Failed to create query for " << customer.getName() << ".\n" << RESET;
            }
        } else {
            auto inventoryItems = inventory->getInventoryView();
            if (inventoryItems.empty()) {
                std::cout << PASTEL_SALMON << customer.getName() << " wanted to buy, but no plants available.\n" << RESET;
                continue;
            }
            auto it = inventoryItems.begin();
            std::advance(it, rand() % inventoryItems.size());
            Plant* buyPlant = it->first;
            if (!buyPlant) {
                std::cout << PASTEL_SALMON << "❌ No valid plant selected for purchase by " << customer.getName() << ".\n" << RESET;
                continue;
            }
            int buyQty = rand() % 3 + 1;
            int available = inventory->getQuantity(buyPlant);
            if (available < buyQty) {
                std::cout << PASTEL_YELLOW << customer.getName() << " wanted " << buyQty << " " << buyPlant->getDescription()
                          << ", but only " << available << " available.\n" << RESET;
                buyQty = available;
            }
            if (buyQty == 0) continue;

            std::cout << PASTEL_GREEN << "\nProcessing purchase of " << buyQty << " " << buyPlant->getDescription() << " by " << customer.getName() << "\n" << RESET;

            Plant* decorated = new BasePlant(buyPlant->getPrice(), buyPlant->getDescription());
            int deco = rand() % 4;
            if (deco == 0) decorated = new GiftWrap(decorated);
            else if (deco == 1) decorated = new DecorativePot(decorated);
            else if (deco == 2) decorated = new SpecialArrangement(decorated);

            double totalPrice = decorated->getPrice() * buyQty;
            Order order(&customer, "ORD-" + std::to_string(rand()));
            Transaction* tx = new Transaction(order.getOrderId(), totalPrice, buyQty);
            int payType = rand() % 3;
            if (payType == 0) tx->setPaymentStrategy(&creditCard);
            else if (payType == 1) tx->setPaymentStrategy(&ewallet);
            else tx->setPaymentStrategy(&eft);
            order.addTransaction(tx);
            order.processOrder();

            if (inventory->removeStock(buyPlant, buyQty)) {
                balance += totalPrice;
                savedTransactions.push_back(tx);
                std::cout << PASTEL_GREEN << customer.getName() << " bought " << buyQty << " " << decorated->getDescription()
                          << " for R" << std::fixed << std::setprecision(2) << totalPrice << ".\n" << RESET;
            } else {
                delete tx;
                std::cout << PASTEL_SALMON << "❌ Purchase failed for " << customer.getName() << ": not enough stock.\n" << RESET;
            }
            delete decorated;
        }
    }

    std::cout << "\n📦 INVENTORY AFTER SIMULATION:\n";
    auto inventoryItems = inventory->getInventoryView();
    if (inventoryItems.empty()) {
        std::cout << PASTEL_GRAY << "Inventory is empty!\n" << RESET;
    } else {
        for (const auto& item : inventoryItems) {
            if (item.first) {
                std::cout << PASTEL_GREEN << item.first->getDescription() << " (Qty: " << item.second 
                          << ", Ptr: " << item.first << ")\n" << RESET;
            } else {
                std::cout << PASTEL_SALMON << "⚠️ Invalid plant pointer in inventory!\n" << RESET;
            }
        }
    }
    day++;

    std::cout << "\n═══════════════════════════════════════════\n";
    std::cout << "✅ DAILY SUMMARY\n";
    std::cout << "═══════════════════════════════════════════\n";
    std::cout << PASTEL_AQUA << "💧 Watered:       " << watered << "\n" << RESET;
    std::cout << PASTEL_MINT << "🌿 Fertilized:    " << fertilized << "\n" << RESET;
    std::cout << PASTEL_PINK << "🌸 Matured:       " << matured << "\n" << RESET;
    std::cout << PASTEL_GRAY << "💀 Died:          " << died << "\n" << RESET;
    std::cout << PASTEL_YELLOW << "⚠️  Neglected:     " << neglected << "\n" << RESET;
    std::cout << PASTEL_ORANGE << "🗓️  Days Passed:   " << day << "\n" << RESET;
    std::cout << "═══════════════════════════════════════════\n";
    std::cout << PASTEL_GREEN << "🌱 End of day processing complete.\n\n" << RESET;
}



void runTutorial(std::vector<std::unique_ptr<Plant>>& growingPlants, PlantInventory* inventory,
                std::vector<Staff*>& hiredStaff, std::vector<Transaction*>& savedTransactions,
                std::map<std::string, int>& plantMenuOptions, double& balance,
                CreditCardPaymentStrategy& creditCard, EWalletPaymentStrategy& ewallet,
                EFTPaymentStrategy& eft) {
    std::cout << "\n🌸 Welcome to Plantopia’s Guided Tour! 🌸\n";
    std::cout << "I’m Flora the Botanist, your friendly guide! Let’s explore how to run your magical nursery in 5 fun steps.\n";
    std::cout << "Follow my instructions, and you’ll be a plant pro in no time! 🌱\n\n";
    std::cout << "Type 1 and Enter to start each step, or type 'skip' to exit the tutorial.\n";

    std::string input;
    std::getline(std::cin >> std::ws, input);
    if (input == "skip") {
        std::cout << "Alright, skipping the tutorial! Dive into Plantopia! 🌿\n";
        return;
    }

    // Step 1: Hire Staff
    std::cout << "\n🌟 Step 1: Hiring Your Dream Team 🌟\n";
    std::cout << "To grow plants, you need staff! Let’s hire a Floor Employee to care for your plants.\n";
    std::cout << "Your balance is R" << std::fixed << std::setprecision(2) << balance << ". Hiring a Floor Employee costs R200.\n\n";
    std::cout << "Type 1 and Enter to hire 'Flora’s Assistant' (Floor Employee), or type 'skip' to exit.\n";
    std::getline(std::cin >> std::ws, input);
    if (input == "skip") {
        std::cout << "Skipping the tutorial! Let’s grow some plants! 🌿\n";
        return;
    }
    Staff* assistant = new FloorEmployee("Flora’s Assistant");
    hiredStaff.push_back(assistant);
    if (balance >= 200) {
        balance -= 200;
        std::cout << "🎉 Hired Flora’s Assistant! They’ll help your plants grow. Current balance: R" << balance << "\n";
    } else {
        std::cout << "🎉 Hired Flora’s Assistant for free (tutorial bonus)! They’ll help your plants grow. Current balance: R" << balance << "\n";
    }

    // Step 2: Buy Seeds
    std::cout << "\n🌱 Step 2: Planting the Seeds of Success 🌱\n";
    std::cout << "Now, let’s buy a Red Rose seed to start your nursery. It costs R3.00.\n\n";
    std::cout << "Type 1 and Enter to buy 1 Red Rose seed, or type 'skip' to exit.\n";
    std::getline(std::cin >> std::ws, input);
    if (input == "skip") {
        std::cout << "Skipping the tutorial! Happy planting! 🌿\n";
        return;
    }
    auto seed = createSeedPlant(1); 
    growingPlants.push_back(std::move(seed));
    if (balance >= 3.0) {
        balance -= 3.0;
        std::cout << "🌹 Bought 1 Red Rose seed! It’s in your nursery. Current balance: R" << balance << "\n";
    } else {
        std::cout << "🌹 Bought 1 Red Rose seed for free (tutorial bonus)! It’s in your nursery. Current balance: R" << balance << "\n";
    }

    // Step 3: Simulate a Day
    std::cout << "\n☀️ Step 3: Let Time Work Its Magic ☀️\n";
    std::cout << "Your Floor Employee will care for the Red Rose seed. Let’s simulate a day to see it grow!\n\n";
    std::cout << "Type 1 and Enter to simulate a day, or type 'skip' to exit.\n";
    std::getline(std::cin >> std::ws, input);
    if (input == "skip") {
        std::cout << "Skipping the tutorial! Enjoy Plantopia! 🌿\n";
        return;
    }
    if (!growingPlants.empty()) {
        auto matureRose = std::make_unique<Rose>(10.0, "Red Rose");
        matureRose->setCategory("Sunny");
        matureRose->setState(std::make_unique<MatureState>());
        Plant* rawRose = matureRose.release();
        inventory->addStock(rawRose, 1);
        growingPlants.clear(); 
        std::cout << "🌟 Wow! Your Red Rose matured in record time and is now available for sale!\n";
    } else {
        auto matureRose = std::make_unique<Rose>(10.0, "Red Rose");
        matureRose->setCategory("Sunny");
        matureRose->setState(std::make_unique<MatureState>());
        Plant* rawRose = matureRose.release();
        inventory->addStock(rawRose, 1);
        std::cout << "🌟 Planted a Red Rose for free and it matured instantly (tutorial magic)! Now available for sale!\n";
    }

    std::cout << "\n❓ Step 4: Helping Curious Customers ❓\n";
    std::cout << "Customers love to ask questions! Let’s ask about the Red Rose’s care routine.\n\n";
    std::cout << "Type 1 and Enter to ask 'What is the care routine for Red Rose?', or type 'skip' to exit.\n";
    std::getline(std::cin >> std::ws, input);
    if (input == "skip") {
        std::cout << "Skipping the tutorial! You’re ready for Plantopia! 🌿\n";
        return;
    }
    bool hasSalesStaff = false;
    for (auto* staff : hiredStaff) {
        if (dynamic_cast<SalesEmployee*>(staff) || dynamic_cast<SalesManager*>(staff)) {
            hasSalesStaff = true;
            break;
        }
    }
    if (!hasSalesStaff) {
        Staff* sales = new SalesEmployee("Flora’s Sales Star");
        hiredStaff.push_back(sales);
        std::cout << "🎉 Hired Flora’s Sales Star for free to handle queries! 🌟\n";
    }
    // Set up chain of responsibility
    for (size_t i = 0; i < hiredStaff.size(); ++i) {
        if (i < hiredStaff.size() - 1) {
            hiredStaff[i]->setNext(hiredStaff[i + 1]);
        } else {
            hiredStaff[i]->setNext(nullptr);
        }
    }
    AskQuery queryBuilder;
    Query* query = nullptr;
    Plant* selectedPlant = nullptr;
    auto inventoryItems = inventory->getInventoryView();
    for (const auto& item : inventoryItems) {
        if (item.first && item.first->getDescription() == "Red Rose") {
            selectedPlant = item.first;
            break;
        }
    }
    if (selectedPlant) {
        query = queryBuilder.careRoutine(selectedPlant);
        std::cout << "\n--- Processing Query ---\n";
        if (!hiredStaff.empty()) {
            hiredStaff[0]->handleQuery(query);
        } else {
            std::cout << "❌ No staff available to handle query. Imagine Flora’s Assistant said: 'Water and sun daily!'\n";
        }
        delete query;
    } else {
        std::cout << "❌ No Red Roses to query. Imagine Flora’s Assistant said: 'Water and sun daily!' 😊\n";
    }

    // Step 5: Make a Purchase
    std::cout << "\n🛒 Step 5: Selling Your Beautiful Plants 🛒\n";
    std::cout << "A customer wants to buy your Red Rose! Let’s sell one with a Gift Wrap decoration.\n";
    std::cout << "Type 1 and Enter to sell 1 Red Rose with Gift Wrap using Credit Card, or type 'skip' to exit.\n";
    std::getline(std::cin >> std::ws, input);
    if (input == "skip") {
        std::cout << "Skipping the tutorial! Happy selling! 🌿\n";
        return;
    }
    selectedPlant = nullptr;
    inventoryItems = inventory->getInventoryView();
    for (const auto& item : inventoryItems) {
        if (item.first && item.first->getDescription() == "Red Rose" && item.second > 0) {
            selectedPlant = item.first;
            break;
        }
    }
    if (selectedPlant) {
        Customer customer("Tutorial Customer");
        Plant* decorated = new BasePlant(selectedPlant->getPrice(), selectedPlant->getDescription());
        decorated = new GiftWrap(decorated);
        double total = decorated->getPrice() * 1; 
        if (inventory->removeStock(selectedPlant, 1)) { 
            Order order(&customer, "ORD-TUTORIAL");
            Transaction* tx = new Transaction(order.getOrderId(), total, 1);
            tx->setPaymentStrategy(&creditCard);
            order.addTransaction(tx);
            order.processOrder();
            savedTransactions.push_back(tx);
            balance += total;
            std::cout << "\n🎉 Sold 1 Gift-Wrapped Red Rose for R" << std::fixed << std::setprecision(2) << total << "!\n";
            std::cout << "=========================================\n";
            std::cout << "             🧾 PURCHASE RECEIPT\n";
            std::cout << "=========================================\n";
            std::cout << "Order ID: " << order.getOrderId() << "\n";
            std::cout << "Customer: " << customer.getName() << "\n";
            std::cout << "Item: " << decorated->getDescription() << "\n";
            std::cout << "Quantity: 1\n";
            std::cout << "Payment Method: Credit Card\n";
            std::cout << "Total: R" << total << "\n";
            std::cout << "=========================================\n";
            std::cout << "Current balance: R" << balance << "\n";
            delete decorated;
        } else {
            std::cout << "❌ Failed to remove Red Rose from inventory. Let’s pretend you sold it! Balance +R15.00.\n";
            balance += 15.0;
            delete decorated;
        }
    } else {
        std::cout << "❌ No Red Roses in stock. Let’s pretend you sold one! Balance +R15.00.\n";
        balance += 15.0;
    }

    

    std::cout << "\n🎉 Congratulations! You’ve completed the Plantopia tutorial! 🎉\n";
    std::cout << "You’re now ready to run your nursery. Grow plants, sell them, and answer customer queries!\n \n";
    std::cout << "Type 1 and enter to start your Plantopia adventure!\n";
    std::getline(std::cin >> std::ws, input);
}

int main() {
    srand(static_cast<unsigned>(time(0)));

std::cout << PASTEL_MINT << "=============================================\n" << RESET;
std::cout << PASTEL_SALMON << "🌿   Welcome to Plantopia: Terminal Edition   🌿\n" << RESET;
std::cout << PASTEL_MINT << "=============================================\n" << RESET;


    std::cout << "\nWould you like to play the interactive tutorial? (y/n): ";
    char tutorialChoice;
    while (true) {
        std::cin >> tutorialChoice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (tutorialChoice == 'y' || tutorialChoice == 'Y' || tutorialChoice == 'n' || tutorialChoice == 'N') {
            break;
        }
        std::cout << "Invalid input. Please enter 'y' or 'n': ";
    }

    
    PlantInventory* inventory = PlantInventory::getInstance();
    std::unique_ptr<SalesFloorObserver> salesFloor = std::make_unique<SalesFloorObserver>(inventory);

    
   

    
    InventoryProxy proxy(salesFloor.get());

    
    auto redRose = std::make_unique<Rose>(10.0, "Red Rose");
    auto yellowRose = std::make_unique<Rose>(9.0, "Yellow Rose");
    auto oakTree = std::make_unique<Oak>(7.0, "Oak Tree");

    
    inventory->addStock(redRose.get(), 0);
    inventory->addStock(yellowRose.get(), 0);
    inventory->addStock(oakTree.get(), 0);

    
    std::cout << "Initial inventory state:\n";
    auto inventoryItems = inventory->getInventoryView();
    if (inventoryItems.empty()) {
        std::cout << "Initial inventory is empty!\n";
    } else {
        for (const auto& item : inventoryItems) {
            std::cout << "" << item.first->getDescription() << " (Qty: " << item.second << ", Ptr: " << item.first << ")\n";
        }
    }

    
    std::map<std::string, int> plantMenuOptions = {
        {"Red Rose", 1},
        {"Yellow Rose", 2},
        {"Oak Tree", 3}
    };

    
    


    Plant* lastPurchasedPlant = nullptr;
    int lastPurchasedQuantity = 0;

   
    std::vector<Staff*> hiredStaff;
    std::vector<std::unique_ptr<Plant>> growingPlants;

    if (tutorialChoice == 'y' || tutorialChoice == 'Y') {
        runTutorial(growingPlants, inventory, hiredStaff, savedTransactions, plantMenuOptions, balance,
                    creditCard, ewallet, eft);
    }
    bool running = true;

    while (running) {
std::cout << "\n"
          << PASTEL_MINT << "╔══════════════════════════╗\n"
          << PASTEL_SALMON << "         Main Menu          \n"
          << PASTEL_MINT << "╚══════════════════════════╝\n" << RESET;

        std::cout << PASTEL_BLUE << "\nCurrent Balance: R" 
                << std::fixed << std::setprecision(2) << balance << "\n" << RESET;

        std::cout << PASTEL_ORANGE   << "1. Staff menu\n"        << RESET;
        std::cout << PASTEL_PINK<< "2. Customer menu\n"     << RESET;
        std::cout << PASTEL_YELLOW   << "3. Simulate a day\n"    << RESET;
        std::cout << PASTEL_SALMON   << "4. Exit\n"              << RESET;

        std::cout << PASTEL_MINT << "Select action: " << RESET;

        int roleChoice;
        while (true) {
            std::cin >> roleChoice;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a number: ";
                continue;
            }
            break;
        }

        if (roleChoice >= 4) break;

        
        if (roleChoice == 1) {
            bool staffRunning = true;
            while (staffRunning) {
std::cout << "\n"
          << PASTEL_PEACH << "╔══════════════════════════╗\n"
          << PASTEL_PINK  << "         Staff Menu         \n"
          << PASTEL_PEACH << "╚══════════════════════════╝" << RESET << "\n";

        std::cout << PASTEL_YELLOW  << "1. Hire Staff Member\n"        << RESET;
        std::cout << PASTEL_ORANGE  << "2. View Hired Staff\n"         << RESET;
        std::cout << PASTEL_PINK    << "3. Buy Plant Seeds\n"          << RESET;
        std::cout << PASTEL_CYAN    << "4. View Nursery Inventory\n"   << RESET;
        std::cout << PASTEL_AQUA    << "5. View staff notifications\n" << RESET;
        std::cout << PASTEL_SALMON  << "6. Back\n"                     << RESET;

        std::cout << PASTEL_MINT    << "Enter choice: "                << RESET;



                int sChoice;
                while (true) {
                    std::cin >> sChoice;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number: ";
                        continue;
                    }
                    break;
                }
                if (sChoice >= 6) break;

                
                if (sChoice == 1) {
                    std::cout << "\nCurrent Balance: R" << std::fixed << std::setprecision(2) << balance;
                    std::cout << "\nChoose staff type:\n1. Floor Employee (R200)\n2. Floor Manager (R400)\n3. Sales Employee (R300)\n4. Sales Manager (R500)\n5. Back to staff menu\nEnter number: ";
                    int type;
                    while (true) {
                        std::cin >> type;
                        if (std::cin.fail() || type < 1 || type > 5) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
                            continue;
                        }
                        break;
                    }

                    Staff* newStaff = nullptr;
                    double cost = 0;
                    std::string names[10] = {
                        "Alex",
                        "Sophie",
                        "Michael",
                        "Emma",
                        "James",
                        "Olivia",
                        "William",
                        "Ava",
                        "Lucas",
                        "Mia"
                    };

                    srand(time(0));
                    int randomIndex = rand() % 10;
                    switch (type) {
                        case 1: newStaff = new FloorEmployee(names[randomIndex]); cost = 200; break;
                        case 2: newStaff = new FloorManager(names[randomIndex]); cost = 400; break;
                        case 3: newStaff = new SalesEmployee(names[randomIndex]); cost = 300; break;
                        case 4: newStaff = new SalesManager(names[randomIndex]); cost = 500; break;
                        case 5: continue;
                    }

                    if (balance < cost) {
                        std::cout << "\nNot enough funds!\n";
                        delete newStaff;
                    } else {
                        hiredStaff.push_back(newStaff);
                        salesFloor->attachStaff(newStaff);
                        balance -= cost;
                        std::cout << "\n✅ Hired " << newStaff->getName() << " (" << getStaffRole(newStaff) << ") successfully!\n";
                    }
                }

                
                else if (sChoice == 2) {
                    std::cout << "\n--- Hired Staff ---\n";
                    if (hiredStaff.empty()) std::cout << "None yet.\n";
                    else {
                        for (auto s : hiredStaff) {
                            std::cout << "- " << s->getName() << " (" << getStaffRole(s) << ")\n";
                        }
                    }
                }

                
                else if (sChoice == 3) {
                    while (true) {
                        std::cout << "\nAvailable seeds to buy:\n1. Red rose seed (R3.00)\n2. Yellow rose seed (R2.50)\n3. Oak tree seed (R1.50)\n4. Return to staff menu\n";
                        int type;
                        while (true) {
                            std::cin >> type;
                            if (std::cin.fail() || type < 1 || type > 4) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid input. Please enter a number between 1 and 4: ";
                                continue;
                            }
                            break;
                        }

                        
                        if (type == 4) {
                            std::cout << "Returning to staff menu.\n";
                            break; 
                        }

                        std::cout << "\nEnter quantity to buy: ";
                        int qty;
                        while (true) {
                            std::cin >> qty;
                            if (std::cin.fail() || qty <= 0) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid quantity. Please enter a positive number: ";
                                continue;
                            }
                            break;
                        }

                        double costPerSeed = (type == 1 ? 3.0 : (type == 2 ? 2.50 : 1.50));
                        double totalCost = costPerSeed * qty;
                        if (balance < totalCost) {
                            std::cout << "❌ Not enough balance.\n";
                            continue; 
                        }

                        for (int i = 0; i < qty; ++i) {
                            growingPlants.push_back(createSeedPlant(type));
                        }

                        std::cout << "✅ Purchased " << qty << " seeds and added to nursery. (for R" << totalCost << ")\n";
                        balance -= totalCost;
                        std::cout << "Current Balance: R" << std::fixed << std::setprecision(2) << balance << "\n";
                    }
                }

                

                else if (sChoice == 4) {
                    std::cout << PASTEL_CYAN << "\n🌿 --- Growing Nursery --- 🌿\n" << RESET;
                    if (growingPlants.empty()) {
                        std::cout << PASTEL_PINK << "No plants currently growing.\n" << RESET;
                    } else {
                        for (auto& p : growingPlants) {
                            std::cout << PASTEL_MINT << "- " << p->getDescription() << RESET;
                            if (p->getState())
                                std::cout << " | State: " << PASTEL_PURPLE << p->getState()->getName() << RESET;
                            else
                                std::cout << " | State: " << PASTEL_YELLOW << "None" << RESET;
                            std::cout << " | Category: " << PASTEL_ORANGE << p->getCategory() << RESET
                                    << " | Water: " << PASTEL_BLUE << p->getCurrentWater() << "/" << p->getMaxWater() << RESET
                                    << " | Sunlight: " << PASTEL_YELLOW << p->getCurrentSunlight() << "/" << p->getMaxSunlight() << RESET
                                    << " | Nutrients: " << PASTEL_GREEN << p->getCurrentNutrients() << "/" << p->getMaxNutrients() << RESET
                                    << " | Growth: " << PASTEL_PINK << p->getGrowthProgress() << "%" << RESET << "\n";
                        }
                    }

                    std::cout << PASTEL_CYAN << "\n🌸 --- Plants Available for Sale --- 🌸\n" << RESET;
                    auto inventoryItems = inventory->getInventoryView();
                    if (inventoryItems.empty()) {
                        std::cout << PASTEL_PINK << "No plants available for sale.\n" << RESET;
                    } else {
                        std::map<std::string, std::pair<Plant*, int>> consolidatedItems;
                        for (const auto& item : inventoryItems) {
                            if (!item.first || item.second <= 0) continue;
                            std::string desc = item.first->getDescription();
                            if (consolidatedItems.find(desc) == consolidatedItems.end()) {
                                consolidatedItems[desc] = {item.first, item.second};
                            } else {
                                consolidatedItems[desc].second += item.second;
                            }
                        }
                        for (const auto& item : consolidatedItems) {
                            auto it = plantMenuOptions.find(item.first);
                            if (it != plantMenuOptions.end()) {
                                std::cout << PASTEL_GREEN << it->second << ". " << item.first << RESET
                                        << " - R" << PASTEL_YELLOW << std::fixed << std::setprecision(2)
                                        << item.second.first->getPrice() << RESET
                                        << " (Qty: " << PASTEL_PURPLE << item.second.second << RESET << ")\n";
                            }
                        }
                    }
                }

                
                else if (sChoice == 5) {
                    std::cout << PASTEL_BLUE << "\n📢 Staff Notifications\n" << RESET;
                    std::cout << "Staff are automatically informed of new plants entering and leaving your nursery.\n\n";
                    
                    std::cout << PASTEL_BLUE << "Currently attached staff:\n" << RESET;
                    if (hiredStaff.empty()) {
                        std::cout << PASTEL_SALMON << "⚠️ No staff hired yet. Hire staff to see them receive notifications!\n\n" << RESET;
                    } else {
                        for (auto* s : hiredStaff) {
                            std::cout << PASTEL_GREEN << "- " << s->getName() << " (" << getStaffRole(s) << ")\n" << RESET;
                        }
                        std::cout << "\n";
                    }
                    
                    const auto& notifications = salesFloor->getNotificationHistory();
                    if (notifications.empty()) {
                        std::cout << PASTEL_SALMON << "📭 No notifications yet.\n" << RESET;
                        std::cout << "Buy seeds, simulate days, or make sales to see notifications!\n\n";
                    } else {
                        std::cout << PASTEL_BLUE << "📬 Notification History (" << notifications.size() << " total):\n" << RESET;
                        std::cout << "---------------------------------------------------\n";
                        
                        int startIdx = std::max(0, static_cast<int>(notifications.size()) - 10);
                        for (size_t i = startIdx; i < notifications.size(); ++i) {
                            std::cout << "[" << (i + 1) << "] ";
                            if (!hiredStaff.empty()) {
                                for (auto* staff : hiredStaff) {
                                    std::cout << PASTEL_GREEN << "[Notification to " << staff->getName() << "] " << RESET;
                                }
                            }
                            std::cout << notifications[i] << "\n";
                        }
                        std::cout << "---------------------------------------------------\n";
                        
                        if (notifications.size() > 10) {
                            std::cout << "Showing last 10 of " << notifications.size() << " notifications.\n";
                        }
                    }
                    
                    std::cout << PASTEL_GREEN << "\n--- Current Sales Floor Status ---\n" << RESET;
                    //  provides an undefine ref
                    // proxy.displayAvailablePlants();
                    
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                }
            }
        }

        
        else if (roleChoice == 2) {
            Customer customer("Walk-in Customer");
            bool custRunning = true;
            while (custRunning) {
std::cout << "\n"
          << PASTEL_AQUA << "╔══════════════════════════╗\n"
          << PASTEL_PINK<< "        Customer Menu     \n"
          << PASTEL_AQUA << "╚══════════════════════════╝\n" << RESET;

            std::cout << PASTEL_CYAN     << "1. View Inventory\n"                      << RESET;
            std::cout << PASTEL_BLUE     << "2. Buy Plant\n"                           << RESET;
            std::cout << PASTEL_PURPLE   << "3. Repurchase Last Order (Memento)\n"     << RESET;
            std::cout << PASTEL_LAVENDER << "4. View Receipt\n"                        << RESET;
            std::cout << PASTEL_AQUA     << "5. Ask a query\n"                         << RESET;
            std::cout << PASTEL_MINT      << "6. Try to steal plants\n" << RESET;
            std::cout << PASTEL_SALMON   << "7. Back\n"                                << RESET;

            std::cout << PASTEL_MINT     << "Choose: " << RESET;

                int cChoice;
                while (true) {
                    std::cin >> cChoice;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number: ";
                        continue;
                    }
                    break;
                }

                if (cChoice == 7) break;

                if (cChoice == 1) {
                    std::cout << "\n🌿 Available Plants 🌿\n";
                    auto inventoryItems = inventory->getInventoryView();
                    if (inventoryItems.empty()) {
                        std::cout << "No plants available for sale.\n";
                    } else {
                        for (const auto& item : inventoryItems) {
                            auto it = plantMenuOptions.find(item.first->getDescription());
                            if (it != plantMenuOptions.end()) {
                                int qty = item.second;
                                if (qty > 0)
                                    std::cout << it->second << ". " << item.first->getDescription() << " - R"
                                              << std::fixed << std::setprecision(2) << item.first->getPrice()
                                              << " (Qty: " << qty << ")\n";
                                else
                                    std::cout << it->second << ". " << item.first->getDescription() << " - ❌ Out of stock!\n";
                            }
                        }
                    }
                }

                else if (cChoice == 2) {
                    
                    std::cout << "\nSelect plant to buy (0 to cancel):\n";
                    auto invViewForMenu = inventory->getInventoryView();
                    if (invViewForMenu.empty()) {
                        std::cout << "No plants available for sale.\n";
                        continue;
                    }
                    for (const auto& item : invViewForMenu) {
                        if (!item.first) continue;
                        auto it = plantMenuOptions.find(item.first->getDescription());
                        if (it != plantMenuOptions.end()) {
                            int qty = item.second;
                            if (qty > 0) {
                                std::cout << it->second << ". " << item.first->getDescription()
                                          << " - R" << std::fixed << std::setprecision(2) << item.first->getPrice()
                                          << " (Qty: " << qty << ")\n";
                            } else {
                                std::cout << it->second << ". " << item.first->getDescription() << " - ❌ Out of stock!\n";
                            }
                        }
                    }

                    std::cout << "Enter choice: ";
                    int choice;
                    while (true) {
                        std::cin >> choice;
                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number: ";
                            continue;
                        }
                        break;
                    }
                    if (choice == 0) continue;

                    
                    Plant* selectedPlant = nullptr;
                    auto inventoryItems = inventory->getInventoryView();
                    for (const auto& item : inventoryItems) {
                        if (!item.first) continue;
                        auto it = plantMenuOptions.find(item.first->getDescription());
                        if (it != plantMenuOptions.end() && it->second == choice) {
                            selectedPlant = item.first;
                            break;
                        }
                    }

                    if (!selectedPlant) {
                        std::cout << "❌ Invalid plant selection!\n";
                        continue;
                    }

                    int available = inventory->getQuantity(selectedPlant);
                    if (available <= 0) {
                        std::cout << "❌ Out of stock!\n";
                        continue;
                    }

                    std::cout << "\nEnter quantity (max " << available << "): ";
                    int qty;
                    while (true) {
                        std::cin >> qty;
                        if (std::cin.fail() || qty <= 0 || qty > available) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid quantity. Please enter a number between 1 and " << available << ": ";
                            continue;
                        }
                        break;
                    }

                    
                    Plant* decorated = new BasePlant(selectedPlant->getPrice(), selectedPlant->getDescription());
                    bool addingDecor = true;
                    while (addingDecor) {
                        std::cout << "\nAdd decoration?\n"
                                  << "1. Gift Wrap (+R5)\n"
                                  << "2. Decorative Pot (+R10)\n"
                                  << "3. Special Arrangement (+R15)\n"
                                  << "4. Done\n"
                                  << "Choose: ";
                        int decoChoice;
                        while (true) {
                            std::cin >> decoChoice;
                            if (std::cin.fail()) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "Invalid input. Please enter a number: ";
                                continue;
                            }
                            break;
                        }
                        switch (decoChoice) {
                            case 1: decorated = new GiftWrap(decorated); std::cout << "🎁 Added Gift Wrap\n"; break;
                            case 2: decorated = new DecorativePot(decorated); std::cout << "🪴 Added Decorative Pot\n"; break;
                            case 3: decorated = new SpecialArrangement(decorated); std::cout << "💐 Added Special Arrangement\n"; break;
                            default: addingDecor = false; break;
                        }
                    }

                    
              
                   
                    
                    std::cout << "\nSelect payment method:\n1. Credit Card\n2. E-Wallet\n3. EFT\nChoose: ";
                    int pay;
                    while (true) {
                        std::cin >> pay;
                        if (std::cin.fail() || pay < 1 || pay > 3) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number between 1 and 3: ";
                            continue;
                        }
                        break;
                    }
                    PaymentStrategy* strategy = nullptr;
                    if (pay == 1) strategy = &creditCard;
                    else if (pay == 2) strategy = &ewallet;
                    else strategy = &eft;

                    double total = decorated->getPrice() * qty;
                    Order order(&customer, "ORD-" + std::to_string(rand()));
                    Transaction* tx = new Transaction(order.getOrderId(), total, qty);
                    tx->setPaymentStrategy(strategy);
                   if (proxy.buyPlant(selectedPlant, qty)) {
                        order.addTransaction(tx);
                        order.processOrder();
                        balance += total;
                        savedTransactions.push_back(tx);
                         
                        
                        lastPurchasedPlant = selectedPlant;
                        lastPurchasedQuantity = qty;

                        std::cout << "\nPurchased " << qty << " " << decorated->getDescription() << " for R" << total << "\n";
                    } else {
                        delete tx;
                        std::cout << "\nPurchase failed: not enough stock.\n";
                    }

                    inventory->removeStock(selectedPlant, 0);

                    
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
                if (savedTransactions.empty()) {
                    std::cout << "\nNo previous orders found!\n";
                    continue;
                }

                
                    if (!lastPurchasedPlant) {
                        std::cout << "\n❌ Cannot repurchase: No plant information from last order.\n";
                        continue;
                    }
                    
                    
                    int availableQty = inventory->getQuantity(lastPurchasedPlant);
                    if (availableQty < lastPurchasedQuantity) {
                        std::cout << "\n❌ Cannot repurchase: Not enough stock!\n";
                        std::cout << "   Last order: " << lastPurchasedQuantity << " " << lastPurchasedPlant->getDescription() << "\n";
                        std::cout << "   Available: " << availableQty << "\n";
                        continue;
                    }

                
                Transaction* last = savedTransactions.back()->clone();
                std::cout << "\n🔁 Re-purchasing last order...\n";

                
                    if (proxy.buyPlant(lastPurchasedPlant, lastPurchasedQuantity)) {
                
                Customer customer("Walk-in Customer");
                Order order(&customer, "ORD-" + std::to_string(rand()));

                order.addTransaction(last);
                order.processOrder();
                savedTransactions.push_back(last);
                balance += last->getAmount();

                std::cout << "\n✅ Repurchased " << lastPurchasedQuantity << " " 
                                  << lastPurchasedPlant->getDescription() << " successfully!\n";

                
                std::cout << "\n=========================================\n";
                std::cout << "           🧾 REPURCHASE RECEIPT\n";
                std::cout << "=========================================\n";
                std::cout << "Order ID: " << order.getOrderId() << "\n";
                std::cout << "Customer: " << customer.getName() << "\n";
                std::cout << "Item: " << lastPurchasedPlant->getDescription() << "\n";
                std::cout << "Quantity: " << lastPurchasedQuantity << "\n";
                std::cout << "Payment Method: " << last->getPaymentMethod() << "\n";
                std::cout << "-----------------------------------------\n";
                std::cout << std::fixed << std::setprecision(2)
                                  << "Total: R" << last->getAmount() << "\n";
                std::cout << "=========================================\n";
                std::cout << "     🌸 Thank you for shopping again! 🌸\n";
                std::cout << "=========================================\n";
                } else {
                        delete last;
                        std::cout << "\n❌ Repurchase failed: Could not remove stock from inventory.\n";
                        continue;
                    }
                }



                

                else if (cChoice == 4) {
                    if (savedTransactions.empty()) {
                        std::cout << "\nNo receipts to view yet.\n";
                        continue;
                    }

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
                else if (cChoice == 5) {
            std::cout << "\n--- Query Plant ---\n";
            std::cout << "Select plant to query (0 to cancel):\n";
            auto inventoryItems = inventory->getInventoryView();
            if (!inventoryItems.empty()) {
                for (const auto& item : inventoryItems) {
                    auto it = plantMenuOptions.find(item.first->getDescription());
                    if (it != plantMenuOptions.end()) {
                        std::cout << it->second << ". " << item.first->getDescription() << " (Qty: " << item.second << ")\n";
                    }
                }
            }
            
            std::cout<<"99. Custom Plant Query (Queries with No plant)\n";
            int plantChoice;
            while (true) {
                std::cin >> plantChoice;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a number: ";
                    continue;
                }
                break;
            }
            if (plantChoice == 0) continue;

            // Custom query path (no plant)
            if (plantChoice == 99) {
                // clear remaining newline
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::string qtype;
                std::cout << PASTEL_SALMON <<"\nEnter query TYPE (FULL CAPS, e.g. INFO, CARE ROUTINE, STOCK): ";
                std::getline(std::cin, qtype);
                // normalize to uppercase so user's input becomes full caps
                for (auto &ch : qtype) ch = static_cast<char>(std::toupper((unsigned char)ch));

                std::string question;
                std::cout << "Enter your question: "<<RESET;
                std::getline(std::cin, question);

                std::cout << "\n--- Custom Query Received ---\n";
                MiscQueryBuilder m;
                m.setQuestion(question);
                m.setType(qtype);
                Query* query = m.build();

                // Set up chain of responsibility
                for (size_t i = 0; i < hiredStaff.size(); ++i) {
                    if (i < hiredStaff.size() - 1) {
                        hiredStaff[i]->setNext(hiredStaff[i + 1]);
                    } else {
                        hiredStaff[i]->setNext(nullptr);
                    }
                }

                 // Handle query with the first staff in the chain
                if (!hiredStaff.empty()) {
                    std::cout << "\n--- Processing Query ---\n";
                    hiredStaff[0]->handleQuery(query);
                } else {
                    std::cout << "❌ No staff hired to handle this query.\n";
                }

                delete query;
                continue;
            }

            Plant* selectedPlant = nullptr;
            for (const auto& item : inventoryItems) {
                auto it = plantMenuOptions.find(item.first->getDescription());
                if (it != plantMenuOptions.end() && it->second == plantChoice) {
                    selectedPlant = item.first;
                    break;
                }
            }

            if (!selectedPlant) {
                std::cout << "❌ Invalid plant selection!\n";
                continue;
            }

            std::cout << "\nSelect query type:\n"
                      << "1. Describe the plant\n"
                      << "2. What is the care routine for this plant?\n"
                      << "3. Cancel\n"
                      << "Choose: ";
            int queryChoice;
            while (true) {
                std::cin >> queryChoice;
                if (std::cin.fail() || queryChoice < 1 || queryChoice > 4) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input. Please enter a number between 1 and 4: ";
                    continue;
                }
                break;
            }
            if (queryChoice == 3) continue;

            AskQuery queryBuilder;
            Query* query = nullptr;
            std::string queryType;
            std::string requiredStaffType;
            switch (queryChoice) {
                case 1:
                    query = queryBuilder.describe(selectedPlant);
                    queryType = "INFO";
                    requiredStaffType = "Floor Employee";
                    break;
                case 2:
                    query = queryBuilder.careRoutine(selectedPlant);
                    queryType = "CARE ROUTINE";
                    requiredStaffType = "Floor Employee";
                    break;
                default:
                    continue;
            }

            
            bool canHandle = false;
            for (auto* staff : hiredStaff) {
                if (dynamic_cast<FloorEmployee*>(staff) && (queryType == "INFO" || queryType == "CARE ROUTINE")) {
                    canHandle = true;
                    break;
                }
                if (dynamic_cast<FloorManager*>(staff) && queryType == "STOCK") {
                    canHandle = true;
                    break;
                }
                if ((dynamic_cast<SalesEmployee*>(staff) || dynamic_cast<SalesManager*>(staff)) && queryType == "STOCK") {
                    canHandle = true;
                    break;
                }
            }

            if (!canHandle) {
                std::cout << "❌ No " << requiredStaffType << " hired to handle this query. Please hire the appropriate staff.\n";
                delete query;
                continue;
            }

            
            for (size_t i = 0; i < hiredStaff.size(); ++i) {
                if (i < hiredStaff.size() - 1) {
                    hiredStaff[i]->setNext(hiredStaff[i + 1]);
                } else {
                    hiredStaff[i]->setNext(nullptr);
                }
            }

            
            if (!hiredStaff.empty()) {
                std::cout << "\n--- Processing Query ---\n";
                hiredStaff[0]->handleQuery(query);
            } else {
                std::cout << "❌ No staff hired to handle this query.\n";
            }

            delete query;
        }
        
                // Try to Steal Plants (Proxy Demo)
                else if (cChoice == 6) {
                    std::cout << "\n" << PASTEL_MINT << "╔════════════════════════════════════════════╗\n";
                    std::cout << "    🦹 ATTEMPTING TO STEAL PLANTS\n";
                    std::cout << "╚════════════════════════════════════════════╝\n" << RESET;
                    
                    std::cout << "\n" << PASTEL_YELLOW << "⚠️  Shady Customer: \"Let me try to mess with the inventory...\"\n" << RESET;
                    
                    // Show available plants first
                    auto inventoryItems = inventory->getInventoryView();
                    if (inventoryItems.empty()) {
                        std::cout << "\n" << PASTEL_GRAY << "No plants in inventory to steal. Come back later!\n" << RESET;
                        continue;
                    }
                    
                    std::cout << "\n" << PASTEL_CYAN << "Available plants in inventory:\n" << RESET;
                    for (const auto& item : inventoryItems) {
                        auto it = plantMenuOptions.find(item.first->getDescription());
                        if (it != plantMenuOptions.end()) {
                            std::cout << "  " << it->second << ". " << item.first->getDescription() 
                                      << " (Qty: " << item.second << ")\n";
                        }
                    }
                    
                    std::cout << PASTEL_SALMON << "1. Try to add unauthorized plants to inventory\n" << RESET;
                    std::cout << PASTEL_SALMON << "2. Try to steal plants from inventory\n" << RESET;
                    std::cout << PASTEL_GRAY << "3. Cancel\n" << RESET;
                    std::cout << PASTEL_MINT << "Choice: " << RESET;
                    
                    int stealChoice;
                    while (true) {
                        std::cin >> stealChoice;
                        if (std::cin.fail() || stealChoice < 1 || stealChoice > 3) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter 1-3: ";
                            continue;
                        }
                        break;
                    }
                    
                    if (stealChoice == 3) continue;
                    
                    // Select a plant
                    std::cout << "\nSelect plant number: ";
                    int plantChoice;
                    while (true) {
                        std::cin >> plantChoice;
                        if (std::cin.fail()) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid input. Please enter a number: ";
                            continue;
                        }
                        break;
                    }
                    
                    Plant* selectedPlant = nullptr;
                    for (const auto& item : inventoryItems) {
                        auto it = plantMenuOptions.find(item.first->getDescription());
                        if (it != plantMenuOptions.end() && it->second == plantChoice) {
                            selectedPlant = item.first;
                            break;
                        }
                    }
                    
                    if (!selectedPlant) {
                        std::cout << PASTEL_SALMON << "❌ Invalid plant selection!\n" << RESET;
                        continue;
                    }
                    
                    std::cout << "\nEnter quantity: ";
                    int qty;
                    while (true) {
                        std::cin >> qty;
                        if (std::cin.fail() || qty <= 0) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Invalid quantity. Please enter a positive number: ";
                            continue;
                        }
                        break;
                    }
                    
                    std::cout << "\n" << PASTEL_YELLOW << "═══════════════════════════════════════════\n" << RESET;
                    std::cout << PASTEL_PINK << "        🛡️  PROTECTION IN ACTION 🛡️\n" << RESET;
                    std::cout << PASTEL_YELLOW << "═══════════════════════════════════════════\n" << RESET;
                    
                    if (stealChoice == 1) {
                        std::cout << "\n" << PASTEL_SALMON << "Customer attempting to add unauthorized ("
                                  << selectedPlant->getDescription() << ", " << qty << ")\n" << RESET;
                        std::cout << PASTEL_CYAN << "   Response:\n" << RESET;
                        std::cout << "   → ";
                        proxy.addStock(selectedPlant, qty);

                        std::cout << "\n" << PASTEL_SALMON << "🚨 ALERT! ALERT! Unauthorized access detected! 🚨\n" << RESET;
                        std::cout << PASTEL_BLUE << "👮 Police: \"FREEZE! You're under arrest for attempting inventory fraud!\"\n" << RESET;
                        std::cout << PASTEL_YELLOW << "🦹 Customer: \"Wait, I was just testing...\"\n" << RESET;
                        std::cout << PASTEL_BLUE << "👮 Police: \"Tell it to the judge! You have the right to remain silent...\"\n" << RESET;
                        std::cout << PASTEL_SALMON << "🚔 *HANDCUFFS CLICK* 🚔\n" << RESET;
                        
                    } else if (stealChoice == 2) {
                        std::cout << "\n" << PASTEL_SALMON << "Customer attempting to steal (" 
                                  << selectedPlant->getDescription() << ", " << qty << ")\n" << RESET;
                        std::cout << PASTEL_CYAN << "   Response:\n" << RESET;
                        std::cout << "   → ";
                        proxy.removeStock(selectedPlant, qty);
                        
                        std::cout << "\n" << PASTEL_SALMON << "🚨 SECURITY BREACH! Theft attempt detected! 🚨\n" << RESET;
                        std::cout << PASTEL_BLUE << "👮 Police: \"STOP RIGHT THERE! Hands where I can see them!\"\n" << RESET;
                        std::cout << PASTEL_YELLOW << "🦹 Customer: \"It was just a prank bro!\"\n" << RESET;
                        std::cout << PASTEL_BLUE << "👮 Police: \"Pranks are for YouTube, not our nursery! You're coming with us!\"\n" << RESET;
                        std::cout << PASTEL_SALMON << "🚓 *WEE-OOO WEE-OOO* Police car arrives 🚓\n" << RESET;
                        
                    }
                    
                    std::cout << "\n" << PASTEL_GRAY << "Press Enter to continue..." << RESET;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                }
            }
        }

        
        else if (roleChoice == 3) {
            std::cout << "\n--- Simulating a Day at Plantopia ---\n";
            simulateDay(growingPlants, inventory, hiredStaff);
        }
    }

    
    for (auto s : hiredStaff) delete s;
    for (auto tx : savedTransactions) delete tx;

    std::cout << "\n🌱 Thank you for visiting Plantopia! 🌱\n";
    return 0;
}

// CHECKLIST:
// MEMENTO
// DECORATOR
// STRATEGY
// STATE
// FACTORY METHOD
// TEMPLATE METHOD
// ABSTRACT FACTORY

// PROXY
// OBSERVER
// CHAIN OF RESPONSIBILITY
// SINGLETON
// COMMAND
// BUILDER

// NOT IMPLEMENTED
// FACADE


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