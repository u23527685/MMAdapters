#include"SalesManager.h"
#include <random>
#include<iostream>

SalesManager::SalesManager(std::string name):SalesStaff(name){
    responsibilities.push_back("STOCK");
    responsibilities.push_back("INCOMMING STOCK");
    responsibilities.push_back("OUTGOING STOCK");
    responsibilities.push_back("EVENT PLAN");
    responsibilities.push_back("UPCOMMING SALES");
    responsibilities.push_back("CURRENT SALES");
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