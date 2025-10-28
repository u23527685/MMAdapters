#ifndef TRANSACTION_SNAPSHOT_H
#define TRANSACTION_SNAPSHOT_H

#include <string>

class TransactionSnapshot {
private:
    std::string customerName;
    std::string plantName;
    double amount;
    int quantity;

public:
    TransactionSnapshot(const std::string &customerName, const std::string &plantName, double amount, int quantity);
    std::string getCustomerName();
    std::string getPlantName();
    double getAmount();
    int getQuantity();
    void setSnapshot(const std::string &customerName, const std::string &plantName, double amount, int quantity);
};

#endif
