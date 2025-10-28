#include"SalesEmployee.h"
#include <random>
#include<iostream>

SalesEmployee::SalesEmployee(std::string name):SalesStaff(name){
    responsibilities.push_back("STOCK");
    responsibilities.push_back("INCOMMING STOCK");
    responsibilities.push_back("OUTGOING STOCK");
    responsibilities.push_back("CURRENT SALES");
}

SalesEmployee::~SalesEmployee(){
    responsibilities.clear();
}

bool SalesEmployee::staffCanHandle(std::string type){
    for(std::string responsibility : responsibilities ){
        if(type==responsibility)
            return true;
    }
    return false;
}

void SalesEmployee::reply(Query* query){
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}