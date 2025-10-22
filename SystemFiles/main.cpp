#include <iostream>
#include <vector>

#include "BasePlant.h"
#include "GiftWrap.h"
#include "DecorativePot.h"
#include "SpecialArrangement.h"

int main() {
    std::vector<Plant*> plants;

    plants.push_back(new GiftWrap(new BasePlant()));
    plants.push_back(new DecorativePot(new GiftWrap(new BasePlant())));
    plants.push_back(new SpecialArrangement(new DecorativePot(new GiftWrap(new BasePlant()))));

    for (const auto& plant : plants) {
        std::cout << plant->getDescription() << " | R" << plant->getPrice() << std::endl;
    }

    for (auto& plant : plants) {
        delete plant;
    }

    return 0;
}
