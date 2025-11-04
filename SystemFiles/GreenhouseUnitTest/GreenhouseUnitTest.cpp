#include "GreenhouseUnitTest.h"

void GreenhouseUnitTest::run()
{
    std::cout << "======================================\n";
    std::cout << "Starting Unit Tests\n";
    std::cout << "======================================\n\n";

    testPlant();
    testPlantInventory();
    testAddStock();
    testRemoveStock();
    testPlantStock();
    testPlantFactory();
    testTreeFactory();
    testFlowerFactory();
    testOak();
    testRose();

    std::cout << "\n======================================\n";
    std::cout << "All tests completed\n";
    std::cout << "======================================\n";
}

void GreenhouseUnitTest::testPlant()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing Plant class\n";
    std::cout << "--------------------------------------------\n";

    Rose *plant = new Rose(15.50, "red rose");

    std::cout << "Test: Plant creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (plant != nullptr ? "not null" : "null")
              << "\n\n";

    std::cout << "Test: Get price\n";
    std::cout << "Expected: 15.5\n";
    std::cout << "Actual: " << plant->getPrice() << "\n\n";

    std::cout << "Test: Get description\n";
    std::cout << "Expected: red rose\n";
    std::cout << "Actual: " << plant->getDescription() << "\n\n";

    plant->setColor("red");
    std::cout << "Test: Set and get color\n";
    std::cout << "Expected: red\n";
    std::cout << "Actual: " << plant->getColor() << "\n\n";

    delete plant;
}

void GreenhouseUnitTest::testPlantInventory()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing PlantInventory class\n";
    std::cout << "--------------------------------------------\n";

    PlantInventory *inv = PlantInventory::getInstance();

    std::cout << "Test: Singleton instance\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (inv != nullptr ? "not null" : "null") << "\n\n";

    PlantInventory *inv2 = PlantInventory::getInstance();
    std::cout << "Test: Same instance\n";
    std::cout << "Expected: same pointer\n";
    std::cout << "Actual: "
              << (inv == inv2 ? "same pointer" : "different pointer") << "\n\n";

    Rose *testPlant = new Rose(20.0, "test rose");
    inv->addStock(testPlant, 5);

    std::cout << "Test: Get quantity after adding\n";
    std::cout << "Expected: 5\n";
    std::cout << "Actual: " << inv->getQuantity(testPlant) << "\n\n";

    // Clean up properly - remove from inventory before deleting
    inv->removeStock(testPlant, 5);
    // Don't delete the plant - inventory manages it
}

void GreenhouseUnitTest::testAddStock()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing AddStock class\n";
    std::cout << "--------------------------------------------\n";

    PlantInventory *inv = PlantInventory::getInstance();
    Rose *plant = new Rose(10.0, "stock rose");

    AddStock *cmd = new AddStock(plant, 10, inv);

    std::cout << "Test: AddStock command creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (cmd != nullptr ? "not null" : "null") << "\n\n";

    bool result = cmd->execute();
    std::cout << "Test: Execute add command\n";
    std::cout << "Expected: true\n";
    std::cout << "Actual: " << (result ? "true" : "false") << "\n\n";

    std::cout << "Test: Quantity after add\n";
    std::cout << "Expected: 10\n";
    std::cout << "Actual: " << inv->getQuantity(plant) << "\n\n";

    delete cmd;
    // Don't delete plant - inventory manages it
    inv->removeStock(plant, 10);
}

void GreenhouseUnitTest::testRemoveStock()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing RemoveStock class\n";
    std::cout << "--------------------------------------------\n";

    PlantInventory *inv = PlantInventory::getInstance();
    Oak *plant = new Oak(50.0, "test oak");

    inv->addStock(plant, 15);

    RemoveStock *cmd = new RemoveStock(plant, 5, inv);

    std::cout << "Test: RemoveStock command creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (cmd != nullptr ? "not null" : "null") << "\n\n";

    bool result = cmd->execute();
    std::cout << "Test: Execute remove command\n";
    std::cout << "Expected: true\n";
    std::cout << "Actual: " << (result ? "true" : "false") << "\n\n";

    std::cout << "Test: Quantity after remove\n";
    std::cout << "Expected: 10\n";
    std::cout << "Actual: " << inv->getQuantity(plant) << "\n\n";

    delete cmd;
    // Don't delete plant - inventory manages it
    inv->removeStock(plant, 10);
}

