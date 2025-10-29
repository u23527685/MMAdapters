#ifndef SALESSTAFF_H
#define SALESSTAFF_H

#include "Staff.h"

class SalesStaff:public Staff{
    public:
        SalesStaff(std::string name);
        virtual ~SalesStaff();
        void handleQuery(Query* query) override;
        virtual bool staffCanHandle(std::string type)=0;
        virtual void reply(Query* query)=0;
};

#endif 