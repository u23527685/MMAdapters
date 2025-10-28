#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include <string>

class PaymentStrategy {
public:
    virtual ~PaymentStrategy() {}
    virtual void pay(double amount, const std::string& orderNum) const = 0;
};

#endif
