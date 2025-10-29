#ifndef ROSE_H
#define ROSE_H
#include "Plant.h"

class Rose : public Plant {
    protected:
    double price;
    std::string description;
    public:
    Rose(double price, std::string description) : Plant(price, description) {}
};

#endif 
