#include "TransactionSnapshot.h"

TransactionSnapshot::TransactionSnapshot(const std::string &customerName, const std::string &plantName, double amount, int quantity)
    : customerName(customerName), plantName(plantName), amount(amount), quantity(quantity){}

std::string TransactionSnapshot::getCustomerName(){ 
    return customerName; 
}

std::string TransactionSnapshot::getPlantName(){ 
    return plantName; 
}

double TransactionSnapshot::getAmount(){ 
    return amount; 
}

int TransactionSnapshot::getQuantity(){ 
    return quantity; 
}

void TransactionSnapshot::setSnapshot(const std::string &customerName, const std::string &plantName, double amount, int quantity){
    this->customerName = customerName;
    this->plantName = plantName;
    this->amount = amount;
    this->quantity = quantity;
}
