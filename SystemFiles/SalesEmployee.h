#ifndef SALESEMPLOYEE_H
#define SALESEMPLOYEE_H

#include "SalesStaff.h"
#include<vector>

class SalesEmployee: public SalesStaff{
    private:
        std::vector<std::string>responsibilities;
    
    public:
        SalesEmployee(std::string name);
        virtual ~SalesEmployee();
        bool staffCanHandle(std::string type) override;
        void reply(Query* query) override;
};

#endif // !SALESEMPLOYEE_H