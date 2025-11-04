/**
 * @file TransactionHistory.cpp
 * @brief Implementation of the TransactionHistory class
 * @author Jerusha
 * @date October 28, 2025
 */
#include "TransactionHistory.h"
#include <stdexcept>

/**
 * @brief Adds a transaction snapshot to the history
 * @details Appends the provided snapshot to the end of the history vector
 * @param snapshot The TransactionSnapshot to add
 * @return void
 * @author Jerusha
 */
void TransactionHistory::addSnapshot(const TransactionSnapshot &snapshot)
{
    history.push_back(snapshot);
}

/**
 * @brief Retrieves a specific transaction snapshot from history
 * @details Returns the snapshot at the specified index if it exists
 * @param index The index of the snapshot to retrieve
 * @return TransactionSnapshot The requested transaction snapshot
 * @throw std::out_of_range if index is invalid
 * @author Jerusha
 */
TransactionSnapshot TransactionHistory::getSnapshot(int index) const
{
    if (index < 0 || index >= static_cast<int>(history.size()))
        throw std::out_of_range("Invalid snapshot index");
    return history[index];
}

/**
 * @brief Gets the current size of the transaction history
 * @details Returns the number of snapshots currently stored in the history
 * @return int The number of snapshots in the history
 * @author Jerusha
 */
int TransactionHistory::getHistorySize() const
{
    return static_cast<int>(history.size());
}
