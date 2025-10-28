#include"SalesEmployee.h"
#include <random>
#include<iostream>

SalesEmployee::SalesEmployee(std::string name):SalesStaff(name){
    responsibilities.push_back("FUTURE STOCK");
    responsibilities.push_back("CURRENT STOCK");
    responsibilities.push_back("DEALS");
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