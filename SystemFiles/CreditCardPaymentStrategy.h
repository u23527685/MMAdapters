/**
 * @file CreditCardPaymentStrategy.h
 * @brief Concrete payment strategy using credit card transactions.
 *
 * Implements the PaymentStrategy interface to process payments through a
 * stored credit card number. Outputs confirmation or transaction details
 * to the console.
 */
#ifndef CREDITCARDPAYMENTSTRATEGY_H
#define CREDITCARDPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>

/**
 * @class CreditCardPaymentStrategy
 * @brief Payment strategy implementation using credit card information.
 *
 * Stores a card number and defines the logic to execute a payment using it.
 */
class CreditCardPaymentStrategy : public PaymentStrategy {
private:
    std::string cardNumber; /**< Credit card number used for payment. */
public:
    /**
     * @brief Construct a CreditCardPaymentStrategy.
     * @param cardNumber The credit card number as a string.
     */
    CreditCardPaymentStrategy(const std::string& cardNumber);

    /**
     * @brief Execute a credit card payment.
     * @param amount The total amount to charge.
     * @param orderNum Identifier for the order being paid.
     */
    void pay(double amount, const std::string& orderNum) const override;
    std::string getName() const override;
};

#endif
