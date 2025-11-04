/**
 * @file CreditCardPaymentStrategy.h
 * @brief Defines the CreditCardPaymentStrategy class for handling credit card
 * payments.
 */

#ifndef CREDITCARDPAYMENTSTRATEGY_H
#define CREDITCARDPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>

/**
 * @class CreditCardPaymentStrategy
 * @brief Implements the PaymentStrategy interface for credit card payments.
 */
class CreditCardPaymentStrategy : public PaymentStrategy
{
  private:
    std::string cardNumber; /**< The credit card number used for payment. */
  public:
    /**
     * @brief Constructs a CreditCardPaymentStrategy with a specified card
     * number.
     * @param cardNumber The credit card number.
     */
    CreditCardPaymentStrategy(const std::string &cardNumber);

    /**
     * @brief Processes payment using a credit card.
     * @param amount The amount to be paid.
     * @param orderNum The order number associated with the payment.
     */
    void pay(double amount, const std::string &orderNum) const override;

    /**
     * @brief Retrieves the name of the payment method.
     * @return The name of the payment strategy.
     */
    std::string getName() const override;
};

#endif
