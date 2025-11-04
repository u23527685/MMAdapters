#include "FloorEmployee.h"
#include "PlantCareRoutine.h"
#include "Shade.h"
#include "Sunny.h"
#include "Temperate.h"
#include "Tropical.h"
#include <iostream>
#include <random>
#include <string>

FloorEmployee::FloorEmployee(std::string name) : FloorStaff(name)
{
    responsibilities.push_back("INFO");
    responsibilities.push_back("CARE ROUTINE");
    responsibilities.push_back("RECOMMENDATIONS");
}

FloorEmployee::~FloorEmployee() { responsibilities.clear(); }

bool FloorEmployee::staffCanHandle(std::string type)
{
    for (std::string responsibility : responsibilities)
    {
        if (type == responsibility)
            return true;
    }
    return false;
}

void FloorEmployee::reply(Query *query)
{
    std::string q = query->getQuestion();
    std::string t = query->getType();
    Plant *i = query->getItem();
    if (q == "Describe the plant to me" || t == "INFO")
    {
        std::cout << "Floor Employee " << getName() << " will answer the query "
                  << std::endl;
        if (i)
        {
            std::cout << i->getDescription() << std::endl;
            std::cout << "Floor Employee " << getName()
                      << " answered the query " << std::endl;
            return;
        }
        std::cout << "You did not add an item to ask about, please add the "
                     "item and ask the query again"
                  << std::endl;
        return;
    }
    if (q == "What is the care routine for this plant" || t == "CARE ROUTINE")
    {
        std::cout << "Floor Employee " << getName() << " will answer the query "
                  << std::endl;
        if (i)
        {
            auto PCR = PlantCareRoutine::PlantCare(i);
            PCR->printCareRoutine();
            std::cout << "Floor Employee " << getName()
                      << " answered the query " << std::endl;
            return;
        }
        std::cout << "You did not add an item to ask about, please add the "
                     "item and ask the query again"
                  << std::endl;
        return;
    }
    if (q == "What plants do you recomend" || t == "RECOMMENDATIONS")
    {
        std::cout << "Floor Employee " << getName() << " will answer the query "
                  << std::endl;
        std::cout << "I recommend cactus as they are easy to take care of and "
                     "they are very stylish"
                  << std::endl;
        std::cout << "Floor Employee " << getName() << " answered the query "
                  << std::endl;
        return;
    }
    std::cout << "Floor Employee " << getName()
              << " is passing the task to the next staff member" << std::endl;
    Staff *next = getNext();
    if (next == nullptr)
    {
        std::cout << "Sorry we can not handle the query" << std::endl;
        return;
    }
    next->handleQuery(query);
}