/**
 * @file Order.h
 * @brief Represents a customer's order containing multiple transactions.
 *
 * The Order class tracks the status, transactions, and associated customer
 * for each order placed within the system.
 *
 * @see Transaction
 * @see Customer
 *
 * @author
 * Jerusha Thaver
 */
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "Transaction.h"

class Customer;

/**
 * @class Order
 * @brief Represents a customer's purchase order.
 *
 * An Order aggregates multiple transactions and manages their processing,
 * status updates, and display details.
 */
class Order {
private:
    std::string orderId; ///< Unique identifier for the order.
    std::string status; ///< Current status of the order.
    Customer* customer; ///< Pointer to the customer who placed the order.                     
    std::vector<Transaction*> transactions;  ///< List of associated transactions.

public:
     /**
     * @brief Constructs a new Order instance.
     * @param customer Pointer to the customer placing the order.
     * @param orderId Unique order identifier.
     */
    Order(Customer* customer, const std::string& orderId);

    /// Destructor to clean up order resources.
    ~Order();

    /**
     * @brief Adds a transaction to this order.
     * @param transaction Pointer to the transaction to add.
     */
    void addTransaction(Transaction* transaction);

    /**
     * @brief Processes all transactions associated with this order.
     */
    void processOrder();

    /**
     * @brief Displays detailed information about this order.
     */
    void displayOrderDetails() const;

    /**
     * @brief Retrieves the order ID.
     * @return String representing the order ID.
     */
    std::string getOrderId() const;

    /**
     * @brief Retrieves the current order status.
     * @return String representing the order status.
     */
    std::string getStatus() const;

    /**
     * @brief Gets the customer associated with this order.
     * @return Pointer to the Customer.
     */
    Customer* getCustomer() const;
};

#endif
