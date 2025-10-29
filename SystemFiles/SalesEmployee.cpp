#include"SalesEmployee.h"
#include <random>
#include<iostream>

SalesEmployee::SalesEmployee(std::string name):SalesStaff(name){
    responsibilities.push_back("STOCK");
    responsibilities.push_back("DEALS");
    responsibilities.push_back("SALES");
}

SalesEmployee::~SalesEmployee(){
    responsibilities.clear();
}

bool SalesEmployee::staffCanHandle(std::string type){
    for(std::string responsibility : responsibilities ){
        if(type==responsibility)
            return true;
    }
    return false;
}

void SalesEmployee::reply(Query* query){
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
    std::cout<<"Sales Employee "<<getName()<<" answered the query "<<std::endl;
}