void GreenhouseUnitTest::testPlantStock()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing PlantStock class\n";
    std::cout << "--------------------------------------------\n";

    PlantInventory *inv = PlantInventory::getInstance();
    PlantStock *stock = new PlantStock(inv);

    std::cout << "Test: PlantStock creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (stock != nullptr ? "not null" : "null")
              << "\n\n";

    Rose *plant = new Rose(12.0, "stock test");

    bool addResult = stock->addStock(plant, 8);
    std::cout << "Test: Add via PlantStock\n";
    std::cout << "Expected: true\n";
    std::cout << "Actual: " << (addResult ? "true" : "false") << "\n\n";

    std::cout << "Test: Quantity after add via stock\n";
    std::cout << "Expected: 8\n";
    std::cout << "Actual: " << inv->getQuantity(plant) << "\n\n";

    bool removeResult = stock->removeStock(plant, 3);
    std::cout << "Test: Remove via PlantStock\n";
    std::cout << "Expected: true\n";
    std::cout << "Actual: " << (removeResult ? "true" : "false") << "\n\n";

    std::cout << "Test: Quantity after remove via stock\n";
    std::cout << "Expected: 5\n";
    std::cout << "Actual: " << inv->getQuantity(plant) << "\n\n";

    // Don't delete plant - inventory manages it
    stock->removeStock(plant, 5);
    delete stock;
}

void GreenhouseUnitTest::testPlantFactory()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing PlantFactory class\n";
    std::cout << "--------------------------------------------\n";

    std::cout << "Test: PlantFactory is abstract\n";
    std::cout << "Expected: cannot instantiate directly\n";
    std::cout << "Actual: tested via concrete implementations\n\n";
}

void GreenhouseUnitTest::testTreeFactory()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing TreeFactory class\n";
    std::cout << "--------------------------------------------\n";

    TreeFactory *factory = new TreeFactory();

    std::cout << "Test: TreeFactory creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (factory != nullptr ? "not null" : "null")
              << "\n\n";

    Plant *oak = factory->createPlant("Oak", 75.0);

    std::cout << "Test: Create Oak via factory\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (oak != nullptr ? "not null" : "null") << "\n\n";

    std::cout << "Test: Oak price from factory\n";
    std::cout << "Expected: 75\n";
    std::cout << "Actual: " << oak->getPrice() << "\n\n";

    delete oak;
    delete factory;
}

void GreenhouseUnitTest::testFlowerFactory()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing FlowerFactory class\n";
    std::cout << "--------------------------------------------\n";

    FlowerFactory *factory = new FlowerFactory();

    std::cout << "Test: FlowerFactory creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (factory != nullptr ? "not null" : "null")
              << "\n\n";

    Plant *rose = factory->createPlant("Rose", 25.0);

    std::cout << "Test: Create Rose via factory\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (rose != nullptr ? "not null" : "null")
              << "\n\n";

    std::cout << "Test: Rose price from factory\n";
    std::cout << "Expected: 25\n";
    std::cout << "Actual: " << rose->getPrice() << "\n\n";

    delete rose;
    delete factory;
}

void GreenhouseUnitTest::testOak()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing Oak class\n";
    std::cout << "--------------------------------------------\n";

    Oak *oak = new Oak(100.0, "big oak tree");

    std::cout << "Test: Oak creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (oak != nullptr ? "not null" : "null") << "\n\n";

    std::cout << "Test: Oak price\n";
    std::cout << "Expected: 100\n";
    std::cout << "Actual: " << oak->getPrice() << "\n\n";

    std::cout << "Test: Oak description\n";
    std::cout << "Expected: big oak tree\n";
    std::cout << "Actual: " << oak->getDescription() << "\n\n";

    delete oak;
}

void GreenhouseUnitTest::testRose()
{
    std::cout << "--------------------------------------------\n";
    std::cout << "Testing Rose class\n";
    std::cout << "--------------------------------------------\n";

    Rose *rose = new Rose(18.50, "pink rose");

    std::cout << "Test: Rose creation\n";
    std::cout << "Expected: not null\n";
    std::cout << "Actual: " << (rose != nullptr ? "not null" : "null")
              << "\n\n";

    std::cout << "Test: Rose price\n";
    std::cout << "Expected: 18.5\n";
    std::cout << "Actual: " << rose->getPrice() << "\n\n";

    std::cout << "Test: Rose description\n";
    std::cout << "Expected: pink rose\n";
    std::cout << "Actual: " << rose->getDescription() << "\n\n";

    delete rose;
}
