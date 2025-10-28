#ifndef ADD_STOCK_H
#define ADD_STOCK_H

#include "StockCommand.h"
#include "PlantStock.h"
#include <string>
#include <iostream>

class AddStock : public StockCommand {
public:
    AddStock(PlantStock* s, std::string type, int quantity);
    void execute() override;

private:
    PlantStock* stock;
    std::string plantType;
    int quantity;
};


#endif
