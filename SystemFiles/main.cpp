#include "Transaction.h"
#include "CreditCardPaymentStrategy.h"
#include "EWalletPaymentStrategy.h"
#include "EFTPaymentStrategy.h"
#include <iostream>

int main() {

    Transaction tx("ORD-1001", 25.50, 2);
    tx.getDetails();

    std::cout << "\n--- Testing Credit Card Payment ---\n";
    CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
    tx.setPaymentMethod(&creditCard);
    tx.processPayment();

    std::cout << "\n--- Testing E-Wallet Payment ---\n";
    EWalletPaymentStrategy ewallet("wallet123");
    tx.setPaymentMethod(&ewallet);
    tx.processPayment();

    std::cout << "\n--- Testing EFT Payment ---\n";
    EFTPaymentStrategy eft("9876543210");
    tx.setPaymentMethod(&eft);
    tx.processPayment();

    return 0;
}
