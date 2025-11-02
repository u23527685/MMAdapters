#include "Order.h"
#include "Customer.h"
#include <iostream>

Order::Order(Customer* customer, const std::string& orderId)
    : orderId(orderId), status("Pending"), customer(customer) {}


Order::~Order() {
    transactions.clear();
}

void Order::addTransaction(Transaction* transaction) {
    if (transaction) {
        transactions.push_back(transaction);
    }
}

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

std::string Order::getOrderId() const { return orderId; }
std::string Order::getStatus() const { return status; }
Customer* Order::getCustomer() const { return customer; }
