#ifndef CREDITCARDPAYMENTSTRATEGY_H
#define CREDITCARDPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>

class CreditCardPaymentStrategy : public PaymentStrategy {
private:
    std::string cardNumber;
public:
    CreditCardPaymentStrategy(const std::string& cardNumber);
    void pay(double amount, const std::string& orderNum) const override;
};

#endif
