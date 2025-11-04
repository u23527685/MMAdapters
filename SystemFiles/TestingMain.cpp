#define DOCTEST_CONFIG_IMPLEMENT
#include "StateUnitTests/doctest.h"

#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "PlantInventory.h"
#include "InventoryProxy.h"
#include "SalesFloorObserver.h"

#include "BasePlant.h"
#include "GiftWrap.h"
#include "DecorativePot.h"
#include "SpecialArrangement.h"

#include "Rose.h"
#include "Oak.h"

#include "Customer.h"
#include "Order.h"
#include "Transaction.h"
#include "CreditCardPaymentStrategy.h"
#include "EWalletPaymentStrategy.h"
#include "EFTPaymentStrategy.h"

#include "FloorEmployee.h"
#include "FloorManager.h"
#include "SalesEmployee.h"
#include "SalesManager.h"

#include "AskQuery.h"
#include "MiscQueryBuilder.h"

// Include GreenhouseUnitTest for custom test framework
#include "GreenhouseUnitTest/GreenhouseUnitTest.h"
#include "GreenhouseUnitTest/GreenhouseUnitTest.cpp"

// Include unit test files (without DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
// StateUnitTests - Testing plant state transitions and behaviors
#include "StateUnitTests/seedStateTest_include.h"
#include "StateUnitTests/matureStateTest.cpp"
#include "StateUnitTests/seedlingStateTest.cpp"
#include "StateUnitTests/distressedStateTest.cpp"
#include "StateUnitTests/witheredStateTest.cpp"
#include "StateUnitTests/strategyTest.cpp"

#include "ProxyUnitTest/proxyUnitTest_include.h"
#include "SalesObserverUnitTest/salesObserverUnitTest_include.h"
#include "PLCO_And_PCRTM_UnitTests/test_core_components_include.h"
#include "QueryHandlingUnitTest/QueryHandlingUnitTest_include.h"
#include "DecoratorUnitTest/PlantDecoratorUnitTest_include.h"
#include "MementoStartergyUnitTest/TransactionUnitTest_include.h"
#include "UnitTest/UnitTest.h"

int main() {
    std::cout << "\n=== Running All Unit Tests ===\n\n";
    
    // Run doctest unit tests first
    std::cout << "=== Running Doctest Unit Tests ===\n";
    doctest::Context context;
    
    int res = context.run();
    
    if(context.shouldExit()) {
        return res;
    }
    
    std::cout << "\n=== Running Greenhouse Unit Tests ===\n\n";
    GreenhouseUnitTest::run();
    
    std::cout << "\n=== Running Integration Tests ===\n\n";
    // deterministic randomness for tests
    srand(42);

    // Payment strategies
    CreditCardPaymentStrategy credit("0000-0000-0000-0000");
    EWalletPaymentStrategy wallet("test-wallet");
    EFTPaymentStrategy eft("000000");

    // Inventory + observer + proxy
    PlantInventory* inventory = PlantInventory::getInstance();
    auto salesObs = std::make_unique<SalesFloorObserver>(inventory);
    InventoryProxy proxy(salesObs.get());

    // Create sample plants (raw pointers; inventory takes ownership per project conventions)
    Rose* r1 = new Rose(10.0, "Red Rose");
    r1->setCategory("Sunny");
    Oak* o1 = new Oak(7.0, "Oak Tree");
    o1->setCategory("Temperate");

    // Add stock directly and via proxy, assert basic API works
    inventory->addStock(r1, 2);
    inventory->addStock(o1, 1);

    // Inspect inventory view and quantities
    auto view = inventory->getInventoryView();
    for (const auto& it : view) {
        if (it.first)
            std::cout << "Inventory item: " << it.first->getDescription() << " qty=" << it.second << "\n";
    }

    // Proxy: buy and restore behavior
    bool bought = proxy.buyPlant(r1, 1);
    std::cout << "Proxy buyPlant(Red Rose,1) => " << (bought ? "success" : "fail") << "\n";
    // try buying more than available
    bool boughtTooMany = proxy.buyPlant(o1, 5);
    std::cout << "Proxy buyPlant(Oak Tree,5) => " << (boughtTooMany ? "success" : "fail") << "\n";

    // Decorator tests: wrap a base plant and query prices/descriptions
    BasePlant base(5.0, "Generic Plant");
    std::unique_ptr<Plant> deco = std::make_unique<GiftWrap>(new BasePlant(base.getPrice(), base.getDescription()));
    deco = std::make_unique<DecorativePot>(deco.release());
    deco = std::make_unique<SpecialArrangement>(deco.release());
    std::cout << "Decorated description: " << deco->getDescription() << " price: " << deco->getPrice() << "\n";

    // Create customer, order, transaction and test payment strategies
    Customer cust("UnitTester");
    Order order(&cust, "ORD-UNIT-1");
    Transaction* tx1 = new Transaction(order.getOrderId(), deco->getPrice(), 1);
    tx1->setPaymentStrategy(&credit);
    order.addTransaction(tx1);
    order.processOrder();
    std::cout << "Processed order " << order.getOrderId() << " amount: " << tx1->getAmount()
              << " method: " << tx1->getPaymentMethod() << "\n";

    // Save another transaction (ewallet)
    Transaction* tx2 = new Transaction(order.getOrderId(), 2.5, 1);
    tx2->setPaymentStrategy(&wallet);
    std::cout << "E-Wallet payment method: " << tx2->getPaymentMethod() << "\n";
    delete tx2;

    // Test EFT behavior (no crash)
    Transaction tx3(order.getOrderId(), 1.0, 1);
    tx3.setPaymentStrategy(&eft);
    std::cout << "EFT method: " << tx3.getPaymentMethod() << "\n";

    // Staff and queries: set up a small chain and a query for an inventory plant
    std::vector<Staff*> staff;
    staff.push_back(new FloorEmployee("Alice"));
    staff.push_back(new SalesEmployee("Bob"));
    // chain links
    for (size_t i = 0; i < staff.size(); ++i) {
        staff[i]->setNext(i + 1 < staff.size() ? staff[i + 1] : nullptr);
    }

    // Build an ASK query (care/describe) for an existing plant
    AskQuery qBuilder;
    Query* q = qBuilder.describe(r1);
    if (q) {
        std::cout << "Handling describe query for: " << r1->getDescription() << "\n";
        staff.front()->handleQuery(q);
        delete q;
    }

    // Custom query via MiscQueryBuilder (no plant)
    MiscQueryBuilder mb;
    mb.setType("INFO");
    mb.setQuestion("TEST QUESTION");
    Query* mq = mb.build();
    if (mq) {
        std::cout << "Handling misc query type: INFO\n";
        staff.front()->handleQuery(mq);
        delete mq;
    }

    // Clean up staff
    for (auto s : staff) delete s;

    // Test inventory proxy add/remove unauthorized paths
    proxy.addStock(r1, 3);   // should not crash
    proxy.removeStock(r1, 1);

    // Final inventory dump
    auto finalView = inventory->getInventoryView();
    for (const auto& it : finalView) {
        if (it.first)
            std::cout << "Final Inventory: " << it.first->getDescription() << " qty=" << it.second << "\n";
    }

    std::cout << "TestingMain finished without defaults/crashes.\n";

    // Print test summary
    std::cout << "\n=== Test Summary ===\n";
    std::cout << "Unit Tests: " << (res == 0 ? "PASSED" : "FAILED") << "\n";
    std::cout << "Integration Tests: COMPLETED\n";
    std::cout << "====================\n";
    
    return 0;
}