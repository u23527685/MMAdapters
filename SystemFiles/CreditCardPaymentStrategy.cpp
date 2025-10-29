#include "CreditCardPaymentStrategy.h"
#include <iostream>

CreditCardPaymentStrategy::CreditCardPaymentStrategy(const std::string& cardNumber) : cardNumber(cardNumber) {}

void CreditCardPaymentStrategy::pay(double amount, const std::string& orderNum) const {
    std::cout << "Processing credit card payment of R" << amount 
              << " for order " << orderNum << " using card number: " 
              << cardNumber << std::endl;
}


