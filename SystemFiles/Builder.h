#ifndef BULDER_H
#define BULDER_H
#include "Plant.h"
#include <string>

class Query;  // Forward declaration - don't include Query.h here

class Builder{
    friend class Query;  // Use 'class' keyword
    protected:
        Plant* item=nullptr;
        std::string type="";
        std::string question="";
    public:
        virtual void setType(std::string type)=0;
        virtual void setQuestion(std::string question)=0;
        virtual void setItem(Plant* item)=0;
        Query* build();
        Builder();
};
#endif // !BUILDER_H