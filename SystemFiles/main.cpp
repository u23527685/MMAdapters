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
#include "Customer.h"
#include "Order.h"
#include "Staff.h"

#include "Plant.h"
#include "PlantLifeCycle.h"
#include "SeedState.h"
#include "PlantCareRoutine.h"

using namespace std;

int main() {
// C&S main code
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

 
    std::cout << "\n=== Customer and Order Test ===\n\n";

    Customer customer("Alice Green");

    Order order1(&customer, "ORD-CUST-2001");

    Transaction* t1 = new Transaction("ORD-CUST-2001", 100.00, 1);
    Transaction* t2 = new Transaction("ORD-CUST-2001", 250.00, 3);

    t1->setPaymentStrategy(&creditCard);
    t2->setPaymentStrategy(&ewallet);

    order1.addTransaction(t1);
    order1.addTransaction(t2);

    order1.processOrder();

    order1.displayOrderDetails();

 
    customer.placeOrder(order1);

    customer.viewOrders();

    Staff staff;
    customer.makeQuery(staff, "Can I add a gift wrap to my next order?");
  
  
  
  
  
  
  
  
  // Greenhouse testing code


    Plant* myPlant = new Plant("Lavender");
    myPlant->setCurrentWater(5);
    myPlant->setCurrentSunlight(5);
    myPlant->setCurrentNutrients(5);


    PlantState* initialState = new SeedState();
    PlantLifeCycle* lifecycle = new PlantLifeCycle(myPlant, initialState, "LavenderLife");


    //Staff* alice = new Staff("Alice");
    //lifecycle->attach(alice);


    std::cout << "\n--- Initial Evaluation ---\n";
    lifecycle->isHealthy(); // This will call SeedState::evaluate and possibly change state


    for (int day = 1; day <= 3; ++day) {
        std::cout << "\n--- Day " << day << " ---\n";
        lifecycle->notify(); // Triggers Staff::update
        lifecycle->isHealthy(); // Re-evaluate after care
    }

    delete lifecycle;
    delete myPlant;
    //delete alice;

    return 0;
}
