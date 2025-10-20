#ifndef STAFF_H
#define STAFF_H

#include <iostream>

class State;
class PlantLifeCycle;

class Staff {
    public:
        void update();
        void handleQuery();

    private:
        State* observerState;
        PlantLifeCycle* plant;
        Staff* next;
};

#endif
