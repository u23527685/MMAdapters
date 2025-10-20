#ifndef PLANTSTOCK_H
#define PLANTSTOCK_H

#include <string>
#include <iostream>

class PlantStock {
    public:
        bool addStock(std::string plantName, int quantity);
        bool removeStock(std::string plantName, int quantity);
};

#endif
