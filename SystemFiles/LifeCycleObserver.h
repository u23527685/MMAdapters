#ifndef LIFECYCLEOBSERVER_H
#define LIFECYCLEOBSERVER_H

#include "PlantLifeCycle.h"

class PlantLifeCycle;

class LifeCycleObserver{
    public:
    virtual void update(PlantLifeCycle* p);
    virtual ~LifeCycleObserver() {}
};

#endif