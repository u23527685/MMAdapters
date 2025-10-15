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

bool SalesManager::staffCanHandle(){
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(1, 100);

    int randomNumber = dist(gen);

    return randomNumber%2;
}

void SalesManager::reply(){
    std::cout<<"Floor Manager "<<getName()<<" answered the query "<<std::endl;
}