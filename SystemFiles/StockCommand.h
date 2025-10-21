#ifndef STOCKCOMMAND_H
#define STOCKCOMMAND_H

#include <iostream>
#include <string>

class StockCommand {
public:
    virtual void execute() = 0;
    virtual ~StockCommand() = default;
};

#endif
