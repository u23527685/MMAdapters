#include "Transaction.h"
#include <iostream>

Transaction::Transaction(const std::string& orderNum, double amount, int quantity)
    : orderNum(orderNum), amount(amount), quantity(quantity), strategy(NULL) {}

void Transaction::setPaymentMethod(PaymentStrategy* strategy) {
    this->strategy = strategy;
}

void Transaction::processPayment() {
    if (strategy) {
        strategy->pay(amount * quantity, orderNum); // Use orderNum as identifier
    } else {
        std::cout << "No payment strategy set!" << std::endl;
    }
}

void Transaction::getDetails() const {
    std::cout << "Transaction Details:\n"
              << "Order Number: " << orderNum << "\n"
              << "Amount: R" << amount << "\n"
              << "Quantity: " << quantity << std::endl;
}
