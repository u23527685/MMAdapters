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

void Query::printQuery(){
    std::cout<<"Item : "<< item->getName()<<std::end;
    std::cout<<"Type : "<<getType()<<std::endl;
    std::cout<<"Question : "<< getQuestion()<<std::end;
}