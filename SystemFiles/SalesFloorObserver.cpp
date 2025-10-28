#include "SalesFloorObserver.h"

SalesFloorObserver::SalesFloorObserver() {}

SalesFloorObserver::~SalesFloorObserver() {}

void SalesFloorObserver::update() {
    std::cout << "[SalesFloorObserver] Inventory updated - Display updated on sales floor." << std::endl;
}
