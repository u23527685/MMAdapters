#ifndef STAFF_H
#define STAFF_H

#include "PLantLifeCycle.h"
#include "LifeCycleObserver.h"
#include "PlantCareRoutine.h"
#include"Query.h"
#include <iostream>
#include<string>

class Staff : public LifeCycleObserver {
    private:
        Staff* next;
        std::string name;
        PlantCareRoutine* careRoutine;
    public:
        virtual void handleQuery(Query* query)=0;
        Staff(std::string name);
        virtual ~Staff();
        std::string getName();
        void setNext(Staff* staff);
        Staff* getNext();
        void update(PlantLifeCycle* lifeCycle) override;
};

#endif