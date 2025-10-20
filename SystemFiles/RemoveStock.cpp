#include "RemoveStock.h"
#include <iostream>

removeStock::removeStock(PlantStock* s, string type, int qty)
    : stock(s), plantType(type), quantity(qty) {}

void removeStock::execute() {
    if (stock)
        stock->removeStock(plantType, quantity);
}
