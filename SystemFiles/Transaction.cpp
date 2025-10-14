#include "Transaction.h"
#include <iostream>

Transaction::Transaction(const std::string &customerName, const std::string &plantName, double amount, int quantity)
    : customerName(customerName), plantName(plantName), amount(amount), quantity(quantity), paymentMethod(NULL) {}

void Transaction::setTransaction(const std::string &customerName, const std::string &plantName,
                                 double amount, int quantity) {
    this->customerName = customerName;
    this->plantName = plantName;
    this->amount = amount;
    this->quantity = quantity;
}

std::string Transaction::getDetails(){
    return "Customer: " + customerName +
           " | Plant: " + plantName +
           " | Amount: " + std::to_string(amount) +
           " | Quantity: " + std::to_string(quantity);
}

TransactionSnapshot Transaction::createSnapshot() {
    return TransactionSnapshot(customerName, plantName, amount, quantity);
}

void Transaction::restoreSnapshot(const TransactionSnapshot &snapshot) {
    setTransaction(snapshot.getCustomerName(),
                   snapshot.getPlantName(),
                   snapshot.getAmount(),
                   snapshot.getQuantity());
}

void Transaction::setPaymentMethod(PaymentStrategy *strategy) {
    paymentMethod = strategy;
}

void Transaction::processPayment() {
    if (paymentMethod) {
        paymentMethod->pay(amount, customerName);
    } else {
        std::cout << "No payment method selected for " << customerName << std::endl;
    }
}
