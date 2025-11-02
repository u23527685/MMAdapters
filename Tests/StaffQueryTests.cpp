#include <gtest/gtest.h>
#include "../SystemFiles/FloorEmployee.h"
#include "../SystemFiles/FloorManager.h"
#include "../SystemFiles/SalesEmployee.h"
#include "../SystemFiles/SalesManager.h"
#include "../SystemFiles/AskQuery.h"
#include "../SystemFiles/Plant.h"
#include "../SystemFiles/Rose.h"
#include "../SystemFiles/MiscQueryBuilder.h"

class StaffQueryTest : public ::testing::Test {
protected:
    FloorEmployee* floorEmp;
    FloorManager* floorMgr;
    SalesEmployee* salesEmp;
    SalesManager* salesMgr;
    Plant* testPlant;
    Rose* testRose;
    AskQuery* queryBuilder;

    void SetUp() override {
        floorEmp = new FloorEmployee(std::string("John"));
        floorMgr = new FloorManager(std::string("Mike"));
        salesEmp = new SalesEmployee(std::string("Sarah"));
        salesMgr = new SalesManager(std::string("Lisa"));
        
        // Set up chain of responsibility
        floorEmp->setNext(floorMgr);
        floorMgr->setNext(salesEmp);
        salesEmp->setNext(salesMgr);

        // Create test plants with price and description
        testPlant = new Plant(29.99, "Generic Test Plant");
        testRose = new Rose(49.99, "Red Rose");
        queryBuilder = new AskQuery();
    }

    void TearDown() override {
        delete floorEmp;
        delete floorMgr;
        delete salesEmp;
        delete salesMgr;
        delete testPlant;
        delete testRose;
        delete queryBuilder;
    }
};

// Test plant properties
TEST_F(StaffQueryTest, PlantProperties) {
    EXPECT_EQ(testPlant->getPrice(), 29.99);
    EXPECT_EQ(testPlant->getDescription(), "Generic Test Plant");
    EXPECT_EQ(testPlant->getCategory(), "generic");
}

// Test rose properties
TEST_F(StaffQueryTest, RoseProperties) {
    EXPECT_EQ(testRose->getPrice(), 49.99);
    EXPECT_EQ(testRose->getDescription(), "Red Rose");
}

// Test plant care parameters
TEST_F(StaffQueryTest, PlantCareParameters) {
    // Verify current Plant defaults (adjusted to match implementation)
    EXPECT_EQ(testPlant->getMaxWater(), 100);
    EXPECT_EQ(testPlant->getMaxSunlight(), 100);
    EXPECT_EQ(testPlant->getMaxNutrients(), 100);
    EXPECT_EQ(testPlant->getMinWater(), 0);
    EXPECT_EQ(testPlant->getMinSunlight(), 0);
    EXPECT_EQ(testPlant->getMinNutrients(), 0);
}

// Test plant state changes
TEST_F(StaffQueryTest, PlantStateChanges) {
    // Set values within valid range and verify they are stored
    testPlant->setCurrentWater(80);
    testPlant->setCurrentSunlight(75);
    testPlant->setCurrentNutrients(60);
    EXPECT_EQ(testPlant->getCurrentWater(), 80);
    EXPECT_EQ(testPlant->getCurrentSunlight(), 75);
    EXPECT_EQ(testPlant->getCurrentNutrients(), 60);

    // Setting values above max should clamp to the configured maxima
    testPlant->setCurrentWater(150);
    testPlant->setCurrentSunlight(175);
    testPlant->setCurrentNutrients(125);
    EXPECT_EQ(testPlant->getCurrentWater(), testPlant->getMaxWater());
    EXPECT_EQ(testPlant->getCurrentSunlight(), testPlant->getMaxSunlight());
    EXPECT_EQ(testPlant->getCurrentNutrients(), testPlant->getMaxNutrients());
}

// Original staff query tests
TEST_F(StaffQueryTest, FloorEmployeeHandlesInfo) {
    Query* infoQuery = queryBuilder->describe(testPlant);
    EXPECT_TRUE(floorEmp->staffCanHandle(std::string("INFO")));
    delete infoQuery;
}

TEST_F(StaffQueryTest, FloorManagerHandlesStock) {
    Query* stockQuery = queryBuilder->stockInfo();
    EXPECT_TRUE(floorMgr->staffCanHandle(std::string("STOCK")));
    delete stockQuery;
}

