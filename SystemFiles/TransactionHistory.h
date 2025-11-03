#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include "TransactionSnapshot.h"
#include <vector>

class TransactionHistory {
private:
    std::vector<TransactionSnapshot> history;

public:
    void addSnapshot(const TransactionSnapshot& snapshot);
    TransactionSnapshot getSnapshot(int index) const;
    int getHistorySize() const;
};

#endif
