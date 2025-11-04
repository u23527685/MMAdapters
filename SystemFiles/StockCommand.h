/**
 * @file StockCommand.h
 * @brief Abstract base class for stock management commands.
 *
 * Defines the interface for command pattern used in inventory management.
 *
 */
#ifndef STOCKCOMMAND_H
#define STOCKCOMMAND_H

/**
 * @class StockCommand
 * @brief Abstract base class for command pattern in stock management
 * 
 * This interface defines the execute method that all concrete
 * stock commands must implement.
 */
class StockCommand {
public:
    /**
     * @brief Executes the stock command
     * @return true on success, false on failure
     */
    virtual bool execute() = 0;
    
     /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup in derived command classes.
     */
    virtual ~StockCommand() {}
};

#endif
