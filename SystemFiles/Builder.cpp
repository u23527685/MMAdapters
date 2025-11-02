<<<<<<< HEAD
#include "Builder.h"
#include "Query.h" 

Builder::Builder(){
    item=nullptr;
    type="";
    question="";
}

Query* Builder::build(){
    return new Query(this);
=======
#include "Builder.h"
#include "Query.h" 

Builder::Builder(){
    item=NULL;
    type="";
    question="";
}

Query* Builder::build(){
    return new Query(this);
>>>>>>> DemoTesting
}