
// #include "Plant.h"
// #include "PlantInventory.h"
// #include "Customer.h"
// #include "InventoryProxy.h"
// #include "SalesFloorObserver.h"
// #include "FloorEmployee.h"
// #include <iostream>
// #include <stdexcept>

// int main() {
//     Plant* lavender = new Plant(19.99, "Lavender");
//     lavender->setCurrentWater(5);
//     lavender->setCurrentSunlight(5);
//     lavender->setCurrentNutrients(5);

//     PlantInventory* inventory = PlantInventory::getInstance();
//     SalesFloorObserver* salesFloor = new SalesFloorObserver(inventory);
//     FloorEmployee* john = new FloorEmployee("John");
//     salesFloor->attachStaff(john);
//     inventory->addStock(lavender, 10);

//     salesFloor->update();

//     InventoryProxy proxy(salesFloor);
//     std::cout << "Initial inventory:\n";
//     proxy.displayAvailablePlants();

//     Customer customer("Alice");
//     customer.buyPlant(proxy, lavender, 10);

//     salesFloor->update();
//     std::cout << "Inventory after purchase:\n";
//     proxy.displayAvailablePlants();

//     proxy.addStock(lavender, 5);

//     //delete lavender;
//     return 0;
// }
