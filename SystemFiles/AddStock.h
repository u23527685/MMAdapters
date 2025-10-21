#ifndef ADD_STOCK_H
#define ADD_STOCK_H

#include "StockCommand.h"
#include "PlantStock.h"
#include <string>
#include <iostream>

class addStock : public StockCommand {
    public:
        addStock(PlantStock* s, std::string type, int quantity);
        void execute() override;

    private:
        std::string plantType;
        int quantity;
        PlantStock* stock;
};

#endif
