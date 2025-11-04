/**
 * @file Customer.h
 * @brief Defines the Customer class for managing customer-related operations.
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Order.h"
#include "Query.h"
#include "Staff.h"
#include <string>
#include <vector>

/**
 * @class Customer
 * @brief Represents a customer who can place orders and make queries to staff.
 */
class Customer
{
  private:
    std::string name;          /**< The name of the customer. */
    std::vector<Order> orders; /**< List of orders placed by the customer. */

  public:
    /**
     * @brief Default constructor for Customer.
     */
    Customer();

    /**
     * @brief Constructs a Customer with a specified name.
     * @param customerName The name of the customer.
     */
    explicit Customer(const std::string &customerName);

    /**
     * @brief Gets the name of the customer.
     * @return The customer's name.
     */
    std::string getName() const;

    /**
     * @brief Sets the name of the customer.
     * @param customerName The new name of the customer.
     */
    void setName(const std::string &customerName);

    /**
     * @brief Adds a new order to the customer's order list.
     * @param order The order to be placed.
     */
    void placeOrder(const Order &order);

    /**
     * @brief Displays all orders placed by the customer.
     */
    void viewOrders() const;

    /**
     * @brief Sends a query message to a staff member.
     * @param staff Reference to the staff member who will receive the query.
     * @param queryMessage Pointer to the query message object.
     */
    void makeQuery(Staff &staff, Query *queryMessage) const;
};

#endif
