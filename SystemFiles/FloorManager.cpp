#include"FloorManager.h"
#include <random>
#include<iostream>

FloorManager::FloorManager(std::string name):FloorStaff(name){
    responsibilities.push_back("FUTURE STOCK");
    responsibilities.push_back("CURRENT STOCK");
    responsibilities.push_back("RECOMENDATIONS");
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
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}