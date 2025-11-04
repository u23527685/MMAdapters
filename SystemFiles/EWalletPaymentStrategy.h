/**
 * @file EWalletPaymentStrategy.h
 * @brief Concrete payment strategy using a digital e-wallet.
 *
 * Implements the PaymentStrategy interface for processing e-wallet payments
 * through a stored wallet ID (e.g., PayPal, SnapScan, etc.).
 *
 */
#ifndef EWALLETPAYMENTSTRATEGY_H
#define EWALLETPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"

/**
 * @class EWalletPaymentStrategy
 * @brief Implements a payment method using an e-wallet ID.
 *
 * Processes payments through digital wallet services.
 */
class EWalletPaymentStrategy : public PaymentStrategy {
private:
    std::string walletID; /**< Wallet ID associated with the e-wallet account. */
public:
     /**
     * @brief Construct an EWalletPaymentStrategy.
     * @param walletID Identifier of the wallet to charge.
     */
    EWalletPaymentStrategy(const std::string& walletID);

    /**
     * @brief Execute payment using the specified e-wallet.
     * @param amount Amount to deduct.
     * @param orderNum The order number linked to the payment.
     */
    void pay(double amount, const std::string& orderNum) const override;

    /**
     * @brief Retrieve the strategy's display name.
     * @return "E-Wallet Payment".
     */
    std::string getName() const override;
};

#endif
