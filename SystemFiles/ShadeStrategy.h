#ifndef SHADESTRATEGY_H
#define SHADESTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

class ShadeStrategy : public SunlightStrategy{
public:
    void applySunlight(Plant* p) override;
};

#endif