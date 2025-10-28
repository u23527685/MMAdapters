#include <iostream>
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
#include "AddStock.h"
#include "RemoveStock.h"
#include "PlantStock.h"
#include "PlantInventory.h"
#include "InventoryObserver.h"
#include "StaffObserver.h"
#include "SalesFloorObserver.h"
using namespace std;

int main() {
    std::cout << "=== Transaction System Test ===\n\n";

    Transaction tx("ORD-1001", 25.50, 2);
    tx.processPayment();

    std::cout << "\n--- Testing Credit Card Payment ---\n";
    CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
    tx.setPaymentStrategy(&creditCard);
    tx.processPayment();

    std::cout << "\n--- Testing E-Wallet Payment ---\n";
    EWalletPaymentStrategy ewallet("wallet123");
    tx.setPaymentStrategy(&ewallet);
    tx.processPayment();

    std::cout << "\n--- Testing EFT Payment ---\n";
    EFTPaymentStrategy eft("9876543210");
    tx.setPaymentStrategy(&eft);
    tx.processPayment();

    std::cout << "\n=== Testing Transaction Snapshots (Memento Pattern) ===\n";
    TransactionHistory history;
    history.addSnapshot(tx.createSnapshot());

    std::cout << "\nUpdating Transaction...\n";
    tx.setTransaction("ORD-1002", 40.75, 3);
    tx.processPayment();
    history.addSnapshot(tx.createSnapshot());

    std::cout << "\nUpdating Transaction again...\n";
    tx.setTransaction("ORD-1003", 15.99, 5);
    tx.processPayment();
    history.addSnapshot(tx.createSnapshot());

    std::cout << "\n--- Restoring Previous Snapshot ---\n";
    tx.restoreSnapshot(history.getSnapshot(1));
    tx.processPayment();

    std::cout << "\n--- Restoring Original Snapshot ---\n";
    tx.restoreSnapshot(history.getSnapshot(0));
    tx.processPayment();

    std::cout << "\nTransaction history count: " << history.getHistorySize() << std::endl;

    std::cout << "\n=== Plant Decorator Test ===\n\n";

    std::vector<Plant*> plants;
    plants.push_back(new GiftWrap(new BasePlant()));
    plants.push_back(new DecorativePot(new GiftWrap(new BasePlant())));
    plants.push_back(new SpecialArrangement(new DecorativePot(new GiftWrap(new BasePlant()))));

    for (const auto& plant : plants) {
        std::cout << plant->getDescription() << " | R" << plant->getPrice() << std::endl;
    }
    for (auto& plant : plants) {
        delete plant;
    }

    cout << "\n============================================================\n";
    cout << "TESTING COMMAND AND OBSERVER PATTERNS\n";
    cout << "============================================================\n";

    PlantStock stock;
    stock.addStock("Rose", 20);
    stock.addStock("Tulip", 15);
    stock.addStock("Sunflower", 10);

    cout << "DIRECT REMOVESTOCK() CALLS" << endl;
    stock.removeStock("Rose", 5);
    stock.removeStock("Lily", 5);

    cout << "TESTING EDGE CASES" << endl;
    stock.addStock("Daisy", 0);
    stock.addStock("Orchid", -5);
    stock.removeStock("Tulip", 100);

    stock.displayInventory();

    cout << "------------------------------------------------------------------" << endl;

    cout << "TESTING ADDSTOCK COMMAND" << endl;
    AddStock addCmd1(&stock, "Lavender", 30);
    addCmd1.execute();

    cout << "TESTING REMOVESTOCK COMMAND" << endl;
    RemoveStock removeCmd1(&stock, "Lavender", 10);
    removeCmd1.execute();

    stock.displayInventory();

    cout << "------------------------------------------------------------------" << endl;

    cout << "CREATING COMMAND VECTOR" << endl;
    vector<StockCommand*> commandList;
    commandList.push_back(new AddStock(&stock, "Lily", 30));
    commandList.push_back(new AddStock(&stock, "Peony", 25));
    commandList.push_back(new RemoveStock(&stock, "Rose", 10));
    commandList.push_back(new RemoveStock(&stock, "Carnations", 22));
    commandList.push_back(new RemoveStock(&stock, "Gardenia", 3));

    cout << "EXECUTE COMMANDS IN LIST" << endl;
    for (auto* cmd : commandList)
        cmd->execute();

    stock.displayInventory();

    cout << "CLEANING COMMAND LIST" << endl;
    for (auto* cmd : commandList)
        delete cmd;
    cout << "[Test] All commands deleted successfully." << endl;

    cout << "SEQUENTIAL ADD AND REMOVE OPERATIONS" << endl;
    AddStock addHydrangea(&stock, "Hydrangea", 40);
    addHydrangea.execute();
    
    RemoveStock removeHydrangea1(&stock, "Hydrangea", 10);
    removeHydrangea1.execute();
    
    AddStock addMoreHydrangea(&stock, "Hydrangea", 15);
    addMoreHydrangea.execute();
    
    RemoveStock removeHydrangea2(&stock, "Hydrangea", 5);
    removeHydrangea2.execute();
    
    stock.displayInventory();

    cout << "------------------------------------------------------------------" << endl;
    cout << "------------------------------------------------------------------" << endl;

    cout << "TESTING CREATING INVENTORY AND OBSERVERS" << endl;

    PlantInventory inventory;
    StaffObserver staff1;

    inventory.attach(&staff1);
    inventory.updateStock();

    StaffObserver staff2;
    SalesFloorObserver salesFloor;

    inventory.attach(&staff2);
    inventory.attach(&salesFloor);

    inventory.updateStock();

    inventory.detach(&staff1);
    inventory.updateStock();

    StaffObserver staff3;
    inventory.detach(&staff3);

    inventory.attach(&staff1);
    inventory.updateStock();

    inventory.detach(&staff1);
    inventory.detach(&staff2);
    inventory.detach(&salesFloor);

    inventory.updateStock();

    cout << "------------------------------------------------------------------" << endl;
    cout << "------------------------------------------------------------------" << endl;

    cout << "INTEGRATING SYSTEM" << endl;

    PlantInventory inventory2;
    PlantStock stock2;
    StaffObserver manager;
    SalesFloorObserver display;

    inventory2.attach(&manager);
    inventory2.attach(&display);

    AddStock addRoses(&stock2, "Rose", 50);
    addRoses.execute();
    inventory2.updateStock();

    RemoveStock sellRoses(&stock2, "Rose", 10);
    sellRoses.execute();
    inventory2.updateStock();

    AddStock addTulips(&stock2, "Tulip", 30);
    addTulips.execute();
    inventory2.updateStock();

    stock2.displayInventory();

    cout << "CREATING BATCH COMMAND LIST" << endl;

    vector<StockCommand*> batchCommands;
    batchCommands.push_back(new AddStock(&stock2, "Daisy", 40));
    batchCommands.push_back(new AddStock(&stock2, "Sunflower", 35));
    batchCommands.push_back(new AddStock(&stock2, "Lily", 28));
    batchCommands.push_back(new RemoveStock(&stock2, "Rose", 15));

    cout << "EXECUTE BATCH AND NOTIFY AFTER EACH" << endl;

    for (size_t i = 0; i < batchCommands.size(); i++) {
        cout << "\nExecuting command " << (i + 1) << "/" << batchCommands.size() << ":" << endl;
        batchCommands[i]->execute();
        inventory2.updateStock();
    }

    stock2.displayInventory();

    for (auto* cmd : batchCommands) {
        delete cmd;
    }
    cout << "[Test] Batch commands deleted successfully." << endl;

    cout << "------------------------------------------------------------------" << endl;
    cout << "------------------------------------------------------------------" << endl;

    cout << "EDGE CASES AND ERROR HANDLING" << endl;

    AddStock invalidAdd(&stock2, "Orchid", -10);
    invalidAdd.execute();
    
    RemoveStock invalidRemove(&stock2, "Tulip", 0);
    invalidRemove.execute();
    
    RemoveStock removeTooMany(&stock2, "Daisy", 1000);
    removeTooMany.execute();
    
    RemoveStock removeNonExistent(&stock2, "Cactus", 5);
    removeNonExistent.execute();
    
    stock2.displayInventory();

    cout << "------------------------------------------------------------------" << endl;
    cout << "------------------------------------------------------------------" << endl;

    cout << "TESTING NOTFIY() WITHOUT UPDATESTOCK()" << endl;

    PlantInventory inventory3;
    StaffObserver staff4;
    SalesFloorObserver floor2;
    
    inventory3.attach(&staff4);
    inventory3.attach(&floor2);
    
    inventory3.notify();
    inventory3.notify();
    inventory3.notify();
    return 0;
}
