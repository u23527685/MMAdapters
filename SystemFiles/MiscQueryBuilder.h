#ifndef MISCQUERYBUILDER_H
#define MISCQUERYBUILDER_H
#include "Plant.h"
#include "Builder.h"
#include"Query.h"
#include<string>
class MiscQueryBuilder:public Builder{
    friend Query;
    public:
        void setType(std::string type);
        void setQuestion(std::string question);
        void setItem(Plant* item);
        Query* build();
        MiscQueryBuilder():Builder(){}
};
#endif // !MISCQUERYBUILDER_H