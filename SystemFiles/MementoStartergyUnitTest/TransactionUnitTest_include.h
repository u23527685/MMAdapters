// Converted from gtest to doctest for inclusion in TestingMain.cpp

#include "../CreditCardPaymentStrategy.h"
#include "../Customer.h"
#include "../EFTPaymentStrategy.h"
#include "../EWalletPaymentStrategy.h"
#include "../Order.h"
#include "../PaymentStrategy.h"
#include "../Transaction.h"
#include "../TransactionHistory.h"
#include <string>

// Customer Tests
TEST_CASE("Memento: Customer Default Constructor")
{
    Customer customer;
    CHECK(customer.getName() == "Unknown");
}

TEST_CASE("Memento: Customer Parameterized Constructor")
{
    Customer customer("TestUser");
    CHECK(customer.getName() == "TestUser");
}

TEST_CASE("Memento: Customer Set Name")
{
    Customer customer("DefaultUser");
    CHECK(customer.getName() == "DefaultUser");

    customer.setName("Jerusha");
    CHECK(customer.getName() == "Jerusha");
}

TEST_CASE("Memento: Customer Empty Name Handling")
{
    Customer customer("");
    customer.setName("Jerusha");
    CHECK(customer.getName() == "Jerusha");
}

// Payment Strategy Tests
TEST_CASE("Memento: Credit Card Payment Strategy")
{
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    Transaction t1("ORD001", 200.0, 2);
    t1.setPaymentStrategy(&credit);

    // Verify payment processing works (no exception)
    CHECK_NOTHROW(t1.processPayment());
}

TEST_CASE("Memento: EFT Payment Strategy")
{
    EFTPaymentStrategy eft("ACC-987654321");
    Transaction t2("ORD002", 150.5, 1);
    t2.setPaymentStrategy(&eft);

    CHECK_NOTHROW(t2.processPayment());
}

TEST_CASE("Memento: EWallet Payment Strategy")
{
    EWalletPaymentStrategy wallet("WALLET-ABC123");
    Transaction t3("ORD003", 300.75, 3);
    t3.setPaymentStrategy(&wallet);

    CHECK_NOTHROW(t3.processPayment());
}

// Transaction Tests
TEST_CASE("Memento: Transaction Creation")
{
    Transaction t1("ORD001", 200.0, 2);

    // Verify transaction was created (test by using it)
    CHECK_NOTHROW(t1.getDetails());
}

TEST_CASE("Memento: Transaction Modification")
{
    Transaction t1("ORD001", 200.0, 2);

    // Modify transaction
    t1.setTransaction("ORD001_MOD", 500.0, 1);

    CHECK_NOTHROW(t1.getDetails());
}

// Memento Pattern Tests
TEST_CASE("Memento: Create Snapshot")
{
    Transaction t1("ORD001", 200.0, 2);

    TransactionSnapshot snap = t1.createSnapshot();

    // Snapshot should be created successfully
    CHECK_NOTHROW(t1.createSnapshot());
}

TEST_CASE("Memento: Restore Snapshot")
{
    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    // Create snapshot of original state
    TransactionSnapshot snap = t1.createSnapshot();

    // Modify transaction
    t1.setTransaction("ORD001_MOD", 500.0, 1);

    // Restore original snapshot
    t1.restoreSnapshot(snap);

    // Verify restoration worked (should not throw)
    CHECK_NOTHROW(t1.getDetails());
}

TEST_CASE("Memento: Transaction History Add Snapshot")
{
    TransactionHistory history;

    Transaction t1("ORD001", 200.0, 2);
    Transaction t2("ORD002", 150.5, 1);
    Transaction t3("ORD003", 300.75, 3);

    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    EFTPaymentStrategy eft("ACC-987654321");
    EWalletPaymentStrategy wallet("WALLET-ABC123");

    t1.setPaymentStrategy(&credit);
    t2.setPaymentStrategy(&eft);
    t3.setPaymentStrategy(&wallet);

    history.addSnapshot(t1.createSnapshot());
    history.addSnapshot(t2.createSnapshot());
    history.addSnapshot(t3.createSnapshot());

    // Verify snapshots were added (test by retrieving)
    CHECK_NOTHROW(history.getSnapshot(0));
    CHECK_NOTHROW(history.getSnapshot(1));
    CHECK_NOTHROW(history.getSnapshot(2));
}

TEST_CASE("Memento: Transaction History Retrieve Snapshot")
{
    TransactionHistory history;

    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    history.addSnapshot(t1.createSnapshot());

    // Modify transaction
    t1.setTransaction("ORD001_MOD", 500.0, 1);

    // Retrieve and restore snapshot
    TransactionSnapshot snap = history.getSnapshot(0);
    t1.restoreSnapshot(snap);

    CHECK_NOTHROW(t1.getDetails());
}

// Prototype Pattern Tests
TEST_CASE("Memento: Transaction Clone")
{
    Transaction t2("ORD002", 150.5, 1);
    EFTPaymentStrategy eft("ACC-987654321");
    t2.setPaymentStrategy(&eft);

    Transaction *tClone = t2.clone();

    REQUIRE(tClone != nullptr);
    CHECK_NOTHROW(tClone->getDetails());

    delete tClone;
}

