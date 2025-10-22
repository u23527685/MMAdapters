#include "Transaction.h"
#include <iostream>

Transaction::Transaction(const std::string& customerName, const std::string& planName, double amount, int quantity)
    : customerName(customerName), planName(planName), amount(amount), quantity(quantity), strategy(nullptr) {}

void Transaction::setPaymentMethod(PaymentStrategy* strategy) {
    this->strategy = strategy;
}

void Transaction::processPayment() {
    if (strategy) {
        strategy->pay(amount * quantity, customerName);
    } else {
        std::cout << "No payment strategy set!" << std::endl;
    }
}

void Transaction::getDetails() const {
    std::cout << "Transaction Details:\n"
              << "Customer: " << customerName << "\n"
              << "Plan: " << planName << "\n"
              << "Amount: $" << amount << "\n"
              << "Quantity: " << quantity << std::endl;
}
