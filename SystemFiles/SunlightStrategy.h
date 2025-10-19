#ifndef SUNLIGHTSTRATEGY_H
#define SUNLIGHTSTRATEGY_H

#include "Plant.h"

class SunlightStrategy{
protected:
    Plant* currentPlant;
public:
    virtual void applySunlight(Plant* p) =0;
};

#endif