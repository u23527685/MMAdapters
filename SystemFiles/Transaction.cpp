/**
 * @file Transaction.cpp
 * @brief Implementation of the Transaction class
 * @author Jerusha
 * @date October 27, 2025
 */

#include "Transaction.h"
#include <iostream>

/**
 * @brief Constructor for Transaction
 * @param orderNum The order number for the transaction
 * @param amount The monetary amount
 * @param quantity The quantity of items
 * @return None (constructor)
 * @author Jerusha
 */
Transaction::Transaction(const std::string& orderNum, double amount, int quantity)
    : orderNum(orderNum), amount(amount), quantity(quantity), paymentMethod(nullptr) {}

    /**
 * @brief Sets the transaction details
 * @param orderNum The order number
 * @param amount The monetary amount
 * @param quantity The quantity of items
 * @return void
 * @author Jerusha
 */
void Transaction::setTransaction(const std::string& orderNum, double amount, int quantity) {
    this->orderNum = orderNum;
    this->amount = amount;
    this->quantity = quantity;
}


/**
 * @brief Sets the payment strategy
 * @param method Pointer to the payment strategy to use
 * @return void
 * @author Jerusha
 */
void Transaction::setPaymentStrategy(PaymentStrategy* method) {
    paymentMethod = method;
}
 
/**
 * @brief Gets the payment method name
 * @return std::string The name of the payment method
 * @author Jerusha
 */
std::string Transaction::getPaymentMethod() const {
    return paymentMethod ? paymentMethod->getName() : "Unknown";
}
 
/**
 * @brief Processes the payment using the set strategy
 * @return void
 * @author Jerusha
 */
void Transaction::processPayment() const {
    if (paymentMethod)
        paymentMethod->pay(amount, orderNum);
    else
        std::cout << "No payment strategy set for order " << orderNum
                  << std::endl;
}

/**
 * @brief Displays transaction details
 * @return void
 * @author Jerusha
 */
void Transaction::getDetails() const {
    std::cout << "Order Number: " << orderNum
              << "\nAmount: R" << amount
              << "\nQuantity: " << quantity
              << "\nTotal: R" << (amount * quantity)
              << "\nDecorations: ";
    if (decorations.empty())
        std::cout << "None";
    else
        for (const auto &d : decorations)
            std::cout << d << " ";
    std::cout << "\n";
}

/**
 * @brief Gets the Order Number
 * @return std::string The order number
 * @author Jerusha
 */
std::string Transaction::getTransactionId() const {
    return orderNum;
}

/**
 * @brief Gets the transaction amount
 * @return double The monetary amount
 * @author Jerusha
 */
double Transaction::getAmount() const {
    return amount;
}

/**
 * @brief Gets the quantity of items
 * @return int The quantity
 * @author Jerusha
 */
int Transaction::getQuantity() const {
    return quantity;
}

/**
 * @brief Adds a decoration to the transaction
 * @param decor The decoration to add
 * @return void
 * @author Jerusha
 */
void Transaction::addDecoration(const std::string& decor) {
    decorations.push_back(decor);
}

/**
 * @brief Gets the list of decorations
 * @return const std::vector<std::string>& Reference to decorations vector
 * @author Jerusha
 */

const std::vector<std::string>& Transaction::getDecorations() const {
    return decorations;
}



 /**
 * @brief Creates a snapshot of current transaction state
 * @return TransactionSnapshot The created snapshot
 * @author Jerusha
 */
TransactionSnapshot Transaction::createSnapshot() const {
    return TransactionSnapshot(orderNum, amount, quantity, decorations);
}

/**
 * @brief Restores transaction state from a snapshot
 * @param snapshot The snapshot to restore from
 * @return void
 * @author Jerusha
 */
void Transaction::restoreSnapshot(const TransactionSnapshot& snapshot) {
    orderNum = snapshot.getOrderNum();
    amount = snapshot.getAmount();
    quantity = snapshot.getQuantity();
    decorations = snapshot.getDecorations();
}

/**
 * @brief Creates a clone of the transaction
 * @return Transaction* Pointer to the cloned transaction
 * @author Jerusha
 */
Transaction* Transaction::clone() const {
    Transaction* copy = new Transaction(orderNum, amount, quantity);
    copy->decorations = decorations;
    if (paymentMethod)
        copy->setPaymentStrategy(paymentMethod);
    return copy;
}
