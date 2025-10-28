#include <string>
#include <iostream>
#include "Plant.h"

#include "PlantCareRoutine.h"


PlantCareRoutine* PlantCareRoutine::PlantCare(Plant* p){

    delete PCR;
    PCR = nullptr;
    if(p->getName() == "Rose" || p->getName() == "rose"){
        //PCR = new RoseCare;
    } else if(p->getName() == "Oak" || p->getName() == "oak"){
        //PCR = new OakCare;
    } else if(p->getName() == "Mint" || p->getName() == "mint" ){
        //PCR = new MintCare;
    } else if(p->getName() == "Cactus" || p->getName() == "cactus" ){
        //PCR = new CactusCare;
    } else {
        std::cout << "We're Sorry, The Nursery doesn't house that kind of plant..." << std::endl;
    }

    return 0;
}