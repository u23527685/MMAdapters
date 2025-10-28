#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
public:
    virtual ~Plant() = default;
    virtual std::string getDescription() const = 0;
    virtual double getPrice() const = 0;
};

#endif 
