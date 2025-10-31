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
    std::string t=query->getType();
    Plant* i=query->getItem();
    if(q=="What Stock is going out"||t=="SALES"){
        std::cout<<"Sales Employee "<<getName()<<" will answer the query "<<std::endl;
        getStock();
        std::cout<<"Sales Employee "<<getName()<<" answered the query "<<std::endl;
        return;
    }
    if(q=="What is the current Stock"||t=="SALES"){
        std::cout<<"Sales Employee "<<getName()<<" will answer the query "<<std::endl;
        getStock();
        std::cout<<"Sales Employee "<<getName()<<" answered the query "<<std::endl;
        return;
    }
    if(q=="What deals are there currently"||t=="DEALS"){
        std::cout<<"Sales Employee "<<getName()<<" will answer the query "<<std::endl;
        std::cout<<"We have no deals at the moment. If you want information for any upcoming deals and promotions please leave us your email address"<<std::endl;
        std::cout<<"Sales Employee "<<getName()<<" answered the query "<<std::endl;
        return;
    }
    if(q=="What are the curent sales"||t=="SALES"){
        std::cout<<"Sales Employee "<<getName()<<" will answer the query "<<std::endl;
        std::cout<<"I can not expose current sales to the customer"<<std::endl;
        std::cout<<"Sales Employee "<<getName()<<" answered the query "<<std::endl;
        return;
    }
    std::cout<<"Sales Employee "<<getName()<<" is passing the task to the next staff member"<<std::endl;
    Staff* next= getNext();
    if(next==nullptr){
        std::cout<<"Sorry we can not handle the query"<<std::endl;
        return;
    }
    next->handleQuery(query);
    
}