#include"FloorEmployee.h"
#include <random>
#include<iostream>


FloorEmployee::FloorEmployee(std::string name):FloorStaff(name){
    responsibilities.push_back("STOCK");
    responsibilities.push_back("INCOMMING STOCK");
    responsibilities.push_back("OUTGOING STOCK");
}

FloorEmployee::~FloorEmployee(){
    responsibilities.clear();
}

bool FloorEmployee::staffCanHandle(std::string type){
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(1, 100);

    int randomNumber = dist(gen);

    return randomNumber%2;
}

void FloorEmployee::reply(Query* query){
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}