#include"ItemQueryBuilder.h"

void ItemQueryBuilder::setQuestion(std::string question){
    this->question=question;
}


void ItemQueryBuilder::setType(std::string type){
    this->type=type;
}

void ItemQueryBuilder::setItem(Plant* item){
    this->item=item;
}