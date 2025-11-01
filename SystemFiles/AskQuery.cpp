#include"AskQuery.h"

Query* AskQuery::describe(Plant* item){
    builder= new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("INFO");
    Query *q=builder->build();
    delete builder;
    return q;
}

Query* AskQuery::careRoutine(Plant* item){
    builder= new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("CARE ROUTINE");
    Query *q=builder->build();
    delete builder;
    return q;
}

Query* AskQuery::stockInfo(){
    builder= new MiscQueryBuilder();
    builder->setType("STOCK");
    Query *q=builder->build();
    delete builder;
    return q;
}