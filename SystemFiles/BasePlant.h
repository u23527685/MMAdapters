#ifndef BASEPLANT_H
#define BASEPLANT_H
#include <string>
#include "Plant.h"

class BasePlant: public Plant {
    public:
    BasePlant();
    BasePlant(double p, std::string desc);
    virtual ~BasePlant() {}
    std::string getDescription() const override;
    double getPrice() const override;

    
};

#endif
