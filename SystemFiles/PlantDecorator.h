#ifndef PLANT_DECORATOR_H
#define PLANT_DECORATOR_H

#include "Plant.h"

class PlantDecorator : public Plant
{
  protected:
    Plant *plant;

  public:
    PlantDecorator(Plant *plant);
    virtual ~PlantDecorator();

    virtual std::string getDescription() const override;
    virtual double getPrice() const override;
};

#endif
