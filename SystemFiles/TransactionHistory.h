/**
 * @file TransactionHistory.h
 * @brief Header file for the TransactionHistory class
 * @author Jerusha
 * @date October 27, 2025
 */

#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include "TransactionSnapshot.h"
#include <vector>

/**
 * @class TransactionHistory
 * @brief Class for managing transaction history
 * @details Maintains a collection of transaction snapshots and provides methods
 * to access them
 * @author Jerusha
 */
class TransactionHistory
{
  private:
    std::vector<TransactionSnapshot> history;

  public:
    /**
     * @brief Adds a transaction snapshot to the history
     * @param snapshot The TransactionSnapshot to add
     * @return void
     * @author Jerusha
     */
    void addSnapshot(const TransactionSnapshot &snapshot);

    /**
     * @brief Retrieves a specific transaction snapshot from history
     * @param index The index of the snapshot to retrieve
     * @return TransactionSnapshot The requested transaction snapshot
     * @throw std::out_of_range if index is invalid
     * @author Jerusha
     */
    TransactionSnapshot getSnapshot(int index) const;

    /**
     * @brief Gets the current size of the transaction history
     * @return int The number of snapshots in the history
     * @author Jerusha
     */
    int getHistorySize() const;
};

#endif