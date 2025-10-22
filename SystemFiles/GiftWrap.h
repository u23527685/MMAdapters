#ifndef GIFT_WRAP_H
#define GIFT_WRAP_H

#include "PlantDecorator.h"

class GiftWrap : public PlantDecorator {
public:
    GiftWrap(Plant* plant);
    std::string getDescription() const override;
    double getPrice() const override;
};

#endif // GIFT_WRAP_H
