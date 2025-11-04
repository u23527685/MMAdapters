/**
 * @file PaymentStrategy.h
 * @brief Interface for payment processing strategies
 */

#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include <string>

/**
 * @class PaymentStrategy
 * @brief Abstract base class defining interface for payment methods
 * @details Provides a framework for implementing different payment processing strategies
 */
class PaymentStrategy {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~PaymentStrategy() {}

    /**
     * @brief Process a payment transaction
     * @param amount The monetary amount to process
     * @param orderNum The order number for the transaction
     * @return void
     */
    virtual void pay(double amount, const std::string& orderNum) const = 0;

    /**
     * @brief Gets the name of the payment method
     * @return std::string The payment method name
     */
    virtual std::string getName() const = 0;
};

#endif