/**
 * @file EWalletPaymentStrategy.h
 * @brief Header file for E-Wallet payment strategy implementation
 */

#ifndef EWALLETPAYMENTSTRATEGY_H
#define EWALLETPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"

/**
 * @class EWalletPaymentStrategy
 * @brief Strategy for processing e-wallet payments
 * @details Implements payment processing for electronic wallet transactions
 */
class EWalletPaymentStrategy : public PaymentStrategy {
private:
    std::string walletID;    ///< Unique identifier for the e-wallet account

public:
    /**
     * @brief Constructor for EWalletPaymentStrategy
     * @param walletID The ID of the e-wallet account
     * @return None (constructor)
     */
    EWalletPaymentStrategy(const std::string& walletID);

    /**
     * @brief Process an e-wallet payment
     * @param amount The monetary amount to process
     * @param orderNum The order number for the transaction
     * @return void
     */
    void pay(double amount, const std::string& orderNum) const override;

    /**
     * @brief Gets the payment method name
     * @return std::string The name "E-Wallet"
     */
    std::string getName() const override;
};

#endif