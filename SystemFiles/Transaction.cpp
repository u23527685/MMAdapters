#include "Transaction.h"
#include <iostream>

Transaction::Transaction(const std::string& orderNum, double amount, int quantity)
    : orderNum(orderNum), amount(amount), quantity(quantity), paymentMethod(nullptr) {}

void Transaction::setTransaction(const std::string& orderNum, double amount, int quantity) {
    this->orderNum = orderNum;
    this->amount = amount;
    this->quantity = quantity;
}

void Transaction::setPaymentStrategy(PaymentStrategy* method) {
    paymentMethod = method;
}

void Transaction::processPayment() const {
    if (paymentMethod)
        paymentMethod->pay(amount * quantity, orderNum);
    else
        std::cout << "No payment strategy set for order " << orderNum << std::endl;
}

void Transaction::getDetails() const {
    std::cout << "Order Number: " << orderNum
              << "\nAmount: R" << amount
              << "\nQuantity: " << quantity
              << "\nTotal: R" << (amount * quantity)
              << "\n";
}

std::string Transaction::getTransactionId() const {
    return orderNum;
}

double Transaction::getAmount() const {
    return amount * quantity;
}

int Transaction::getQuantity() const {
    return quantity;
}

TransactionSnapshot Transaction::createSnapshot() const {
    return TransactionSnapshot(orderNum, amount, quantity);
}

void Transaction::restoreSnapshot(const TransactionSnapshot& snapshot) {
    orderNum = snapshot.getOrderNum();
    amount = snapshot.getAmount();
    quantity = snapshot.getQuantity();
}

Transaction* Transaction::clone() const {
    Transaction* copy = new Transaction(orderNum, amount, quantity);
    if (paymentMethod)
        copy->setPaymentStrategy(paymentMethod);
    return copy;
}
