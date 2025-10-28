#ifndef STOCKCOMMAND_H
#define STOCKCOMMAND_H

class StockCommand {
public:
    // Return true on success, false on failure
    virtual bool execute() = 0;
    virtual ~StockCommand() {}
};

#endif
