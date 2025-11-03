#include "Customer.h"
#include <iostream>

Customer::Customer() : name("Unknown") {}

Customer::Customer(const std::string& customerName)
    : name(customerName) {}

std::string Customer::getName() const {
    return name;
}

void Customer::setName(const std::string& customerName) {
    name = customerName;
}

void Customer::placeOrder(const Order& order) {
    orders.push_back(order);
    std::cout << "Order placed by " << name << "." << std::endl;
}

void Customer::viewOrders() const {
    if (orders.empty()) {
        std::cout << name << " has no orders." << std::endl;
        return;
    }

    std::cout << "\nOrders for " << name << ":" << std::endl;
    for (const auto& order : orders) {
        order.displayOrderDetails();
    }
}

void Customer::makeQuery(Staff& staff, Query* queryMessage) const {
    std::cout << name << " makes a query to staff: " << queryMessage << std::endl;
    staff.handleQuery(queryMessage);
}
