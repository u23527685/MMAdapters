#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include "PaymentStrategy.h"
#include "TransactionSnapshot.h"

class Transaction {
private:
    std::string orderNum;
    double amount;
    int quantity;
    PaymentStrategy* paymentMethod; // Strategy reference

public:
    Transaction(const std::string& orderNum, double amount, int quantity);

    void setTransaction(const std::string& orderNum, double amount, int quantity);
    void setPaymentStrategy(PaymentStrategy* method);
    void processPayment() const;
    void getDetails() const;

    // Memento pattern
    TransactionSnapshot createSnapshot() const;
    void restoreSnapshot(const TransactionSnapshot& snapshot);
    Transaction* clone() const;

};

#endif
