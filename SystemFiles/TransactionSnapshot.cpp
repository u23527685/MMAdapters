#include "TransactionSnapshot.h"

TransactionSnapshot::TransactionSnapshot(const std::string& orderNum, double amount, int quantity)
    : orderNum(orderNum), amount(amount), quantity(quantity) {}

std::string TransactionSnapshot::getOrderNum() const {
    return orderNum;
}

double TransactionSnapshot::getAmount() const {
    return amount;
}

int TransactionSnapshot::getQuantity() const {
    return quantity;
}
