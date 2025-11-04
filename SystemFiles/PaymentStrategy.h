/**
 * @file PaymentStrategy.h
 * @brief Abstract interface for various payment strategies.
 *
 * PaymentStrategy defines the interface for all payment mechanisms,
 * allowing flexibility through polymorphism (Strategy Pattern).
 *
 * @see EFTPaymentStrategy
 * @see EWalletPaymentStrategy
 *
 * @author
 * Jerusha Thaver
 */
#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include <string>

/**
 * @class PaymentStrategy
 * @brief Abstract strategy for processing payments.
 *
 * Provides a common interface for different payment types (EFT, E-Wallet, etc.).
 */
class PaymentStrategy {
public:
    /// Virtual destructor.
    virtual ~PaymentStrategy() {}

     /**
     * @brief Executes a payment operation.
     * @param amount The payment amount.
     * @param orderNum The associated order identifier.
     */
    virtual void pay(double amount, const std::string& orderNum) const = 0;

    /**
     * @brief Retrieves the payment strategy name.
     * @return String representing the payment method type.
     */
    virtual std::string getName() const = 0;
};

#endif
