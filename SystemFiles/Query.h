#ifndef QUERY_H
#define QUERY_H
#include "Plant.h"
#include"Builder.h"
#include<string>
class Query{
    protected:
        Plant* item;
        std::string type;
        std::string question;
    
    public:
        Query(Builder* builder);
};
#endif // !QUERY_H