#include "Staff.h"
#include <iostream>

Staff::Staff() : staffName("Unnamed Staff"), role("General") {}

Staff::Staff(const std::string& name, const std::string& role)
    : staffName(name), role(role) {}

std::string Staff::getName() const {
    return staffName;
}

std::string Staff::getRole() const {
    return role;
}

void Staff::setName(const std::string& name) {
    staffName = name;
}

void Staff::setRole(const std::string& newRole) {
    role = newRole;
}

void Staff::respondToQuery(const std::string& queryMessage) const {
    std::cout << "[Staff: " << staffName << "] Received customer query: \""
              << queryMessage << "\"\n";
    std::cout << "Response: We'll review your request and get back to you shortly.\n";
}

void Staff::checkOrderStatus(const Order& order) const {
    std::cout << "[Staff: " << staffName << "] Checking status for Order ID: "
              << order.getOrderId() << std::endl;
    std::cout << "Current status: " << order.getStatus() << "\n";
}
