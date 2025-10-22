#include "EFTPaymentStrategy.h"
#include <iostream>

EFTPaymentStrategy::EFTPaymentStrategy(const std::string& accountNumber) : accountNumber(accountNumber) {}

void EFTPaymentStrategy::pay(double amount, const std::string& customerName) {
    std::cout << "Processing EFT payment of $" << amount 
              << " for " << customerName << " using account number: " 
              << accountNumber << std::endl;
}
