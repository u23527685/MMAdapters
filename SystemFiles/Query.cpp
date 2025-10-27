#include"Query.h"

Query::Query(Builder* builder){
    this->item=builder->item;
    type=builder->type;
    question=builder->question;
}

std::string Query::getType(){
    return type;
}

std::string Query::getQuestion(){
    return question;
}

Plant* Query::getItem(){
    return item;
}