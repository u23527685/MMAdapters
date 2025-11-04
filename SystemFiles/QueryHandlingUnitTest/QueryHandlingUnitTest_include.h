// Converted from gtest to doctest for inclusion in TestingMain.cpp

#include "../AskQuery.h"
#include "../FloorEmployee.h"
#include "../FloorManager.h"
#include "../ItemQueryBuilder.h"
#include "../MiscQueryBuilder.h"
#include "../Plant.h"
#include "../Rose.h"
#include "../SalesEmployee.h"
#include "../SalesManager.h"
#include <functional>
#include <iostream>
#include <sstream>

// Helper function to capture stdout
std::string captureOutput(std::function<void()> func)
{
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

TEST_CASE("QueryHandling: Plant Properties")
{
    Plant *testPlant = new Plant(29.99, "Generic Test Plant");

    CHECK(testPlant->getPrice() == 29.99);
    CHECK(testPlant->getDescription() == "Generic Test Plant");
    CHECK(testPlant->getCategory() == "generic");

    delete testPlant;
}

TEST_CASE("QueryHandling: Rose Properties")
{
    Rose *testRose = new Rose(49.99, "Red Rose");

    CHECK(testRose->getPrice() == 49.99);
    CHECK(testRose->getDescription() == "Red Rose");

    delete testRose;
}

TEST_CASE("QueryHandling: Plant Care Parameters")
{
    Plant *testPlant = new Plant(29.99, "Generic Test Plant");

    CHECK(testPlant->getMaxWater() == 100);
    CHECK(testPlant->getMaxSunlight() == 100);
    CHECK(testPlant->getMaxNutrients() == 100);
    CHECK(testPlant->getMinWater() == 0);
    CHECK(testPlant->getMinSunlight() == 0);
    CHECK(testPlant->getMinNutrients() == 0);

    delete testPlant;
}

TEST_CASE("QueryHandling: Plant State Changes")
{
    Plant *testPlant = new Plant(29.99, "Generic Test Plant");

    testPlant->setCurrentWater(80);
    testPlant->setCurrentSunlight(75);
    testPlant->setCurrentNutrients(60);
    CHECK(testPlant->getCurrentWater() == 80);
    CHECK(testPlant->getCurrentSunlight() == 75);
    CHECK(testPlant->getCurrentNutrients() == 60);

    testPlant->setCurrentWater(150);
    testPlant->setCurrentSunlight(175);
    testPlant->setCurrentNutrients(125);
    CHECK(testPlant->getCurrentWater() == testPlant->getMaxWater());
    CHECK(testPlant->getCurrentSunlight() == testPlant->getMaxSunlight());
    CHECK(testPlant->getCurrentNutrients() == testPlant->getMaxNutrients());

    delete testPlant;
}

TEST_CASE("QueryHandling: FloorEmployee Handles Info")
{
    FloorEmployee *floorEmp = new FloorEmployee("John");
    Plant *testPlant = new Plant(29.99, "Generic Test Plant");
    AskQuery *queryBuilder = new AskQuery();

    Query *infoQuery = queryBuilder->describe(testPlant);
    CHECK(floorEmp->staffCanHandle("INFO") == true);

    delete infoQuery;
    delete queryBuilder;
    delete testPlant;
    delete floorEmp;
}

TEST_CASE("QueryHandling: FloorManager Handles Stock")
{
    FloorManager *floorMgr = new FloorManager("Mike");
    Plant *testPlant = new Plant(29.99, "Generic Test Plant");

    ItemQueryBuilder builder;
    builder.setType("STOCK");
    builder.setItem(testPlant);
    Query *stockQuery = builder.build();

    CHECK(floorMgr->staffCanHandle("STOCK") == true);
    CHECK(stockQuery->getItem() == testPlant);

    delete stockQuery;
    delete testPlant;
    delete floorMgr;
}

TEST_CASE("QueryHandling: Query Chain of Responsibility")
{
    FloorEmployee *floorEmp = new FloorEmployee("John");
    FloorManager *floorMgr = new FloorManager("Mike");
    SalesEmployee *salesEmp = new SalesEmployee("Sarah");
    SalesManager *salesMgr = new SalesManager("Lisa");

    floorEmp->setNext(floorMgr);
    floorMgr->setNext(salesEmp);
    salesEmp->setNext(salesMgr);

    Plant *testPlant = new Plant(29.99, "Generic Test Plant");
    ItemQueryBuilder builder;
    builder.setType("STOCK");
    builder.setItem(testPlant);
    Query *salesQuery = builder.build();

    std::string output =
        captureOutput([&]() { floorEmp->handleQuery(salesQuery); });

    CHECK(output.find("passing the task") != std::string::npos);

    delete salesQuery;
    delete testPlant;
    delete floorEmp;
    delete floorMgr;
    delete salesEmp;
    delete salesMgr;
}

TEST_CASE("QueryHandling: Query Construction")
{
    Plant *testPlant = new Plant(29.99, "Generic Test Plant");
    AskQuery *queryBuilder = new AskQuery();

    Query *infoQuery = queryBuilder->describe(testPlant);
    CHECK(infoQuery->getType() == "INFO");
    CHECK(infoQuery->getItem() == testPlant);

    delete infoQuery;
    delete queryBuilder;
    delete testPlant;
}

TEST_CASE("QueryHandling: Staff Name and Next")
{
    FloorEmployee *floorEmp = new FloorEmployee("John");
    FloorManager *floorMgr = new FloorManager("Mike");
    floorEmp->setNext(floorMgr);

    CHECK(floorEmp->getName() == "John");
    CHECK(floorEmp->getNext() == floorMgr);

    delete floorEmp;
    delete floorMgr;
}

TEST_CASE("QueryHandling: SalesEmployee Handles Deals")
{
    SalesEmployee *salesEmp = new SalesEmployee("Sarah");

    MiscQueryBuilder builder;
    builder.setType("DEALS");
    builder.setQuestion("What deals are there currently");
    Query *dealsQuery = builder.build();

    std::string output =
        captureOutput([&]() { salesEmp->handleQuery(dealsQuery); });

    CHECK(salesEmp->staffCanHandle("DEALS") == true);
    CHECK(output.find("upcoming deals and promotions") != std::string::npos);

    delete dealsQuery;
    delete salesEmp;
}

TEST_CASE("QueryHandling: SalesManager Handles Events")
{
    SalesManager *salesMgr = new SalesManager("Lisa");

    MiscQueryBuilder builder;
    builder.setType("EVENT");
    Query *eventQuery = builder.build();

    std::string output =
        captureOutput([&]() { salesMgr->handleQuery(eventQuery); });

    CHECK(salesMgr->staffCanHandle("EVENT") == true);
    CHECK(output.find("event plans") != std::string::npos);

    delete eventQuery;
    delete salesMgr;
}

TEST_CASE("QueryHandling: FloorEmployee Handles Recommendations")
{
    FloorEmployee *floorEmp = new FloorEmployee("John");

    MiscQueryBuilder builder;
    builder.setType("RECOMMENDATIONS");
    builder.setQuestion("What plants do you recommend");
    Query *recQuery = builder.build();

    std::string output =
        captureOutput([&]() { floorEmp->handleQuery(recQuery); });

    CHECK(floorEmp->staffCanHandle("RECOMMENDATIONS") == true);
    CHECK(output.find("recommend") != std::string::npos);

    delete recQuery;
    delete floorEmp;
}

TEST_CASE("QueryHandling: Unhandled Query Type")
{
    FloorEmployee *floorEmp = new FloorEmployee("John");
    FloorManager *floorMgr = new FloorManager("Mike");
    SalesEmployee *salesEmp = new SalesEmployee("Sarah");
    SalesManager *salesMgr = new SalesManager("Lisa");

    floorEmp->setNext(floorMgr);
    floorMgr->setNext(salesEmp);
    salesEmp->setNext(salesMgr);

    MiscQueryBuilder builder;
    builder.setType("INVALID_QUERY_TYPE");
    builder.setQuestion("Can you do my taxes?");
    Query *invalidQuery = builder.build();

    std::string output =
        captureOutput([&]() { floorEmp->handleQuery(invalidQuery); });

    CHECK(floorEmp->staffCanHandle("INVALID_QUERY_TYPE") == false);
    CHECK(floorMgr->staffCanHandle("INVALID_QUERY_TYPE") == false);
    CHECK(salesEmp->staffCanHandle("INVALID_QUERY_TYPE") == false);
    CHECK(salesMgr->staffCanHandle("INVALID_QUERY_TYPE") == false);
    CHECK(output.find("Sorry we can not handle the query") !=
          std::string::npos);

    delete invalidQuery;
    delete floorEmp;
    delete floorMgr;
    delete salesEmp;
    delete salesMgr;
}

TEST_CASE("QueryHandling: MiscQueryBuilder Ignores Item")
{
    Plant *testPlant = new Plant(29.99, "Generic Test Plant");

    MiscQueryBuilder builder;
    builder.setType("DEALS");
    builder.setItem(testPlant);
    Query *query = builder.build();

    CHECK(query->getItem() == nullptr);
    CHECK(query->getType() == "DEALS");

    delete query;
    delete testPlant;
}

TEST_CASE("QueryHandling: Multiple Misc Queries")
{
    MiscQueryBuilder builder;
    std::vector<std::pair<std::string, std::string>> queries = {
        {"DEALS", "Are there any deals?"},
        {"EVENT", "When is the next event?"},
        {"RECOMMENDATIONS", "What do you recommend?"}};

    for (const auto &q : queries)
    {
        builder.setType(q.first);
        builder.setQuestion(q.second);
        Query *query = builder.build();

        CHECK(query->getType() == q.first);
        CHECK(query->getQuestion() == q.second);
        CHECK(query->getItem() == nullptr);

        delete query;
    }
}
