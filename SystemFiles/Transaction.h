#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "PaymentStrategy.h"

class Transaction {
private:
    std::string customerName;
    std::string planName;
    double amount;
    int quantity;
    PaymentStrategy* strategy;

public:
    Transaction(const std::string& customerName, const std::string& planName, double amount, int quantity);

    void setPaymentMethod(PaymentStrategy* strategy);
    void processPayment();
    void getDetails() const;
};

#endif
