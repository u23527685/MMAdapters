#ifndef FLOOREMPLOYEE_H
#define FLOOREMPLOYEE_H

#include "FloorStaff.h"
#include<vector>

class FloorEmployee: public FloorStaff{
    private:
        std::vector<std::string>responsibilities;
    
    public:
        FloorEmployee(std::string name);
        virtual ~FloorEmployee();
        bool staffCanHandle() override;
        void reply() override;
};

#endif // !FLOOREMPLOYEE_H