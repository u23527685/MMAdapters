#include"FloorManager.h"
#include <random>
#include<iostream>

FloorManager::FloorManager(std::string name):FloorStaff(name){
    responsibilities.push_back("STOCK");
    responsibilities.push_back("INCOMMING STOCK");
    responsibilities.push_back("OUTGOING STOCK");
    responsibilities.push_back("EVENT PLAN");
    responsibilities.push_back("STOCK");
}

FloorManager::~FloorManager(){
    responsibilities.clear();
}

bool FloorManager::staffCanHandle(){
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(1, 100);

    int randomNumber = dist(gen);

    return randomNumber%2;
}

void FloorManager::reply(){
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}