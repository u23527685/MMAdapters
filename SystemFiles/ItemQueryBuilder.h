#ifndef ITEMQUERYBULDER_H
#define ITEMQUERYBULDER_H
#include "Plant.h"
#include "Builder.h"
#include"Query.h"
#include<string>
class ItemQueryBuilder:public Builder{
    friend Query;
    public:
        void setType(std::string type);
        void setQuestion(std::string question);
        void setItem(Plant* item);
        Query* build();
        ItemQueryBuilder():Builder(){}
};
#endif // !ITEMQUERYBULDER_H