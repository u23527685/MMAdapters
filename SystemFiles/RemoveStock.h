#ifndef REMOVESTOCK_H
#define REMOVESTOCK_H

#include "StockCommand.h"
#include "PlantStock.h"
#include <string>
#include <iostream>

class removeStock : public StockCommand {
    public:
        removeStock(PlantStock* s, std::string type, int qty);
        void execute() override;

    private:
        std::string plantType;
        int quantity;
        PlantStock* stock;
};

#endif
