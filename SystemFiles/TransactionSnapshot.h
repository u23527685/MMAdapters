#pragma once
#include <string>
#include <vector>
/**
 * @file TransactionSnapshot.h
 * @brief Header file for the TransactionSnapshot class
 * @author Jerusha
 * @date October 27, 2025
 */

/**
 * @class TransactionSnapshot
 * @brief Class representing a snapshot of a transaction
 * @details Stores transaction details including order number, amount, quantity
 * and decorations
 * @author Jerusha
 */
class TransactionSnapshot
{
    std::string orderNum;
    double amount;
    int quantity;
    std::vector<std::string> decorations; // added

  public:
    /**
     * @brief Constructor for TransactionSnapshot
     * @details Initializes a new transaction snapshot with given parameters
     * @param orderNum The order number for the transaction
     * @param amount The monetary amount of the transaction
     * @param quantity The quantity of items in the transaction
     * @param decorations Vector of decoration strings (optional)
     * @author Jerusha
     */
    TransactionSnapshot(const std::string &orderNum, double amount,
                        int quantity,
                        const std::vector<std::string> &decorations = {});
    /**
     * @brief Gets the order number
     * @return std::string The order number of the transaction
     * @author Jerusha
     */
    std::string getOrderNum() const;
    /**
     * @brief Gets the transaction amount
     * @return double The monetary amount of the transaction
     * @author Jerusha
     */
    double getAmount() const;
    /**
     * @brief Gets the quantity of items
     * @return int The quantity of items in the transaction
     * @author Jerusha
     */
    int getQuantity() const;
    /**
     * @brief Gets the decorations associated with the transaction
     * @return const std::vector<std::string>& Vector of decoration strings
     * @author Jerusha
     */
    const std::vector<std::string> &getDecorations() const; // added
};
