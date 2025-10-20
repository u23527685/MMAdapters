#include "Staff.h"
#include <iostream>

void Staff::update() {
    std::cout << "[Staff] Update received." << std::endl;
}

void Staff::handleQuery() {
    std::cout << "[Staff] Handling query..." << std::endl;
}
