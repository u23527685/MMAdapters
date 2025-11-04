/**
 * @file Staff.h
 * @brief Abstract base class for staff members and lifecycle observers.
 *
 * This header declares Staff, the common base for all personnel types in the
 * system. Staff inherits from LifeCycleObserver so that staff members can
 * observe plant lifecycle events and apply care routines. It also provides a
 * simple chain-of-responsibility mechanism by linking to a "next" staff
 * member for query escalation.
 *
 * @see LifeCycleObserver
 */
#ifndef STAFF_H
#define STAFF_H

#include "LifeCycleObserver.h"
#include "PLantLifeCycle.h"
#include "PlantCareRoutine.h"
#include "Query.h"
#include <iostream>
#include <string>

class SalesFloorObserver;

/**
 * @class Staff
 * @brief Base class representing a staff member and lifecycle observer.
 *
 * Inheritance:
 *  - Staff : LifeCycleObserver
 *
 * Data members:
 *  - next: pointer to the next Staff in the chain (non-owning).
 *  - name: human-readable staff member name.
 *  - careRoutine: optional PlantCareRoutine associated with this staff member.
 *  - salesFloorObserver: optional observer used for sales-floor notifications.
 */
class Staff : public LifeCycleObserver
{
  private:
    Staff *next;      /**< Non-owning pointer to next staff in chain */
    std::string name; /**< Staff member's name */
    PlantCareRoutine *careRoutine; /**< Optional care routine (non-owning) */
    SalesFloorObserver
        *salesFloorObserver; /**< Optional sales-floor observer (non-owning) */

  public:
    /**
     * @brief Request stock information or trigger stock-related behaviour.
     * @param plant Plant for which to get stock information.
     *
     * Concrete implementations or callers may use this hook to fetch or
     * report stock data. Default behaviour is implementation-specific.
     */
    void getStock(Plant *plant);

    /**
     * @brief Handle an incoming Query.
     *
     * This pure virtual function must be implemented by concrete staff
     * types to process or forward Query objects. Implementations are
     * responsible for deciding whether to reply or pass the query on.
     *
     * @param query Non-owning pointer to the Query to handle.
     */
    virtual void handleQuery(Query *query) = 0;

    /**
     * @brief Construct a Staff instance with the given name.
     * @param name Human-readable name of the staff member.
     */
    Staff(std::string name);

    /**
     * @brief Virtual destructor.
     *
     * Ensures derived destructors are invoked correctly.
     */
    virtual ~Staff();

    /**
     * @brief Get this staff member's name.
     * @return Name string.
     */
    std::string getName();

    /**
     * @brief Set the next staff member in the chain-of-responsibility.
     *
     * The Staff class does not take ownership of the provided pointer.
     *
     * @param staff Non-owning pointer to the next Staff.
     */
    void setNext(Staff *staff);

    /**
     * @brief Get the next staff member in the chain.
     * @return Non-owning pointer to the next Staff, or nullptr if none.
     */
    Staff *getNext();

    /**
     * @brief Notification callback from PlantLifeCycle to indicate health
     * state.
     *
     * As part of the LifeCycleObserver interface, this method is invoked
     * when observed PlantLifeCycle instances produce lifecycle events.
     * Implementations can use careRoutine to adjust or log plant care state.
     *
     * @param lifeCycle Pointer to the PlantLifeCycle that triggered the update.
     */
    void isHealthy(PlantLifeCycle *lifeCycle);
};

#endif // STAFF_H
