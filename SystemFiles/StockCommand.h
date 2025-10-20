#ifndef STOCKCOMMAND_H
#define STOCKCOMMAND_H

class StockCommand {
public:
    virtual void execute() = 0;
    virtual ~StockCommand() = default;
};

#endif
