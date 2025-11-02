cmake_minimum_required(VERSION 3.22)
project(SystemFiles)

set(CMAKE_CXX_STANDARD 17)

add_executable(SystemFiles
        FertilizerStrategy.cpp
        FertilizerStrategy.h
        InorganicFertilizer.h
        InorganicFertilizer.cpp
        OrganicFertilizer.cpp
        OrganicFertilizer.h
        WateringStrategy.cpp
        WateringStrategy.h
        LowWaterStrategy.cpp
        LowWaterStrategy.h
        HighWaterStrategy.cpp
        HighWaterStrategy.h
        MediumWaterStrategy.cpp
        MediumWaterStrategy.h
        SunlightStrategy.cpp
        SunlightStrategy.h
        ShadeStrategy.cpp
        ShadeStrategy.h
        PartialSunStrategy.cpp
        PartialSunStrategy.h
        FullSunStrategy.cpp
        FullSunStrategy.h

        Plant.cpp
        Plant.h

        PlantState.h
        PlantState.cpp
        SeedState.h
        SeedState.cpp
        SeedlingState.h
        SeedlingState.cpp
        MatureState.h
        MatureState.cpp
        DistressedState.h
        DistressedState.cpp
        WitheredState.h
        WitheredState.cpp

        TestingState.cpp


        PLantLifeCycle.h
        PlantLifeCycle.cpp

        Staff.h
        Staff.cpp

        StaffObserver.h

        PlantCareRoutine.h
        PlantCareRoutine.cpp

        LifeCycleObserver.h
        LifeCycleObserver.cpp
)
