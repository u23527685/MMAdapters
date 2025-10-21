#include "AddStock.h"

addStock::addStock(PlantStock* s, string type, int quantity)
    : stock(s), plantType(type), quantity(qty) {}

void addStock::execute() {
    if (stock)
        stock->addStock(plantType, quantity);
}
