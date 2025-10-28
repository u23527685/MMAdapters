#include "EWalletPaymentStrategy.h"
#include <iostream>

EWalletPaymentStrategy::EWalletPaymentStrategy(const std::string& walletID) : walletID(walletID) {}

void EWalletPaymentStrategy::pay(double amount, const std::string& customerName) {
    std::cout << "Processing e-wallet payment of R" << amount 
              << " for " << customerName << " using wallet ID: " 
              << walletID << std::endl;
}
