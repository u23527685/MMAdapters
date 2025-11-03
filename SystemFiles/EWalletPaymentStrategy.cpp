#include "EWalletPaymentStrategy.h"
#include <iostream>

EWalletPaymentStrategy::EWalletPaymentStrategy(const std::string& walletID) : walletID(walletID) {}

void EWalletPaymentStrategy::pay(double amount, const std::string& orderNum) const {
    std::cout << "Processing e-wallet payment of R" << amount 
              << " for order " << orderNum << " using wallet ID: " 
              << walletID << std::endl;
}
