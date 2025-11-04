#include "CreditCardPaymentStrategy.h"
#include "Customer.h"
#include "EFTPaymentStrategy.h"
#include "EWalletPaymentStrategy.h"
#include "Order.h"
#include "PaymentStrategy.h"
#include "Transaction.h"
#include "TransactionHistory.h"
#include <gtest/gtest.h>
#include <string>

class TransactionMementoTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        // Setup code if needed
    }

    void TearDown() override
    {
        // Cleanup code if needed
    }
};

// Customer Tests
TEST_F(TransactionMementoTest, CustomerDefaultConstructor)
{
    Customer customer;
    EXPECT_EQ(customer.getName(), "Unknown");
}

TEST_F(TransactionMementoTest, CustomerParameterizedConstructor)
{
    Customer customer("TestUser");
    EXPECT_EQ(customer.getName(), "TestUser");
}

TEST_F(TransactionMementoTest, CustomerSetName)
{
    Customer customer("DefaultUser");
    EXPECT_EQ(customer.getName(), "DefaultUser");

    customer.setName("Jerusha");
    EXPECT_EQ(customer.getName(), "Jerusha");
}

TEST_F(TransactionMementoTest, CustomerEmptyNameHandling)
{
    Customer customer("");
    customer.setName("Jerusha");
    EXPECT_EQ(customer.getName(), "Jerusha");
}

// Payment Strategy Tests
TEST_F(TransactionMementoTest, CreditCardPaymentStrategy)
{
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    Transaction t1("ORD001", 200.0, 2);
    t1.setPaymentStrategy(&credit);

    // Verify payment processing works (no exception)
    EXPECT_NO_THROW(t1.processPayment());
}

TEST_F(TransactionMementoTest, EFTPaymentStrategy)
{
    EFTPaymentStrategy eft("ACC-987654321");
    Transaction t2("ORD002", 150.5, 1);
    t2.setPaymentStrategy(&eft);

    EXPECT_NO_THROW(t2.processPayment());
}

TEST_F(TransactionMementoTest, EWalletPaymentStrategy)
{
    EWalletPaymentStrategy wallet("WALLET-ABC123");
    Transaction t3("ORD003", 300.75, 3);
    t3.setPaymentStrategy(&wallet);

    EXPECT_NO_THROW(t3.processPayment());
}

// Transaction Tests
TEST_F(TransactionMementoTest, TransactionCreation)
{
    Transaction t1("ORD001", 200.0, 2);

    // Verify transaction was created (test by using it)
    EXPECT_NO_THROW(t1.getDetails());
}

TEST_F(TransactionMementoTest, TransactionModification)
{
    Transaction t1("ORD001", 200.0, 2);

    // Modify transaction
    t1.setTransaction("ORD001_MOD", 500.0, 1);

    EXPECT_NO_THROW(t1.getDetails());
}

// Memento Pattern Tests
TEST_F(TransactionMementoTest, CreateSnapshot)
{
    Transaction t1("ORD001", 200.0, 2);

    TransactionSnapshot snap = t1.createSnapshot();

    // Snapshot should be created successfully
    EXPECT_NO_THROW(t1.createSnapshot());
}

TEST_F(TransactionMementoTest, RestoreSnapshot)
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
    EXPECT_NO_THROW(t1.getDetails());
}

TEST_F(TransactionMementoTest, TransactionHistoryAddSnapshot)
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
    EXPECT_NO_THROW(history.getSnapshot(0));
    EXPECT_NO_THROW(history.getSnapshot(1));
    EXPECT_NO_THROW(history.getSnapshot(2));
}

TEST_F(TransactionMementoTest, TransactionHistoryRetrieveSnapshot)
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

    EXPECT_NO_THROW(t1.getDetails());
}

// Prototype Pattern Tests
TEST_F(TransactionMementoTest, TransactionClone)
{
    Transaction t2("ORD002", 150.5, 1);
    EFTPaymentStrategy eft("ACC-987654321");
    t2.setPaymentStrategy(&eft);

    Transaction *tClone = t2.clone();

    ASSERT_NE(tClone, nullptr);
    EXPECT_NO_THROW(tClone->getDetails());

    delete tClone;
}

TEST_F(TransactionMementoTest, ClonedTransactionIndependence)
{
    Transaction t2("ORD002", 150.5, 1);
    EFTPaymentStrategy eft("ACC-987654321");
    t2.setPaymentStrategy(&eft);

    Transaction *tClone = t2.clone();

    // Modify original
    t2.setTransaction("ORD002_MOD", 999.0, 5);

    // Clone should still work independently
    EXPECT_NO_THROW(tClone->getDetails());
    EXPECT_NO_THROW(t2.getDetails());

    delete tClone;
}

// Order Tests
TEST_F(TransactionMementoTest, OrderCreation)
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    EXPECT_NO_THROW(order.displayOrderDetails());
}

TEST_F(TransactionMementoTest, OrderAddTransaction)
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    order.addTransaction(&t1);

    EXPECT_NO_THROW(order.displayOrderDetails());
}

TEST_F(TransactionMementoTest, OrderMultipleTransactions)
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

    EXPECT_NO_THROW(order.displayOrderDetails());
}

TEST_F(TransactionMementoTest, OrderProcessing)
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

    EXPECT_NO_THROW(order.processOrder());
}

TEST_F(TransactionMementoTest, ProcessPayments)
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

    EXPECT_NO_THROW(t1.processPayment());
    EXPECT_NO_THROW(t2.processPayment());
    EXPECT_NO_THROW(t3.processPayment());
}

// Customer Order Management Tests
TEST_F(TransactionMementoTest, CustomerPlaceOrder)
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    order.addTransaction(&t1);

    EXPECT_NO_THROW(customer.placeOrder(order));
}

TEST_F(TransactionMementoTest, CustomerViewOrders)
{
    Customer customer("TestUser");
    Order order(&customer, "ORDER-1001");

    Transaction t1("ORD001", 200.0, 2);
    CreditCardPaymentStrategy credit("1111-2222-3333-4444");
    t1.setPaymentStrategy(&credit);

    order.addTransaction(&t1);
    customer.placeOrder(order);

    EXPECT_NO_THROW(customer.viewOrders());
}

// Integration Test - Full Workflow
TEST_F(TransactionMementoTest, FullWorkflowIntegration)
{
    // Create customer
    Customer customer("TestUser");
    customer.setName("Jerusha");
    EXPECT_EQ(customer.getName(), "Jerusha");

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
    ASSERT_NE(tClone, nullptr);

    // Process payments
    EXPECT_NO_THROW(t1.processPayment());
    EXPECT_NO_THROW(t2.processPayment());
    EXPECT_NO_THROW(t3.processPayment());

    // Create and process order
    Order order(&customer, "ORDER-1001");
    order.addTransaction(&t1);
    order.addTransaction(&t2);
    order.addTransaction(&t3);

    EXPECT_NO_THROW(order.processOrder());
    EXPECT_NO_THROW(order.displayOrderDetails());

    // Customer places order and views
    EXPECT_NO_THROW(customer.placeOrder(order));
    EXPECT_NO_THROW(customer.viewOrders());

    // Cleanup
    delete tClone;
}

TEST_F(TransactionMementoTest, TemporaryCustomer)
{
    Customer tempCustomer;
    tempCustomer.setName("Jerusha");
    EXPECT_EQ(tempCustomer.getName(), "Jerusha");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}