#include"AskQuery.h"

Query* AskQuery::describe(Plant* item){
    builder= new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("INFO");
    builder->setQuestion("Describe the plant to me");
    Query *q=builder->build();
    delete builder;
    builder = nullptr;
    return q;
}

Query* AskQuery::careRoutine(Plant* item){
    builder= new ItemQueryBuilder();
    builder->setItem(item);
    builder->setType("CARE ROUTINE");
    builder->setQuestion("What is the care routine for this plant");
    Query *q=builder->build();
    delete builder;
    builder = nullptr;
    return q;
}
