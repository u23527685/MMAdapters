#include "PlantInventory.h"
#include "InventoryObserver.h"
#include <iostream>
using namespace std;

// --- Concrete Observers for testing ---
class StaffObserver : public InventoryObserver {
public:
    void update() override {
        cout << "[StaffObserver] Received stock update notification." << endl;
    }
};

class ManagerObserver : public InventoryObserver {
public:
    void update() override {
        cout << "[ManagerObserver] Received stock update notification." << endl;
    }
};

// --- Main test ---
int main() {
    cout << "=== Testing Observer Pattern ===" << endl;

    // Create subject
    PlantInventory inventory;

    // Create observers
    StaffObserver staff1;
    ManagerObserver manager1;

    // Attach observers
    cout << "\n[TEST] Attaching observers..." << endl;
    inventory.attach(&staff1);
    inventory.attach(&manager1);

    // Notify all
    cout << "\n[TEST] Updating stock (both should receive update)..." << endl;
    inventory.updateStock();

    // Detach one
    cout << "\n[TEST] Detaching ManagerObserver..." << endl;
    inventory.detach(&manager1);

    // Notify again
    cout << "\n[TEST] Updating stock again (only Staff should receive update)..." << endl;
    inventory.updateStock();

    cout << "\n=== Observer Pattern Test Complete ===" << endl;
    return 0;
}