TEST_CASE("Memento: Cloned Transaction Independence")
{
    Transaction t2("ORD002", 150.5, 1);
    EFTPaymentStrategy eft("ACC-987654321");
    t2.setPaymentStrategy(&eft);

    Transaction *tClone = t2.clone();

    // Modify original
    t2.setTransaction("ORD002_MOD", 999.0, 5);

    // Clone should still work independently
    CHECK_NOTHROW(tClone->getDetails());
    CHECK_NOTHROW(t2.getDetails());

    delete tClone;
}

// Order Tests
TEST_CASE("Memento: Order Creation")
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    CHECK_NOTHROW(order.displayOrderDetails());
}

TEST_CASE("Memento: Order Add Transaction")
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    order.addTransaction(&t1);

    CHECK_NOTHROW(order.displayOrderDetails());
}

TEST_CASE("Memento: Order Multiple Transactions")
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    Transaction t2("ORD002", 150.5, 1);
    Transaction t3("ORD003", 300.75, 3);

    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    EFTPaymentStrategy eft("ACC-987654321");
    EWalletPaymentStrategy wallet("WALLET-ABC123");

    t1.setPaymentStrategy(&credit);
    t2.setPaymentStrategy(&eft);
    t3.setPaymentStrategy(&wallet);

    order.addTransaction(&t1);
    order.addTransaction(&t2);
    order.addTransaction(&t3);

    CHECK_NOTHROW(order.displayOrderDetails());
}

TEST_CASE("Memento: Order Processing")
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    Transaction t2("ORD002", 150.5, 1);
    Transaction t3("ORD003", 300.75, 3);

    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    EFTPaymentStrategy eft("ACC-987654321");
    EWalletPaymentStrategy wallet("WALLET-ABC123");

    t1.setPaymentStrategy(&credit);
    t2.setPaymentStrategy(&eft);
    t3.setPaymentStrategy(&wallet);

    order.addTransaction(&t1);
    order.addTransaction(&t2);
    order.addTransaction(&t3);

    CHECK_NOTHROW(order.processOrder());
}

TEST_CASE("Memento: Process Payments")
{
    Transaction t1("ORD001", 200.0, 2);
    Transaction t2("ORD002", 150.5, 1);
    Transaction t3("ORD003", 300.75, 3);

    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    EFTPaymentStrategy eft("ACC-987654321");
    EWalletPaymentStrategy wallet("WALLET-ABC123");

    t1.setPaymentStrategy(&credit);
    t2.setPaymentStrategy(&eft);
    t3.setPaymentStrategy(&wallet);

    CHECK_NOTHROW(t1.processPayment());
    CHECK_NOTHROW(t2.processPayment());
    CHECK_NOTHROW(t3.processPayment());
}

// Customer Order Management Tests
TEST_CASE("Memento: Customer Place Order")
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    order.addTransaction(&t1);

    CHECK_NOTHROW(customer.placeOrder(order));
}

TEST_CASE("Memento: Customer View Orders")
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    order.addTransaction(&t1);
    customer.placeOrder(order);

    CHECK_NOTHROW(customer.viewOrders());
}

// Integration Test - Full Workflow
TEST_CASE("Memento: Full Workflow Integration")
{
    // Create customer
    Customer customer("TestUser");
    customer.setName("Jerusha");
    CHECK(customer.getName() == "Jerusha");

    // Create transaction history
    TransactionHistory history;

    // Create payment strategies
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    EFTPaymentStrategy eft("ACC-987654321");
    EWalletPaymentStrategy wallet("WALLET-ABC123");

    // Create transactions
    Transaction t1("ORD001", 200.0, 2);
    Transaction t2("ORD002", 150.5, 1);
    Transaction t3("ORD003", 300.75, 3);

    t1.setPaymentStrategy(&credit);
    t2.setPaymentStrategy(&eft);
    t3.setPaymentStrategy(&wallet);

    // Add snapshots
    history.addSnapshot(t1.createSnapshot());
    history.addSnapshot(t2.createSnapshot());
    history.addSnapshot(t3.createSnapshot());

    // Modify and restore
    t1.setTransaction("ORD001_MOD", 500.0, 1);
    TransactionSnapshot snap = history.getSnapshot(0);
    t1.restoreSnapshot(snap);

    // Clone transaction
    Transaction *tClone = t2.clone();
    REQUIRE(tClone != nullptr);

    // Process payments
    CHECK_NOTHROW(t1.processPayment());
    CHECK_NOTHROW(t2.processPayment());
    CHECK_NOTHROW(t3.processPayment());

    // Create and process order
    Order order(&customer, "ORDER-1001");
    order.addTransaction(&t1);
    order.addTransaction(&t2);
    order.addTransaction(&t3);

    CHECK_NOTHROW(order.processOrder());
    CHECK_NOTHROW(order.displayOrderDetails());

    // Customer places order and views
    CHECK_NOTHROW(customer.placeOrder(order));
    CHECK_NOTHROW(customer.viewOrders());

    // Cleanup
    delete tClone;
}

TEST_CASE("Memento: Temporary Customer")
{
    Customer tempCustomer;
    tempCustomer.setName("Jerusha");
    CHECK(tempCustomer.getName() == "Jerusha");
}
