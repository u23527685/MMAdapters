#include "RemoveStock.h"

RemoveStock::RemoveStock(PlantStock* s, std::string type, int quantity)
    : stock(s), plantType(type), quantity(quantity) {}

void RemoveStock::execute() {
    if (stock)
        stock->removeStock(plantType, quantity);
}
