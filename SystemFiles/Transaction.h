/**
 * @file Transaction.h
 * @brief Header file for the Transaction class
 * @author Jerusha
 * @date October 27, 2025
 */

#pragma once
#include <string>
#include <vector>
#include "TransactionSnapshot.h"
#include "PaymentStrategy.h"

/**
 * @class Transaction
 * @brief Class representing a transaction in the system
 * @details Manages transaction details, payment processing, and state management
 * @author Jerusha
 */
class Transaction {
    std::string orderNum;
    double amount;
    int quantity;
    PaymentStrategy* paymentMethod;
    std::vector<std::string> decorations;
     

public:
  /**
     * @brief Constructor for Transaction
     * @param orderNum The order number for the transaction
     * @param amount The monetary amount
     * @param quantity The quantity of items
     * @author Jerusha
     */
    Transaction(const std::string& orderNum, double amount, int quantity);
    /**
     * @brief Sets the transaction details
     * @param orderNum The order number
     * @param amount The monetary amount
     * @param quantity The quantity of items
     * @return void
     * @author Jerusha
     */
    void setTransaction(const std::string& orderNum, double amount, int quantity);
        /**
     * @brief Sets the payment strategy
     * @param method Pointer to the payment strategy to use
     * @return void
     * @author Jerusha
     */
    void setPaymentStrategy(PaymentStrategy* method);
        /**
     * @brief Processes the payment using the set strategy
     * @return void
     * @author Jerusha
     */
    void processPayment() const;
        /**
     * @brief Displays transaction details
     * @return void
     * @author Jerusha
     */
    void getDetails() const;
    /**
     * @brief Gets the transaction ID
     * @return std::string The transaction ID
     * @author Jerusha
     */
    std::string getTransactionId() const;
    /**
     * @brief Gets the transaction amount
     * @return double The monetary amount
     * @author Jerusha
     */
    double getAmount() const;

    /**
     * @brief Gets the quantity of items
     * @return int The quantity
     * @author Jerusha
     */
    int getQuantity() const;

    /**
     * @brief Gets the payment method
     * @return std::string The payment method
     * @author Jerusha
     */
    std::string getPaymentMethod() const;

    /**
     * @brief Adds a decoration to the transaction
     * @param decor The decoration to add
     * @return void
     * @author Jerusha
     */
    void addDecoration(const std::string& decor);

    /**
     * @brief Gets the decorations associated with the transaction
     * @return const std::vector<std::string>& The vector of decorations
     * @author Jerusha
     */
    const std::vector<std::string>& getDecorations() const;

    /**
     * @brief Creates a snapshot of the current transaction state
     * @return TransactionSnapshot The created snapshot
     * @author Jerusha
     */
    TransactionSnapshot createSnapshot() const;

    /**
     * @brief Restores the transaction state from a snapshot
     * @param snapshot The snapshot to restore from
     * @return void
     * @author Jerusha
     */
    void restoreSnapshot(const TransactionSnapshot& snapshot);

    /**
     * @brief Clones the current transaction
     * @return Transaction* A pointer to the cloned transaction
     * @author Jerusha
     */
    Transaction* clone() const;
};
