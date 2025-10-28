#ifndef BASEPLANT_H
#define BASEPLANT_H
#include <string>

class BasePlant {
    protected:
    std::string description;
    double price;
    public:
    BasePlant(double p, std::string desc) : price(p), description(desc) {}
    virtual std::string getDescription();
    virtual double getPrice();
    virtual ~BasePlant() {}
};

#endif
