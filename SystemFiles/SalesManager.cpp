#include"SalesManager.h"
#include <random>
#include<iostream>

SalesManager::SalesManager(std::string name):SalesStaff(name){
    responsibilities.push_back("FUTURE STOCK");
    responsibilities.push_back("CURRENT STOCK");
    responsibilities.push_back("DEALS");
    responsibilities.push_back("CURRENT SALES");
    responsibilities.push_back("EVENT PLAN");
}

SalesManager::~SalesManager(){
    responsibilities.clear();
}

bool SalesManager::staffCanHandle(std::string type){
    for(std::string responsibility : responsibilities ){
        if(type==responsibility)
            return true;
    }
    return false;
}

void SalesManager::reply(Query* query){
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}