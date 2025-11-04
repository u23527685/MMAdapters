/**
 * @file EFTPaymentStrategy.h
 * @brief Header file for Electronic Funds Transfer payment strategy
 */

#ifndef EFTPAYMENTSTRATEGY_H
#define EFTPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"

/**
 * @class EFTPaymentStrategy
 * @brief Strategy for processing electronic funds transfer payments
 * @details Implements payment processing for bank account transfers
 */
class EFTPaymentStrategy : public PaymentStrategy {
private:
    std::string accountNumber;    ///< Bank account number for transfers

public:
    /**
     * @brief Constructor for EFTPaymentStrategy
     * @param accountNumber The bank account number
     * @return None (constructor)
     */
    EFTPaymentStrategy(const std::string& accountNumber);

    /**
     * @brief Process an EFT payment
     * @param amount The monetary amount to transfer
     * @param orderNum The order number for the transaction
     * @return void
     */
    void pay(double amount, const std::string& orderNum) const override;

    /**
     * @brief Gets the payment method name
     * @return std::string The name "EFT"
     */
    std::string getName() const override;
};

#endif