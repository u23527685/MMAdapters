#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "TransactionSnapshot.h"
#include "PaymentStrategy.h"

class Transaction {
private:
    std::string customerName;
    std::string plantName;
      std::string orderNum;  
    double amount;
    int quantity;
    PaymentStrategy *paymentMethod;

public:
   Transaction(const std::string& orderNum, double amount, int quantity);
 Transaction(const std::string &customerName, const std::string &plantName, double amount, int quantity);
    void setTransaction(const std::string &customerName, const std::string &plantName, double amount, int quantity);

    std::string getDetails();
    TransactionSnapshot createSnapshot();
    void restoreSnapshot(const TransactionSnapshot &snapshot);

    void setPaymentMethod(PaymentStrategy *strategy);
    void processPayment();

   
    void getDetails() const;
};

#endif
