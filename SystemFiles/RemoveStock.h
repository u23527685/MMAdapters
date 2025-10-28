#ifndef REMOVE_STOCK_H
#define REMOVE_STOCK_H

#include "StockCommand.h"
#include "PlantStock.h"
#include <string>
#include <iostream>
class RemoveStock : public StockCommand {
public:
    RemoveStock(PlantStock* s, std::string type, int quantity);
    void execute() override;

private:
    PlantStock* stock;
    std::string plantType;
    int quantity;
};
#endif