#include"FloorManager.h"
#include <random>
#include<iostream>

FloorManager::FloorManager(std::string name):FloorStaff(name){
    responsibilities.push_back("STOCK");
}

FloorManager::~FloorManager(){
    responsibilities.clear();
}

bool FloorManager::staffCanHandle(std::string type){
    for(std::string responsibility : responsibilities ){
        if(type==responsibility)
            return true;
    }
    return false;
}

void FloorManager::reply(Query* query){
    std::string q= query->getQuestion();
    std::string t=query->getType();
    if(q=="What Stock is comming in"||t=="STOCK"){
        std::cout<<"Floor Manager "<<getName()<<" will answer the query "<<std::endl;
        getStock();
        std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
        return;
    }
    if(q=="What Stock is going out in"||t=="STOCK"){
        std::cout<<"Floor Manager "<<getName()<<" will answer the query "<<std::endl;
        getStock();
        std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
        return;
    }
    if(q=="What is the current Stock"||t=="STOCK"){
        std::cout<<"Floor Manager "<<getName()<<" will answer the query "<<std::endl;
        getStock();
        std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
        return;
    }
    std::cout<<"Floor Manager "<<getName()<<" is passing the task to the next staff member"<<std::endl;
    Staff* next= getNext();
    if(next==nullptr){
        std::cout<<"Sorry we can not handle the query"<<std::endl;
        return;
    }
    next->handleQuery(query);
}