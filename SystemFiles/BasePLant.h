#ifndef BASEPLANT_H
#define BASEPLANT_H
#include <string>
#include "Plant.h"

class BasePlant: public Plant {
    public:
    BasePlant(double p, std::string desc);
    virtual ~BasePlant() {}
    virtual std::string getDescription();
    virtual double getPrice();
};

#endif
