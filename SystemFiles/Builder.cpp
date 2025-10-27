#include"Builder.h"

Builder::Builder(){
    item=NULL;
    type="";
    question="";
}

Query* Builder::build(){
    return new Query(this);
}