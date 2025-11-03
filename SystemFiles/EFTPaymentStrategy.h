#ifndef EFTPAYMENTSTRATEGY_H
#define EFTPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"

class EFTPaymentStrategy : public PaymentStrategy {
private:
    std::string accountNumber;
public:
    EFTPaymentStrategy(const std::string& accountNumber);
    void pay(double amount, const std::string& orderNum) const override;
    std::string getName() const override;
};

#endif
