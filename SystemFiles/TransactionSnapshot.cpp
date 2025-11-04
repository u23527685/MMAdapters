#include "TransactionSnapshot.h"

TransactionSnapshot::TransactionSnapshot(
    const std::string &orderNum, double amount, int quantity,
    const std::vector<std::string> &decorations)
    : orderNum(orderNum), amount(amount), quantity(quantity),
      decorations(decorations)
{
}

std::string TransactionSnapshot::getOrderNum() const { return orderNum; }

double TransactionSnapshot::getAmount() const { return amount; }

int TransactionSnapshot::getQuantity() const { return quantity; }

const std::vector<std::string> &TransactionSnapshot::getDecorations() const
{
    return decorations;
}
