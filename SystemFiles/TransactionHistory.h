#ifndef TRANSACTION_HISTORY_H
#define TRANSACTION_HISTORY_H

#include <vector>
#include "TransactionSnapshot.h"

class TransactionHistory {
private:
    std::vector<TransactionSnapshot> history;

public:
    void addSnapshot(const TransactionSnapshot& snapshot);
    TransactionSnapshot getSnapshot(int index);
    int getHistorySize();
};

#endif 
