#include "AddStock.h"
#include <iostream>

addStock::addStock(PlantStock* s, string type, int qty)
    : stock(s), plantType(type), quantity(qty) {}

void addStock::execute() {
    if (stock)
        stock->addStock(plantType, quantity);
}
