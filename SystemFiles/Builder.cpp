#include "Builder.h"
#include "Query.h" 

Builder::Builder(){
    item=nullptr;
    type="";
    question="";
}

Query* Builder::build(){
    return new Query(this);
}