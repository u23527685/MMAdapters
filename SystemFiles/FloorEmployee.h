#ifndef FLOOREMPLOYEE_H
#define FLOOREMPLOYEE_H

#include "FloorStaff.h"
#include<vector>
#include<string>

class FloorEmployee: public FloorStaff{
    private:
        std::vector<std::string>responsibilities;
    
    public:
        FloorEmployee(std::string name);
        virtual ~FloorEmployee();
        bool staffCanHandle(std::string type) override;
        void reply(Query* query) override;
};

#endif // !FLOOREMPLOYEE_H