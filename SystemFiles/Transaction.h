/**
 * @file Transaction.h
 * @brief Represents a customer transaction and payment.
 *
 * Supports snapshot creation and restoration for Memento pattern.
 *
 */
#pragma once
#include <string>
#include <vector>
#include "TransactionSnapshot.h"
#include "PaymentStrategy.h"

/**
 * @class Transaction
 * @brief Encapsulates all details of a plant purchase transaction.
 */
class Transaction {
    std::string orderNum; /**< Unique order number. */
    double amount; /**< Total amount for the transaction. */
    int quantity; /**< Number of plants purchased. */
    PaymentStrategy* paymentMethod;  /**< Payment strategy used. */
    std::vector<std::string> decorations; /**< List of applied decorations. */
     

public:
    /**
     * @brief Constructs a transaction.
     * @param orderNum Unique identifier for the order.
     * @param amount Total purchase amount.
     * @param quantity Number of items purchased.
     */
    Transaction(const std::string& orderNum, double amount, int quantity);

    /**
     * @brief Updates transaction details.
     * @param orderNum Order identifier.
     * @param amount Updated amount.
     * @param quantity Updated quantity.
     */
    void setTransaction(const std::string& orderNum, double amount, int quantity);

    /**
     * @brief Sets the payment strategy.
     * @param method Pointer to the chosen PaymentStrategy.
     */
    void setPaymentStrategy(PaymentStrategy* method);

    /**
     * @brief Processes payment using the selected strategy.
     */
    void processPayment() const;

    /**
     * @brief Displays the transaction details.
     */
    void getDetails() const;

    /**
     * @brief Retrieves the transaction ID.
     * @return Order number as a string.
     */
    std::string getTransactionId() const;

    /**
     * @brief Retrieves the transaction amount.
     * @return Total amount.
     */
    double getAmount() const;

    /**
     * @brief Retrieves quantity purchased.
     * @return Quantity of items.
     */
    int getQuantity() const;

    /**
     * @brief Retrieves payment method name.
     * @return Payment strategy name.
     */
    std::string getPaymentMethod() const;

    /**
     * @brief Adds a decorative feature to the transaction.
     * @param decor Name of the decoration.
     */
    void addDecoration(const std::string& decor);

    /**
     * @brief Returns all applied decorations.
     * @return Vector of decoration names.
     */
    const std::vector<std::string>& getDecorations() const;

    /**
     * @brief Creates a snapshot of the current transaction state.
     * @return A TransactionSnapshot instance.
     */
    TransactionSnapshot createSnapshot() const;

    /**
     * @brief Restores the transaction from a snapshot.
     * @param snapshot The snapshot to restore from.
     */
    void restoreSnapshot(const TransactionSnapshot& snapshot);

    /**
     * @brief Clones this transaction.
     * @return Pointer to a new Transaction object with the same state.
     */
    Transaction* clone() const;
};
