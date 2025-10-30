displayMenu()
void displayMenu() { ... }

→ Prints the main game menu:

1. Buy Plants
2. Hire Staff
3. Simulate Day
4. View Status
5. Quit


displayPlantBuyOptions()
→ Shows which plants you can buy and their wholesale prices (what you pay to stock them).


displayHireOptions()
→ Shows which staff you can hire and their hiring cost.

3. main() Function – Game Setup
srand(static_cast<unsigned>(time(0)));
→ Seeds the random number generator so you get different results each run.

Inventory & Observer Setup
PlantInventory* inventory = PlantInventory::getInstance();
SalesFloorObserver* salesFloor = new SalesFloorObserver(inventory);


→ PlantInventory is a Singleton → only one inventory exists.
→ SalesFloorObserver watches the inventory and prints updates when stock changes.

Plant Prototypes (Factory Pattern)
Rose* redRose = new Rose(25.99, "Beautiful Red Rose");
redRose->setCategory("Sunny");
redRose->setMaxWater(100);
// ... etc.


→ These are prototype objects — you don’t sell these directly.
→ You clone them into inventory using addStock(plant, qty).


std::map<int, std::pair<Plant*, double>> plantOptions = {
    {1, {redRose, 10.0}},
    {2, {yellowRose, 9.0}},
    // ...
};


→ Maps menu choice → {prototype plant, buy price}

Game State Variables
double money = 1000.0;
std::vector<Staff*> hiredStaff;
std::map<Plant*, PlantLifeCycle*> lifecycles;
FloorEmployee* floorEmployee = nullptr;
// ... other staff pointers


→ Tracks:
Your money
Who you’ve hired
Lifecycle of each plant type
Specific staff instances (only one of each type)

CreditCardPaymentStrategy creditCard("...");
EWalletPaymentStrategy ewallet("...");
EFTPaymentStrategy eft("...");


→ Strategy Pattern for different payment methods.
AskQuery askQuery;

→ Builder Pattern to create different types of customer questions.

bool running = true;
→ Main game loop control.

4. Main Game Loop
while (running) {
    displayMenu();
    int choice;
    std::cin >> choice;
    switch (choice) { ... }
}

5. Case 1: Buy Plants
case 1: {
    displayPlantBuyOptions();
    int plantChoice;
    std::cin >> plantChoice;
    if (plantChoice == 0) break;
    // ...
    Plant* plant = plantOptions[plantChoice].first;
    double buyPrice = plantOptions[plantChoice].second;
    int qty;
    std::cin >> qty;
    double cost = buyPrice * qty;
    if (money < cost) { ... break; }
    money -= cost;
    inventory->addStock(plant, qty);


→ You spend money to add plants to inventory.



if (lifecycles.find(plant) == lifecycles.end()) {
    PlantLifeCycle* cycle = new PlantLifeCycle(plant, new SeedState(), ...);
    lifecycles[plant] = cycle;
    plant->setCurrentWater(plant->getMaxWater());
    // ...
    for (auto staff : hiredStaff) cycle->attach(staff);
}

→ First time you buy a plant type:
Create a lifecycle starting in SeedState
Set full health (water, sun, nutrients)
Attach all current staff as observers (they’ll care for it)


6. Case 2: Hire Staff
case 2: {
    displayHireOptions();
    int staffChoice;
    std::cin >> staffChoice;
    // ...
    switch (staffChoice) {
        case 1: floorEmployee = new FloorEmployee(name); hireCost = 200; break;
        // ...
    }
    if (money < hireCost) { ... }
    money -= hireCost;
    hiredStaff.push_back(newStaff);
    salesFloor->attachStaff(newStaff);
    for (auto& pair : lifecycles) pair.second->attach(newStaff);


→ Hire one staff of each type.

→ Attach to:
salesFloor → for inventory updates
All plant lifecycles → so they can care for plants

Chain of Responsibility Setup
Staff* chainStart = nullptr;

if (floorEmployee) {
    chainStart = floorEmployee;
    Staff* nxt = floorManager ? floorManager : salesEmployee ? ...;
    floorEmployee->setNext(nxt);
}
// ... same for others


→ Builds a chain:
textFloorEmployee → FloorManager → SalesEmployee → SalesManager
→ Queries go to the first available staff, then passed up if they can’t handle it.


7. Case 3: Simulate Day
std::cout << "\nSimulating a day...\n";
Decay Plant Health
cppfor (auto& pair : lifecycles) {
    Plant* p = pair.first;
    double decay = rand() % 20 + 10.0;
    p->setCurrentWater(std::max(0.0, p->getCurrentWater() - decay));
    // ... same for sun, nutrients
    cycle->isHealthy();
}

→ Each day, plants lose water, sun, nutrients.

→ isHealthy() triggers:
State evaluation
Care routine (if staff are attached)
Possible state change (Seed → Seedling → Mature → Distressed → Withered)


Generate Customers
cppint numCustomers = rand() % 5 + 1;

→ 1–5 customers per day.

Staff* chainStart = floorEmployee ? static_cast<Staff*>(floorEmployee) : ...;

→ Find first staff in chain to handle queries.

Customer Actions (50/50 chance)
Action 0: Ask Query
Query* q = askQuery.careRoutine(randPlant);
// or describe(), or stockInfo()
chainStart->handleQuery(q);

→ Customer asks a question → passed through Chain of Responsibility.

Action 1: Buy Plant
Plant* buyPlant = ...;
if (state == "Withered" || "Distressed") continue;  // won't buy sick plants
int buyQty = rand() % 3 + 1;

→ Pick a healthy plant from inventory.

Plant* decorated = new BasePlant(...);
if (rand() % 4 == 0) decorated = new GiftWrap(decorated);
// ... etc.

→ Decorator Pattern: 25% chance to add gift wrap, pot, or arrangement.

Order order(&customer, "ORD-...");
Transaction* tx = new Transaction(order.getOrderId(), totalPrice, buyQty);
tx->setPaymentStrategy(&creditCard);  // or ewallet, eft
order.addTransaction(tx);
order.processOrder();

→ Strategy Pattern for payment.
→ Order aggregates transactions.

cppinventory->removeStock(buyPlant, buyQty);
money += totalPrice;

→ You earn money from sale.

delete decorated;
→ Clean up decorated plant (destructors delete inner ones if virtual).

8. Case 4: View Status
std::cout << "Current Money: $" << money << "\n";
std::cout << "Hired Staff:\n";
salesFloor->displayAvailablePlants();
std::cout << "Plant States:\n";
for (auto& pair : lifecycles) {
    std::cout << p->getDescription() << ":\n";
    std::cout << "  State: " << cycle->getState() << "\n";
    std::cout << "  Water: " << p->getCurrentWater() << "/" << p->getMaxWater() << "\n";
    // ...
}
→ Full game state:

Money
Staff
Inventory
Plant health & lifecycle state


9. Case 5: Quit
running = false;
→ Exit loop.

10. Cleanup (Memory Management)
cppdelete salesFloor;
for (auto staff : hiredStaff) delete staff;
for (auto& pair : lifecycles) delete pair.second;
delete redRose; delete yellowRose; // ... etc.
→ Manual memory cleanup (since using new).
→ Prevents memory leaks.
cppstd::cout << "Game ended.\n";
return 0;