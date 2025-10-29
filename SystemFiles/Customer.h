#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "Order.h"
#include "Staff.h"
#include "Query.h"

class Customer {
private:
    std::string name;
    std::vector<Order> orders; 

public:
    Customer();
    explicit Customer(const std::string& customerName);
    std::string getName() const;
    void setName(const std::string& customerName);
    void placeOrder(const Order& order);
    void viewOrders() const;
    void makeQuery(Staff& staff, Query* queryMessage) const;
};

#endif
