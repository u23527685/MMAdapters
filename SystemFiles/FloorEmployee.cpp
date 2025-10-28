#include"FloorEmployee.h"
#include <random>
#include<iostream>
#include<string>


FloorEmployee::FloorEmployee(std::string name):FloorStaff(name){
    responsibilities.push_back("INFO");
    responsibilities.push_back("CURRENT STOCK");
    responsibilities.push_back("RECOMENDATIONS");
}

FloorEmployee::~FloorEmployee(){
    responsibilities.clear();
}

bool FloorEmployee::staffCanHandle(std::string type){
    for(std::string responsibility : responsibilities ){
        if(type==responsibility)
            return true;
    }
    return false;
}

void FloorEmployee::reply(Query* query){
    std::string q= query->getQuestion();
    if(q=="Describe the plant to me")
    {
        Plant* item=query->getItem();
    }
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}