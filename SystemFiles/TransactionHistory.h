/**
 * @file TransactionHistory.h
 * @brief Maintains a record of transaction snapshots for order tracking and history retrieval.
 *
 * This class stores and manages a collection of TransactionSnapshot objects,
 * allowing addition, retrieval, and inspection of past transactions.
 * 
 * @see TransactionSnapshot
 */
#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include "TransactionSnapshot.h"
#include <vector>

/**
 * @class TransactionHistory
 * @brief Manages the storage and retrieval of transaction snapshots.
 *
 * Provides functionality to add new snapshots, access previous ones,
 * and get the total number of transactions recorded.
 */
class TransactionHistory {
private:
    std::vector<TransactionSnapshot> history; /**< Vector containing all transaction snapshots. */

public:
    /**
     * @brief Adds a new snapshot to the transaction history.
     * @param snapshot The TransactionSnapshot object representing a completed order.
     */
    void addSnapshot(const TransactionSnapshot& snapshot);

    /**
     * @brief Retrieves a specific snapshot by index.
     * @param index The index of the snapshot to retrieve.
     * @return The TransactionSnapshot at the specified index.
     * @warning Calling with an invalid index may cause undefined behavior.
     */
    TransactionSnapshot getSnapshot(int index) const;

    /**
     * @brief Gets the total number of snapshots in the history.
     * @return The number of stored TransactionSnapshot objects.
     */
    int getHistorySize() const;
};

#endif
