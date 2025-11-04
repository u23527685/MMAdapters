#ifndef EWALLETPAYMENTSTRATEGY_H
#define EWALLETPAYMENTSTRATEGY_H

#include "PaymentStrategy.h"

class EWalletPaymentStrategy : public PaymentStrategy
{
  private:
    std::string walletID;

  public:
    EWalletPaymentStrategy(const std::string &walletID);
    void pay(double amount, const std::string &orderNum) const override;
    std::string getName() const override;
};

#endif
