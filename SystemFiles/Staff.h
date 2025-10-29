#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <iostream>
#include "Order.h"

#include "PLantLifeCycle.h"
#include "LifeCycleObserver.h"
#include "PlantCareRoutine.h"

class Staff: public LifeCycleObserver {

//C&S Staff implemention
private:
    std::string staffName;
    std::string role;

public:
    Staff();
    Staff(const std::string& name, const std::string& role);
    std::string getName() const;
    std::string getRole() const;
    void setName(const std::string& name);
    void setRole(const std::string& role);
    void respondToQuery(const std::string& queryMessage) const;
    void checkOrderStatus(const Order& order) const;
    
    //Greenhouse Staff implemention
    private:
        Staff* next;
        std::string name;
        PlantCareRoutine* careRoutine;
    public:
        virtual void handleQuery()=0;
        Staff(std::string name);
        virtual ~Staff();
        //std::string getName(); // this is commented out to resolve merge conflicts
        void setNext(Staff* staff);
        Staff* getNext();
        void update(PlantLifeCycle* lifeCycle) override;
};

#endif
