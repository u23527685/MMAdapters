#ifndef TRANSACTIONSNAPSHOT_H
#define TRANSACTIONSNAPSHOT_H

#include <string>

class TransactionSnapshot {
private:
    std::string orderNum;
    double amount;
    int quantity;

public:
    TransactionSnapshot(const std::string& orderNum, double amount, int quantity);

    std::string getOrderNum() const;
    double getAmount() const;
    int getQuantity() const;
};

#endif