TEST_F(StaffQueryTest, QueryChainOfResponsibility) {
    Query* salesQuery = queryBuilder->stockInfo();
    testing::internal::CaptureStdout();
    
    floorEmp->handleQuery(salesQuery);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("passing the task") != std::string::npos);
    delete salesQuery;
}

TEST_F(StaffQueryTest, QueryConstruction) {
    Query* infoQuery = queryBuilder->describe(testPlant);
    EXPECT_EQ(infoQuery->getType(), "INFO");
    EXPECT_EQ(infoQuery->getItem(), testPlant);
    delete infoQuery;
}

TEST_F(StaffQueryTest, StaffNameAndNext) {
    EXPECT_EQ(floorEmp->getName(), "John");
    EXPECT_EQ(floorEmp->getNext(), floorMgr);
}

// New miscellaneous query tests
TEST_F(StaffQueryTest, SalesEmployeeHandlesDeals) {
    MiscQueryBuilder builder;
    builder.setType("DEALS");
    builder.setQuestion("What deals are there currently");
    Query* dealsQuery = builder.build();
    
    testing::internal::CaptureStdout();
    salesEmp->handleQuery(dealsQuery);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(salesEmp->staffCanHandle("DEALS"));
    EXPECT_TRUE(output.find("upcoming deals and promotions") != std::string::npos);
    delete dealsQuery;
}

TEST_F(StaffQueryTest, SalesManagerHandlesEvents) {
    MiscQueryBuilder builder;
    builder.setType("EVENT");
    Query* eventQuery = builder.build();
    
    testing::internal::CaptureStdout();
    salesMgr->handleQuery(eventQuery);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(salesMgr->staffCanHandle("EVENT"));
    EXPECT_TRUE(output.find("event plans") != std::string::npos);
    delete eventQuery;
}

TEST_F(StaffQueryTest, FloorEmployeeHandlesRecommendations) {
    MiscQueryBuilder builder;
    builder.setType("RECOMMENDATIONS");
    builder.setQuestion("What plants do you recommend");
    Query* recQuery = builder.build();
    
    testing::internal::CaptureStdout();
    floorEmp->handleQuery(recQuery);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(floorEmp->staffCanHandle("RECOMMENDATIONS"));
    EXPECT_TRUE(output.find("recommend") != std::string::npos);
    delete recQuery;
}

TEST_F(StaffQueryTest, UnhandledQueryType) {
    MiscQueryBuilder builder;
    builder.setType("INVALID_QUERY_TYPE");
    builder.setQuestion("Can you do my taxes?");
    Query* invalidQuery = builder.build();
    
    testing::internal::CaptureStdout();
    floorEmp->handleQuery(invalidQuery);
    std::string output = testing::internal::GetCapturedStdout();
    
    // Should propagate through entire chain and fail
    EXPECT_FALSE(floorEmp->staffCanHandle("INVALID_QUERY_TYPE"));
    EXPECT_FALSE(floorMgr->staffCanHandle("INVALID_QUERY_TYPE"));
    EXPECT_FALSE(salesEmp->staffCanHandle("INVALID_QUERY_TYPE"));
    EXPECT_FALSE(salesMgr->staffCanHandle("INVALID_QUERY_TYPE"));
    EXPECT_TRUE(output.find("Sorry we can not handle the query") != std::string::npos);
    delete invalidQuery;
}

// Test that MiscQueryBuilder properly ignores items
TEST_F(StaffQueryTest, MiscQueryBuilderIgnoresItem) {
    MiscQueryBuilder builder;
    builder.setType("STOCK");
    builder.setItem(testPlant);  // Should be ignored with warning
    Query* query = builder.build();
    
    EXPECT_EQ(query->getItem(), nullptr);
    EXPECT_EQ(query->getType(), "STOCK");
    
    delete query;
}

// Test multiple misc queries in sequence
TEST_F(StaffQueryTest, MultipleMiscQueries) {
    MiscQueryBuilder builder;
    std::vector<std::pair<std::string, std::string>> queries = {
        {"STOCK", "What is the current stock?"},
        {"DEALS", "Are there any deals?"},
        {"EVENT", "When is the next event?"}
    };
    
    for (const auto& q : queries) {
        builder.setType(q.first);
        builder.setQuestion(q.second);
        Query* query = builder.build();
        
        EXPECT_EQ(query->getType(), q.first);
        EXPECT_EQ(query->getQuestion(), q.second);
        EXPECT_EQ(query->getItem(), nullptr);
        
        delete query;
    }
}