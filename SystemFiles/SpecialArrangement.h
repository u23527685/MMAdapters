#ifndef SPECIAL_ARRANGEMENT_H
#define SPECIAL_ARRANGEMENT_H

#include "PlantDecorator.h"

class SpecialArrangement : public PlantDecorator
{
  public:
    SpecialArrangement(Plant *plant);
    std::string getDescription() const override;
    double getPrice() const override;
};

#endif
