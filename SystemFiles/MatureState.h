/**
 * @file MatureState.h
 * @brief Defines the MatureState class representing a plant’s healthy phase.
 *
 * In this state, the plant thrives under regular care and sustenance.
 * If its resources fall below minimum thresholds, it transitions to DistressedState.
 *
 */
#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantCareRoutine.h"
#include "PLantLifeCycle.h"
#include "PlantState.h"

/**
 * @class MatureState
 * @brief Represents a thriving stage in the plant’s life cycle.
 */
class MatureState : public PlantState {
public:
    void applyCare(PlantLifeCycle* context, Plant* plant, PlantCareRoutine* routine) override;
    bool evaluate(PlantLifeCycle* context, Plant* plant) override;
    std::string getName() const override;
    PlantState* clone() const override;
};

#endif