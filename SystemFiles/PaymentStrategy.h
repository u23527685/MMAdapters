#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include <string>

class PaymentStrategy {
public:
    virtual void pay(double amount, const std::string& customerName) = 0;
    virtual ~PaymentStrategy() = default;
};

#endif
