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
        std::string getType();
        std::string getQuestion();
        Plant* getItem(); 
        void printQuery();
};
#endif // !QUERY_H