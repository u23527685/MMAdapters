#ifndef DECORATIVE_POT_H
#define DECORATIVE_POT_H

#include "PlantDecorator.h"

class DecorativePot : public PlantDecorator {
public:
    DecorativePot(Plant* plant);
    std::string getDescription() const override;
    double getPrice() const override;
};

#endif 
