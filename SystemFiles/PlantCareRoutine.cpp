#include <string>
#include <iostream>
#include "Plant.h"

#include "PlantCareRoutine.h"
#include "Tropical.h"
#include "Sunny.h"
#include "Shade.h"
#include "Temperate.h"


PlantCareRoutine* PlantCareRoutine::PlantCare(Plant* p){
    const std::string& cat = p->getCategory();
    if (cat == "Tropical")   return new Tropical();
    if (cat == "Sunny")      return new Sunny();
    if (cat == "Shade")      return new Shade();
    if (cat == "Temperate")  return new Temperate();
    return nullptr;
}