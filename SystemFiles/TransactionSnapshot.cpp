/**
 * @file TransactionSnapshot.cpp
 * @brief Implementation of the TransactionSnapshot class
 * @author Jerusha
 * @date October 27, 2025
 */

#include "TransactionSnapshot.h"

/**
 * @brief Constructor for TransactionSnapshot
 * @details Initializes a new transaction snapshot with the provided parameters
 * @param orderNum The order number for the transaction
 * @param amount The monetary amount of the transaction
 * @param quantity The quantity of items in the transaction
 * @param decorations Vector of decoration strings (optional)
 * @return None (constructor)
 * @author Jerusha
 */
TransactionSnapshot::TransactionSnapshot(
    const std::string &orderNum, double amount, int quantity,
    const std::vector<std::string> &decorations)
    : orderNum(orderNum), amount(amount), quantity(quantity),
      decorations(decorations)
{
}

/**
 * @brief Gets the order number
 * @details Returns the stored order number for the transaction
 * @return std::string The order number of the transaction
 * @author Jerusha
 */
std::string TransactionSnapshot::getOrderNum() const { return orderNum; }

/**
 * @brief Gets the transaction amount
 * @details Returns the stored monetary amount for the transaction
 * @return double The monetary amount of the transaction
 * @author Jerusha
 */
double TransactionSnapshot::getAmount() const { return amount; }

/**
 * @brief Gets the quantity of items
 * @details Returns the stored quantity of items in the transaction
 * @return int The quantity of items in the transaction
 * @author Jerusha
 */
int TransactionSnapshot::getQuantity() const { return quantity; }

/**
 * @brief Gets the decorations list
 * @details Returns the stored vector of decorations associated with the
 * transaction
 * @return const std::vector<std::string>& Reference to the vector of
 * decorations
 * @author Jerusha
 */
const std::vector<std::string> &TransactionSnapshot::getDecorations() const
{
    return decorations;
}