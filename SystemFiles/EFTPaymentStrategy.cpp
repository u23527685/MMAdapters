#include "EFTPaymentStrategy.h"
#include <iostream>

EFTPaymentStrategy::EFTPaymentStrategy(const std::string& accountNumber) : accountNumber(accountNumber) {}

void EFTPaymentStrategy::pay(double amount, const std::string& orderNum) const {
    std::cout << "Processing EFT payment of R" << amount 
              << " for order " << orderNum << " using account number: " 
              << accountNumber << std::endl;
}
