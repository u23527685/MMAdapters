/**
 * @file TransactionSnapshot.h
 * @brief Defines the TransactionSnapshot class for storing details of a single order transaction.
 *
 * Each snapshot captures order details such as order number, total amount, quantity,
 * and optional decorations applied to the purchased plant.
 */
#pragma once
#include <string>
#include <vector>

/**
 * @class TransactionSnapshot
 * @brief Represents a snapshot of a completed transaction.
 *
 * Encapsulates details such as order number, transaction amount,
 * quantity purchased, and applied decorations.
 */
class TransactionSnapshot {
    std::string orderNum; /**< Unique order number. */
    double amount; /**< Total payment amount. */
    int quantity; /**< Number of items purchased. */
    std::vector<std::string> decorations; /**< List of decorations applied to the plant. */

public:
    /**
     * @brief Constructs a new TransactionSnapshot object.
     * @param orderNum The order number associated with the transaction.
     * @param amount The total amount paid.
     * @param quantity The quantity of items purchased.
     * @param decorations A list of decorations applied (optional).
     */
    TransactionSnapshot(const std::string& orderNum, double amount, int quantity,
                        const std::vector<std::string>& decorations = {});

    /**
     * @brief Retrieves the order number.
     * @return The order number as a string.
     */
    std::string getOrderNum() const;

     /**
     * @brief Retrieves the total transaction amount.
     * @return The amount paid for the order.
     */
    double getAmount() const;

    /**
     * @brief Retrieves the quantity of items purchased.
     * @return The number of items in the order.
     */
    int getQuantity() const;

    /**
     * @brief Retrieves the decorations associated with the transaction.
     * @return A constant reference to the vector of decoration names.
     */
    const std::vector<std::string>& getDecorations() const; // added
};
