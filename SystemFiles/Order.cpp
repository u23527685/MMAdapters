#include "Order.h"
#include <iostream>

// Constructor
Order::Order(Customer* customer, const std::string& orderId)
    : customer(customer), orderId(orderId), status("Pending") {}

// Destructor
Order::~Order() {
    for (auto transaction : transactions) {
        delete transaction;
    }
    transactions.clear();
}

// Add a transaction
void Order::addTransaction(Transaction* transaction) {
    if (transaction != NULL) {
        transactions.push_back(transaction);
    }
}

// Process the order (pays all transactions)
void Order::processOrder() {
    std::cout << "\nProcessing Order: " << orderId << std::endl;
    if (customer) {
        std::cout << "Customer: " << customer->getName() << std::endl;
    }

    if (transactions.empty()) {
        std::cout << "No transactions found for this order.\n";
        return;
    }

    for (auto transaction : transactions) {
        transaction->processPayment();
    }

    status = "Paid";
    std::cout << "Order " << orderId << " processed successfully.\n";
}

// Display order details
void Order::displayOrderDetails() const {
    std::cout << "\n--- Order Details ---\n";
    std::cout << "Order ID: " << orderId << "\n";
    if (customer) {
        std::cout << "Customer: " << customer->getName() << "\n";
    }
    std::cout << "Status: " << status << "\n";

    for (auto transaction : transactions) {
        transaction->getDetails();
    }
    std::cout << "----------------------\n";
}

// Getters
std::string Order::getOrderId() const { return orderId; }
std::string Order::getStatus() const { return status; }
Customer* Order::getCustomer() const { return customer; }
