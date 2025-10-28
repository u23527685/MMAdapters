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
    if(q=="What Stock is comming in"){
        /*
        get incoming stock
        */
    }
    if(q=="What Stock is going out in"){
        /*
        get old stock
        */
    }
    if(q=="What is the current Stock"){
        /*
        get current stock
        */
    }
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}