#ifndef OAK_H
#define OAK_H
#include "Plant.h"

class Oak : public Plant {
    public:
    Oak(double price, std::string description) : Plant(price, description) {}
};

#endif
