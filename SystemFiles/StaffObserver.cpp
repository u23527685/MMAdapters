#include "StaffObserver.h"

StaffObserver::StaffObserver() {}

StaffObserver::~StaffObserver() {}

void StaffObserver::update() {
    std::cout << "[StaffObserver] Inventory updated - Staff notified of stock changes." << std::endl;
}
