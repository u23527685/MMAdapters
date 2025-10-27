#ifndef SALESSTAFF_H
#define SALESSTAFF_H

#include "Staff.h"

class SalesStaff:public Staff{
    public:
        SalesStaff(std::string name);
        virtual ~SalesStaff();
        void handleQuery(Query* query) override;
        virtual bool staffCanHandle()=0;
        virtual void reply()=0;
};

#endif 