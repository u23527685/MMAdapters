#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "Transaction.h"
#include "Customer.h"

class Order {
private:
    std::string orderId;
    std::string status;
    Customer* customer;                      // Associated customer
    std::vector<Transaction*> transactions;  // List of transactions for the order

public:
    // Constructor
    Order(Customer* customer, const std::string& orderId);

    // Destructor
    ~Order();

    // Add a transaction to the order
    void addTransaction(Transaction* transaction);

    // Process all transactions for the order
    void processOrder();

    // Display order details
    void displayOrderDetails() const;

    // Getters
    std::string getOrderId() const;
    std::string getStatus() const;
    Customer* getCustomer() const;
};

#endif
