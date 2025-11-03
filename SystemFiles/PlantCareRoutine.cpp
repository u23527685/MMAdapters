#include <string>
#include <iostream>
#include "Plant.h"

#include "PlantCareRoutine.h"
#include "Tropical.h"
#include "Sunny.h"
#include "Shade.h"
#include "Temperate.h"
#include <memory>


std::unique_ptr<PlantCareRoutine> PlantCareRoutine::PlantCare(Plant* p){
    const std::string& cat = p->getCategory();
    if (cat == "Tropical")   return std::make_unique<Tropical>();
    if (cat == "Sunny")      return std::make_unique<Sunny>();
    if (cat == "Shade")      return std::make_unique<Shade>();
    if (cat == "Temperate")  return std::make_unique<Temperate>();
    return nullptr;
}