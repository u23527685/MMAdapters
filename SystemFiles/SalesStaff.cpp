#include"SalesStaff.h"
#include<iostream>

SalesStaff::SalesStaff(std::string name):Staff(name){

}

SalesStaff::~SalesStaff(){}

void SalesStaff::handleQuery(Query* query){
    if(staffCanHandle(query->getType())){
        reply(query);
    }else{
        std::cout<<"Staff memeber "<<getName()<<"can not handle this query"<<std::endl;
        Staff* next= getNext();
        if(next==nullptr){
            std::cout<<"Sorry we can not handle the query"<<std::endl;
            return;
        }
        std::cout<<"Staff memeber "<<getName()<<" is passing the task to the next staff memner"<<std::endl;
        next->handleQuery(query);
    }
}