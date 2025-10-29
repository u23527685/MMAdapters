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

    return 0;
}
