/**
 * @file Order.h
 * @brief Header file for the Order class
 */

#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "Transaction.h"

class Customer;

/**
 * @class Order
 * @brief Manages customer orders and associated transactions
 * @details Handles order processing, transaction management and status tracking
 */
class Order {
private:
    std::string orderId;                    ///< Unique identifier for the order
    std::string status;                     ///< Current status of the order
    Customer* customer;                      ///< Customer who placed the order
    std::vector<Transaction*> transactions;  ///< List of transactions in the order

public:
    /**
     * @brief Constructor for Order
     * @param customer Pointer to the Customer placing the order
     * @param orderId Unique identifier for the order
     */
    Order(Customer* customer, const std::string& orderId);

    /**
     * @brief Destructor for Order
     */
    ~Order();

    /**
     * @brief Adds a transaction to the order
     * @param transaction Pointer to the Transaction to add
     * @return void
     */
    void addTransaction(Transaction* transaction);

    /**
     * @brief Processes all transactions in the order
     * @return void
     */
    void processOrder();

    /**
     * @brief Displays details of the order
     * @return void
     */
    void displayOrderDetails() const;

    /**
     * @brief Gets the order identifier
     * @return std::string The order ID
     */
    std::string getOrderId() const;

    /**
     * @brief Gets the current order status
     * @return std::string The order status
     */
    std::string getStatus() const;

    /**
     * @brief Gets the customer who placed the order
     * @return Customer* Pointer to the customer
     */
    Customer* getCustomer() const;
};

#endif