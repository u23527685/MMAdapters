#ifndef FULLSUNSTRATEGY_H
#define FULLSUNSTRATEGY_H

#include "Plant.h"
#include "SunlightStrategy.h"

class FullSunStrategy : public SunlightStrategy{
public:
    void applySunlight(Plant* p) override;
};

#endif