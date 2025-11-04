#include "Plant.h"
#include <iostream>
#include <string>

#include "PlantCareRoutine.h"
#include "Shade.h"
#include "Sunny.h"
#include "Temperate.h"
#include "Tropical.h"
#include <memory>

std::unique_ptr<PlantCareRoutine> PlantCareRoutine::PlantCare(Plant *p)
{
    const std::string &cat = p->getCategory();
    if (cat == "Tropical")
        return std::make_unique<Tropical>();
    if (cat == "Sunny")
        return std::make_unique<Sunny>();
    if (cat == "Shade")
        return std::make_unique<Shade>();
    if (cat == "Temperate")
        return std::make_unique<Temperate>();
    return nullptr;
}