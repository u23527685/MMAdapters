#include "AddStock.h"

AddStock::AddStock(PlantStock* s, std::string type, int quantity)
    : stock(s), plantType(type), quantity(quantity) {}

void AddStock::execute() {
    if (stock)
        stock->addStock(plantType, quantity);
}
