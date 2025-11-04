#pragma once
#include <string>
#include <vector>

class TransactionSnapshot
{
    std::string orderNum;
    double amount;
    int quantity;
    std::vector<std::string> decorations; // added

  public:
    TransactionSnapshot(const std::string &orderNum, double amount,
                        int quantity,
                        const std::vector<std::string> &decorations = {});

    std::string getOrderNum() const;
    double getAmount() const;
    int getQuantity() const;
    const std::vector<std::string> &getDecorations() const; // added
};
