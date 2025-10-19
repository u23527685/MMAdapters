#ifndef PARTIALSUNSTRATEGY_H
#define PARTIALSUNSTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

class PartialSunStrategy : public SunlightStrategy{
public:
    void applySunlight(Plant* p) override;
};

#endif