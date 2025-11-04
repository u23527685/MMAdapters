/**
 * @file EFTPaymentStrategy.h
 * @brief Concrete payment strategy using Electronic Funds Transfer (EFT).
 *
 * Implements the PaymentStrategy interface for EFT-based payments.
 * Stores an account number and handles electronic transfers.
 *
 * @author
 * Jerusha Thaver
 */
#ifndef EFTPAYMENTSTRATEGY_H
#define EFTPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"

/**
 * @class EFTPaymentStrategy
 * @brief Payment strategy implementation for EFT transactions.
 *
 * Handles payments made via direct bank transfers using an account number.
 */
class EFTPaymentStrategy : public PaymentStrategy {
private:
    std::string accountNumber; /**< Account number used for the EFT payment. */
public:
    /**
     * @brief Construct an EFTPaymentStrategy with a specific account number.
     * @param accountNumber Bank account number used for transfer.
     */
    EFTPaymentStrategy(const std::string& accountNumber);

    /**
     * @brief Process a payment via EFT.
     * @param amount Amount to transfer.
     * @param orderNum Associated order number.
     */
    void pay(double amount, const std::string& orderNum) const override;

     /**
     * @brief Retrieve the strategy's display name.
     * @return "EFT Payment".
     */
    std::string getName() const override;
};

#endif
