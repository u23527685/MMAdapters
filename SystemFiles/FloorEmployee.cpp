#include"FloorEmployee.h"
#include"PlantCareRoutine.h"
#include"Tropical.h"
#include"Temperate.h"
#include"Sunny.h"
#include"Shade.h"
#include <random>
#include<iostream>
#include<string>


FloorEmployee::FloorEmployee(std::string name):FloorStaff(name){
    responsibilities.push_back("INFO");
    responsibilities.push_back("CARE ROUTINE");
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
    if(q=="Describe the plant to me"){
        std::cout<<query->getItem()->getDescription()<<std::endl;
    }
    if(q=="What is the care routine for this plant"){
       PlantCareRoutine* PCR = PlantCareRoutine::PlantCare(query->getItem());
       PCR->printCareRoutine();
    }
    if(q=="What plants do you recomend"){
       std::cout<<"I recommend cactus as they are easy to take care of and they are very stylish"<<std::endl;
    }
    std::cout<<"Floor Employee "<<getName()<<" answered the query "<<std::endl;
}