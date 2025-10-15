#ifndef SALESMANAGER_H
#define SALESMANAGER_H

#include "SalesStaff.h"
#include<vector>

class SalesManager: public SalesStaff{
    private:
        std::vector<std::string>responsibilities;
    
    public:
        SalesManager(std::string name);
        virtual ~SalesManager();
        bool staffCanHandle() override;
        void reply() override;
};

#endif // !SALESMANAGER_H