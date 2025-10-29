#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <iostream>
#include "Order.h"

class Staff {
private:
    std::string staffName;
    std::string role;

public:
    Staff();
    Staff(const std::string& name, const std::string& role);
    std::string getName() const;
    std::string getRole() const;
    void setName(const std::string& name);
    void setRole(const std::string& role);
    void respondToQuery(const std::string& queryMessage) const;
    void checkOrderStatus(const Order& order) const;
};

#endif 
