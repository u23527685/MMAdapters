#include "TransactionHistory.h"
#include <stdexcept> //out of range for version 11

void TransactionHistory::addSnapshot(const TransactionSnapshot &snapshot) {
    history.push_back(snapshot);
}

TransactionSnapshot TransactionHistory::getSnapshot(int index) {
    if (index >= 0 && index < static_cast<int>(history.size())) {
        return history[index];
    }
    throw std::out_of_range("Snapshot index out of range");//uses stdexcept
}

int TransactionHistory::getHistorySize(){
    return static_cast<int>(history.size());
}
