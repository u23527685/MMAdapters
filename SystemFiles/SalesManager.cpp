#include"SalesManager.h"
#include <random>
#include<iostream>

SalesManager::SalesManager(std::string name):SalesStaff(name){
    responsibilities.push_back("STOCK");
    responsibilities.push_back("DEALS");
    responsibilities.push_back("SALES");
    responsibilities.push_back("EVENT");
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
    std::string q= query->getQuestion();
    if(q=="What Stock is going out"){
        getStock();
    }
    if(q=="What is the current Stock"){
        getStock();
    }
    if(q=="What deals are there currently"){
        std::cout<<"We have no deals at the moment. If you want information for any upcoming deals and promotions please leave us your email address"<<std::endl;
    }
    if(q=="What are the curent sales"){
        
       std::cout<<"I can not expose current sales to the customer"<<std::endl;
    }
    if(query->getType()=="EVENT"){
        std::cout<<"Please email us your event plans so that we can better handle your request and show you our options"<<std::endl;
    }
    std::cout<<"Sales Manager "<<getName()<<" answered the query "<<std::endl;
}