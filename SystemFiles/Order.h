#ifndef ORDER_H
#define ORDER_H

#include "Transaction.h"
#include <string>
#include <vector>

class Customer;

class Order
{
  private:
    std::string orderId;
    std::string status;
    Customer *customer;
    std::vector<Transaction *> transactions;

  public:
    Order(Customer *customer, const std::string &orderId);
    ~Order();
    void addTransaction(Transaction *transaction);
    void processOrder();
    void displayOrderDetails() const;

    std::string getOrderId() const;
    std::string getStatus() const;
    Customer *getCustomer() const;
};

#endif
