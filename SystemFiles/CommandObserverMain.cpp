#include "AddStock.h"
#include "RemoveStock.h"
#include "PlantStock.h"
#include "PlantInventory.h"
#include "InventoryObserver.h"
#include <iostream>
#include <vector>
using namespace std;

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

int main() {
    cout << "=== Testing PlantStock and Command Pattern ===" << endl;

    PlantStock stock;

    cout << "\n[TEST] Directly calling PlantStock methods:" << endl;
    stock.addStock("Rose", 20);
    stock.removeStock("Lily", 5);

    cout << "\n[TEST] Creating Command objects..." << endl;
    addStock addCmd1(&stock, "Tulip", 15);
    removeStock removeCmd1(&stock, "Tulip", 5);

    cout << "\n[TEST] Executing commands individually:" << endl;
    addCmd1.execute();
    removeCmd1.execute();

    cout << "\n[TEST] Executing a sequence of commands:" << endl;
    vector<StockCommand*> commandList;
    commandList.push_back(new addStock(&stock, "Lavender", 30));
    commandList.push_back(new addStock(&stock, "Sunflower", 25));
    commandList.push_back(new removeStock(&stock, "Lavender", 10));

    for (auto* cmd : commandList) {
        cmd->execute();
    }

    for (auto* cmd : commandList) {
        delete cmd;
    }

    cout << "\n=== Command Pattern Tests Complete ===" << endl;

    cout << "\n\n=== Testing Observer Pattern ===" << endl;

    PlantInventory inventory;

    StaffObserver staff1;
    ManagerObserver manager1;

    cout << "\n[TEST] Attaching observers..." << endl;
    inventory.attach(&staff1);
    inventory.attach(&manager1);

    cout << "\n[TEST] Updating stock (both should receive update)..." << endl;
    inventory.updateStock();

    cout << "\n[TEST] Detaching ManagerObserver..." << endl;
    inventory.detach(&manager1);

    cout << "\n[TEST] Updating stock again (only Staff should receive update)..." << endl;
    inventory.updateStock();

    cout << "\n=== Observer Pattern Test Complete ===" << endl;

    cout << "\n=== ALL TESTS COMPLETED SUCCESSFULLY ===" << endl;
    return 0;
}
