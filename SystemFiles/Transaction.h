#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "PaymentStrategy.h"

class Transaction {
private:
    std::string orderNum;      // The order number this transaction belongs to
    double amount;
    int quantity;
    PaymentStrategy* strategy;

public:
    Transaction(const std::string& orderNum, double amount, int quantity);

    void setPaymentMethod(PaymentStrategy* strategy);
    void processPayment();
    void getDetails() const;
};

#endif
