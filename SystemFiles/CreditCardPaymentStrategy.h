#ifndef CREDITCARDPAYMENTSTRATEGY_H
#define CREDITCARDPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"

class CreditCardPaymentStrategy : public PaymentStrategy {
private:
    std::string cardNumber;
public:
    CreditCardPaymentStrategy(const std::string& cardNumber);
    void pay(double amount, const std::string& customerName) override;
};

#endif
