#ifndef ASKQUERY_H
#define ASKQUERY_H

#include"Builder.h"
#include "FloorStaff.h"
#include"ItemQueryBuilder.h"
#include"MiscQueryBuilder.h"
#include "Plant.h"
#include"Query.h"
#include<string>

class AskQuery{
    private:
        Builder* builder;
    public:
        Query* describe(Plant* item);
        Query* careRoutine(Plant* item);
};

#endif // !ASKQUERY_H