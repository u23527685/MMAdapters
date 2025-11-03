#pragma once
#include <string>
#include <vector>
#include "TransactionSnapshot.h"
#include "PaymentStrategy.h"

class Transaction {
    std::string orderNum;
    double amount;
    int quantity;
    PaymentStrategy* paymentMethod;
    std::vector<std::string> decorations;
     

public:
    Transaction(const std::string& orderNum, double amount, int quantity);

    void setTransaction(const std::string& orderNum, double amount, int quantity);
    void setPaymentStrategy(PaymentStrategy* method);
    void processPayment() const;
    void getDetails() const;
    std::string getTransactionId() const;
    double getAmount() const;
    int getQuantity() const;
    std::string getPaymentMethod() const;
    void addDecoration(const std::string& decor);
    const std::vector<std::string>& getDecorations() const;

    TransactionSnapshot createSnapshot() const;
    void restoreSnapshot(const TransactionSnapshot& snapshot);

    Transaction* clone() const;
};
