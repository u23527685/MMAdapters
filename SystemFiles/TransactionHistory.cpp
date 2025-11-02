#include "TransactionHistory.h"
#include <stdexcept>

void TransactionHistory::addSnapshot(const TransactionSnapshot& snapshot) {
    history.push_back(snapshot);
}

TransactionSnapshot TransactionHistory::getSnapshot(int index) const {
    if (index < 0 || index >= static_cast<int>(history.size()))
        throw std::out_of_range("Invalid snapshot index");
    return history[index];
}

int TransactionHistory::getHistorySize() const {
    return static_cast<int>(history.size());
}
