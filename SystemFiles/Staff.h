#ifndef STAFF_H
#define STAFF_H

#include<string>

class Staff{
    private:
        Staff* next;
        std::string name;

    public:
        virtual void handleQuery()=0;
        Staff(std::string name);
        virtual ~Staff();
        std::string getName();
        void setNext(Staff* staff);
        Staff* getNext();
};

#endif