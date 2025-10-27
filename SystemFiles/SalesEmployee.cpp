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
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(1, 100);

    int randomNumber = dist(gen);

    return randomNumber%2;
}

void SalesEmployee::reply(Query* query){
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}