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

// --- Pastel Color Palette (24-bit Truecolor ANSI) ---
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

// Helper: get human-readable role for a Staff pointer
static std::string getStaffRole(Staff* s) {
    if (!s) return "Unknown";
    if (dynamic_cast<FloorEmployee*>(s)) return "Floor Employee";
    if (dynamic_cast<FloorManager*>(s)) return "Floor Manager";
    if (dynamic_cast<SalesEmployee*>(s)) return "Sales Employee";
    if (dynamic_cast<SalesManager*>(s)) return "Sales Manager";
    return "Staff";
}

// Simulate a day for plants
void simulateDay(std::vector<std::unique_ptr<Plant>>& growingPlants,
                PlantInventory* inventory, std::vector<Staff*>& staff) {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════╗\n";
    std::cout << "📅   SIMULATING A NEW DAY IN THE NURSERY\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n\n";


    int watered = 0, fertilized = 0, matured = 0, died = 0;

    // Debug: Print inventory state before simulation
    std::cout << "🔍 INVENTORY BEFORE SIMULATION:\n";
    auto inventoryItems = inventory->getInventoryView();
    if (inventoryItems.empty()) {
        std::cout << "Inventory is empty!\n";
    } else {
        for (const auto& item : inventoryItems) {
            std::cout << item.first->getDescription() << " (Qty: " << item.second << ", Ptr: " << item.first << ")\n";
        }
    }

    for (size_t i = 0; i < growingPlants.size(); ) {
        Plant* plant = growingPlants[i].get();
        if (!plant->getState()) {
            std::cout << "Error: Plant " << plant->getName() << " has no state!\n";
            growingPlants.erase(growingPlants.begin() + i);
            died++;
            continue;
        }

        // Debug: Print plant being processed
        std::cout << "Debug: Processing plant: " << plant->getDescription() << " (Ptr: " << plant << ")\n";

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
            Plant* targetPlant = nullptr;
            for (auto& item : inventoryItems) {
                if (item.first->getDescription() == plant->getDescription()) {
                    targetPlant = item.first;
                    break;
                }
            }

            if (targetPlant) {
                // Increment the quantity of the existing plant in inventory
                inventory->addStock(targetPlant, 1);
                std::cout << "Debug: Incremented " << targetPlant->getDescription() << " to qty " << inventory->getQuantity(targetPlant) << "\n";
            } else {
                std::cout << "Warning: No matching plant found in inventory for " << plant->getDescription() << ". Adding new plant.\n";
                // Create a new plant instance for the inventory
                std::unique_ptr<Plant> newPlant;
                if (plant->getDescription() == "Red Rose") {
                    newPlant = std::make_unique<Rose>(10.0, "Red Rose");
                    newPlant->setCategory("Sunny");
                } else if (plant->getDescription() == "Yellow Rose") {
                    newPlant = std::make_unique<Rose>(9.0, "Yellow Rose");
                    newPlant->setCategory("Shade");
                } else if (plant->getDescription() == "Oak Tree") {
                    newPlant = std::make_unique<Oak>(7.0, "Oak Tree");
                    newPlant->setCategory("Temperate");
                }
                if (newPlant) {
                    newPlant->setState(std::make_unique<MatureState>());
                    // Add to inventory and transfer ownership
                    Plant* rawPlant = newPlant.release();
                    inventory->addStock(rawPlant, 1);
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

//     // Debug: Print inventory state after simulation
    std::cout << "\n📦 INVENTORY AFTER SIMULATION:\n";
    inventoryItems = inventory->getInventoryView();
    if (inventoryItems.empty()) {
        std::cout << "Debug: Inventory is empty!\n";
    } else {
        for (const auto& item : inventoryItems) {
            std::cout << "Debug: " << item.first->getDescription() << " (Qty: " << item.second << ", Ptr: " << item.first << ")\n";
        }
    }


//     std::cout << "\n✅ Daily Summary:\n";
    // Summary
    std::cout <<"\n═══════════════════════════════════════════\n";
    std::cout << "✅ DAILY SUMMARY\n";
    std::cout<<  "═══════════════════════════════════════════\n";
    std::cout << PASTEL_AQUA      << "💧 Watered:       " << watered    << "\n" << RESET;
    std::cout << PASTEL_MINT      << "🌿 Fertilized:    " << fertilized << "\n" << RESET;
    std::cout << PASTEL_PINK      << "🌸 Matured:       " << matured    << "\n" << RESET;
    std::cout << PASTEL_GRAY      << "💀 Withered:      " << died       << "\n" << RESET;

    std::cout << "═══════════════════════════════════════════\n";
    std::cout << "🌱 End of day processing complete.\n\n";
   
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
    auto seed = createSeedPlant(1); // Red Rose seed
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
        growingPlants.clear(); // Clear growing plants to simulate maturity
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
        double total = decorated->getPrice() * 1; // 1 Red Rose with Gift Wrap
        if (inventory->removeStock(selectedPlant, 1)) { // Check if removal succeeds
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

    // Core systems
    PlantInventory* inventory = PlantInventory::getInstance();
    std::unique_ptr<SalesFloorObserver> salesFloor = std::make_unique<SalesFloorObserver>(inventory);

    // Payment strategies
    CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
    EWalletPaymentStrategy ewallet("wallet123");
    EFTPaymentStrategy eft("9876543210");

    // Proxy
    InventoryProxy proxy(salesFloor.get());

    // Initialize inventory with plants
    auto redRose = std::make_unique<Rose>(10.0, "Red Rose");
    auto yellowRose = std::make_unique<Rose>(9.0, "Yellow Rose");
    auto oakTree = std::make_unique<Oak>(7.0, "Oak Tree");

    // Store plants in inventory (use raw pointers, ownership remains with unique_ptr)
    inventory->addStock(redRose.get(), 0);
    inventory->addStock(yellowRose.get(), 0);
    inventory->addStock(oakTree.get(), 0);

    // Debug: Verify initial inventory
    std::cout << "Debug: Initial inventory state:\n";
    auto inventoryItems = inventory->getInventoryView();
    if (inventoryItems.empty()) {
        std::cout << "Debug: Initial inventory is empty!\n";
    } else {
        for (const auto& item : inventoryItems) {
            std::cout << "Debug: " << item.first->getDescription() << " (Qty: " << item.second << ", Ptr: " << item.first << ")\n";
        }
    }

    // Map plant descriptions to menu options for user input
    std::map<std::string, int> plantMenuOptions = {
        {"Red Rose", 1},
        {"Yellow Rose", 2},
        {"Oak Tree", 3}
    };

    // Memento / transactions
    std::vector<Transaction*> savedTransactions;

    // Staff and growing plants
    std::vector<Staff*> hiredStaff;
    std::vector<std::unique_ptr<Plant>> growingPlants;

    double balance = 1000.0;
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

        // --- Staff Menu ---
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

                // Hire Staff
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
                    std::string name = "Staff_" + std::to_string(hiredStaff.size() + 1);
                    switch (type) {
                        case 1: newStaff = new FloorEmployee(name); cost = 200; break;
                        case 2: newStaff = new FloorManager(name); cost = 400; break;
                        case 3: newStaff = new SalesEmployee(name); cost = 300; break;
                        case 4: newStaff = new SalesManager(name); cost = 500; break;
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

                // View Staff
                else if (sChoice == 2) {
                    std::cout << "\n--- Hired Staff ---\n";
                    if (hiredStaff.empty()) std::cout << "None yet.\n";
                    else {
                        for (auto s : hiredStaff) {
                            std::cout << "- " << s->getName() << " (" << getStaffRole(s) << ")\n";
                        }
                    }
                }

                // Buy seeds
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

                        // Exit the loop if the user chooses 4
                        if (type == 4) {
                            std::cout << "Returning to staff menu.\n";
                            break; // Exit the seed selection loop
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
                            continue; // Restart the loop to re-show seed options
                        }

                        for (int i = 0; i < qty; ++i) {
                            growingPlants.push_back(createSeedPlant(type));
                        }

                        std::cout << "✅ Purchased " << qty << " seeds and added to nursery. (for R" << totalCost << ")\n";
                        balance -= totalCost;
                        std::cout << "Current Balance: R" << std::fixed << std::setprecision(2) << balance << "\n";
                    }
                }

                // View Nursery Inventory

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
                        for (const auto& item : inventoryItems) {
                            auto it = plantMenuOptions.find(item.first->getDescription());
                            if (it != plantMenuOptions.end()) {
                                std::cout << PASTEL_GREEN << it->second << ". " << item.first->getDescription() << RESET
                                        << " - R" << PASTEL_YELLOW << std::fixed << std::setprecision(2)
                                        << item.first->getPrice() << RESET
                                        << " (Qty: " << PASTEL_PURPLE << item.second << RESET << ")\n";
                            }
                        }
                    }
                }

                // View Staff Communications (Observer Pattern Demo)
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
                    proxy.displayAvailablePlants();
                    
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                }
            }
        }

        // --- Customer Menu ---
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
            std::cout << PASTEL_SALMON   << "6. Back\n"                                << RESET;

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

                if (cChoice == 6) break;

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
                    // Show available plant options first so customer can see numbers
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

                    // Find the plant corresponding to the user's choice
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

                    // Decorate plant
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

                    // If no decorations added
              
                   
                    // Payment
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
                        std::cout << "\nPurchased " << qty << " " << decorated->getDescription() << " for R" << total << "\n";
                    } else {
                        delete tx;
                        std::cout << "\nPurchase failed: not enough stock.\n";
                    }

                    inventory->removeStock(selectedPlant, 0);

                    // Print a neat receipt
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

                // Retrieve last saved transaction (Memento)
                Transaction* last = savedTransactions.back()->clone();
                std::cout << "\n🔁 Re-purchasing last order...\n";

                int quantity = last->getQuantity();

                // Rebuild decorated plant using decorations stored in the Memento
                Plant* decorated = new BasePlant(0.0, "Plant"); // placeholder
                for (const auto& decor : last->getDecorations()) {
                    if (decor == "GiftWrap") decorated = new GiftWrap(decorated);
                    else if (decor == "DecorativePot") decorated = new DecorativePot(decorated);
                    else if (decor == "SpecialArrangement") decorated = new SpecialArrangement(decorated);
                }

                // Execute purchase using the state from Memento
                Customer customer("Walk-in Customer");
                Order order(&customer, "ORD-" + std::to_string(rand()));

                order.addTransaction(last);
                order.processOrder();
                savedTransactions.push_back(last);
                balance += last->getAmount();

                // REPURCHASE RECEIPT
                std::cout << "\n=========================================\n";
                std::cout << "           🧾 REPURCHASE RECEIPT\n";
                std::cout << "=========================================\n";
                std::cout << "Order ID: " << order.getOrderId() << "\n";
                std::cout << "Customer: " << customer.getName() << "\n";
                std::cout << "Item: " << decorated->getDescription() << "\n";
                std::cout << "Payment Method: " << last->getPaymentMethod() << "\n";
                std::cout << "-----------------------------------------\n";

                // 🔹 Call your existing Transaction::getDetails()
                
                std::cout << "=========================================\n";
                std::cout << "     🌸 Thank you for shopping again! 🌸\n";
                std::cout << "=========================================\n";

                delete decorated;
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
            if (inventoryItems.empty()) {
                std::cout << "No plants available to query.\n";
                continue;
            }
            for (const auto& item : inventoryItems) {
                auto it = plantMenuOptions.find(item.first->getDescription());
                if (it != plantMenuOptions.end()) {
                    std::cout << it->second << ". " << item.first->getDescription() << " (Qty: " << item.second << ")\n";
                }
            }
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

            // Check if any staff can handle the query
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