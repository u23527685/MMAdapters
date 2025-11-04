/**
 * @file Customer.h
 * @brief Represents a Customer who can place orders and make staff queries.
 *
 * The Customer class models a retail customer with a name and a list of
 * previous orders. Customers can interact with staff by submitting queries
 * and can review their order history.
 */
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "Order.h"
#include "Staff.h"
#include "Query.h"

/**
 * @class Customer
 * @brief Represents a store customer and their interactions.
 *
 * Stores customer data, handles order placement, and supports queries
 * directed at staff members.
 */
class Customer {
private:
    std::string name; /**< Customer's name. */
    std::vector<Order> orders; /**< Record of all orders placed by the customer. */

public:
    /**
     * @brief Default constructor creates an unnamed customer.
     */
    Customer();

    /**
     * @brief Construct a Customer with a specific name.
     * @param customerName The customer's name.
     */
    explicit Customer(const std::string& customerName);

    /**
     * @brief Retrieve the customer's name.
     * @return Name of the customer.
     */
    std::string getName() const;

    /**
     * @brief Set or update the customer's name.
     * @param customerName The new name to assign.
     */
    void setName(const std::string& customerName);

    /**
     * @brief Add an order to the customer's order history.
     * @param order The order to add.
     */
    void placeOrder(const Order& order);

    /**
     * @brief Print a summary of all customer orders to the console.
     */
    void viewOrders() const;

    /**
     * @brief Submit a query message to a Staff member.
     * @param staff Reference to the staff member receiving the query.
     * @param queryMessage Pointer to the query message (caller owns).
     */
    void makeQuery(Staff& staff, Query* queryMessage) const;
};

#endif
