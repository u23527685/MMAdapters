#include"MiscQueryBuilder.h"
#include <iostream>

void MiscQueryBuilder::setQuestion(std::string question){
    this->question=question;
}


void MiscQueryBuilder::setType(std::string type){
    this->type=type;
}

void MiscQueryBuilder::setItem(Plant* item){
    std::cout<<"MiscQuery does not support items";
}