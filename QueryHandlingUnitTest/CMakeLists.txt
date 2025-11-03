cmake_minimum_required(VERSION 3.10)
project(QueryHandlingUnitTest)

# Google Test requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set source directory
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/../SystemFiles)

# Include directories
include_directories(${SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Collect all source files
set(SOURCE_FILES
    ${SOURCE_DIR}/Plant.cpp
    ${SOURCE_DIR}/Staff.cpp
    ${SOURCE_DIR}/FloorStaff.cpp
    ${SOURCE_DIR}/FloorEmployee.cpp
    ${SOURCE_DIR}/FloorManager.cpp
    ${SOURCE_DIR}/SalesStaff.cpp
    ${SOURCE_DIR}/SalesEmployee.cpp
    ${SOURCE_DIR}/SalesManager.cpp
    ${SOURCE_DIR}/Query.cpp
    ${SOURCE_DIR}/Builder.cpp
    ${SOURCE_DIR}/ItemQueryBuilder.cpp
    ${SOURCE_DIR}/Tropical.cpp
    ${SOURCE_DIR}/Sunny.cpp
    ${SOURCE_DIR}/Shade.cpp
    ${SOURCE_DIR}/Temperate.cpp
    ${SOURCE_DIR}/InventoryObserver.cpp
    ${SOURCE_DIR}/PlantInventory.cpp
    ${SOURCE_DIR}/MiscQueryBuilder.cpp
    ${SOURCE_DIR}/AskQuery.cpp
    ${SOURCE_DIR}/PlantState.cpp
    ${SOURCE_DIR}/PlantCareRoutine.cpp
    ${SOURCE_DIR}/LifeCycleObserver.cpp
    ${SOURCE_DIR}/PlantLifeCycle.cpp
    ${SOURCE_DIR}/SalesFloorObserver.cpp

    # newly added stubs
    ${SOURCE_DIR}/AddStock.cpp
    ${SOURCE_DIR}/RemoveStock.cpp
    ${SOURCE_DIR}/MediumWaterStrategy.cpp
    ${SOURCE_DIR}/LowWaterStrategy.cpp
    ${SOURCE_DIR}/PartialSunStrategy.cpp
    ${SOURCE_DIR}/FullSunStrategy.cpp
    ${SOURCE_DIR}/OrganicFertilizer.cpp
    ${SOURCE_DIR}/InorganicFertilizer.cpp
    ${SOURCE_DIR}/ShadeStrategy.cpp
    ${SOURCE_DIR}/SeedState.cpp
    ${SOURCE_DIR}/SeedlingState.cpp
    ${SOURCE_DIR}/MatureState.cpp
    ${SOURCE_DIR}/WitheredState.cpp
    ${SOURCE_DIR}/DistressedState.cpp
)

enable_testing()

add_executable(
    query_handler_test
    QueryHandlingUnitTest.cpp
    ${SOURCE_FILES}
)

target_link_libraries(
    query_handler_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(query_handler_test)