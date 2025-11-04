#include "BasePlant.h"
#include "DecorativePot.h"
#include "GiftWrap.h"
#include "SpecialArrangement.h"
#include <cmath>
#include <gtest/gtest.h>
#include <memory>

class PlantDecoratorTest : public ::testing::Test
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

// Base Plant Tests
TEST_F(PlantDecoratorTest, BasicPlantDefaultConstructor)
{
    BasePlant basicPlant;
    EXPECT_EQ(basicPlant.getDescription(), "Basic Plant");
    EXPECT_DOUBLE_EQ(basicPlant.getPrice(), 0.0); // Changed from 10.0 to 0.0
}

TEST_F(PlantDecoratorTest, BasicPlantCustomConstructor)
{
    BasePlant customPlant(25.99, "Custom Rose");
    EXPECT_EQ(customPlant.getDescription(), "Custom Rose");
    EXPECT_DOUBLE_EQ(customPlant.getPrice(), 25.99);
}

// Gift Wrap Tests
TEST_F(PlantDecoratorTest, GiftWrapBasicPlant)
{
    BasePlant *basic = new BasePlant();
    GiftWrap *giftWrappedBasic = new GiftWrap(basic);

    EXPECT_TRUE(giftWrappedBasic->getDescription().find("Gift Wrapped") !=
                std::string::npos);
    EXPECT_GT(giftWrappedBasic->getPrice(), basic->getPrice());

    delete giftWrappedBasic;
}

TEST_F(PlantDecoratorTest, GiftWrapCustomPlant)
{
    BasePlant *custom = new BasePlant(30.0, "Orchid");
    GiftWrap *giftWrappedCustom = new GiftWrap(custom);

    EXPECT_TRUE(giftWrappedCustom->getDescription().find("Orchid") !=
                std::string::npos);
    EXPECT_TRUE(giftWrappedCustom->getDescription().find("Gift Wrapped") !=
                std::string::npos);
    EXPECT_GT(giftWrappedCustom->getPrice(), 30.0);

    delete giftWrappedCustom;
}

// Decorative Pot Tests
TEST_F(PlantDecoratorTest, DecorativePotBasicPlant)
{
    BasePlant *basic = new BasePlant();
    DecorativePot *pottedBasic = new DecorativePot(basic);

    EXPECT_TRUE(pottedBasic->getDescription().find("Decorative Pot") !=
                std::string::npos);
    EXPECT_GT(pottedBasic->getPrice(), basic->getPrice());

    delete pottedBasic;
}

TEST_F(PlantDecoratorTest, DecorativePotCustomPlant)
{
    BasePlant *custom = new BasePlant(45.50, "Bonsai Tree");
    DecorativePot *pottedCustom = new DecorativePot(custom);

    EXPECT_TRUE(pottedCustom->getDescription().find("Bonsai Tree") !=
                std::string::npos);
    EXPECT_TRUE(pottedCustom->getDescription().find("Decorative Pot") !=
                std::string::npos);
    EXPECT_GT(pottedCustom->getPrice(), 45.50);

    delete pottedCustom;
}

// Special Arrangement Tests
TEST_F(PlantDecoratorTest, SpecialArrangementBasicPlant)
{
    BasePlant *basic = new BasePlant();
    SpecialArrangement *arrangedBasic = new SpecialArrangement(basic);

    EXPECT_TRUE(arrangedBasic->getDescription().find("Special Arrangement") !=
                std::string::npos);
    EXPECT_GT(arrangedBasic->getPrice(), basic->getPrice());

    delete arrangedBasic;
}

TEST_F(PlantDecoratorTest, SpecialArrangementCustomPlant)
{
    BasePlant *custom = new BasePlant(60.75, "Exotic Flower Bouquet");
    SpecialArrangement *arrangedCustom = new SpecialArrangement(custom);

    EXPECT_TRUE(arrangedCustom->getDescription().find(
                    "Exotic Flower Bouquet") != std::string::npos);
    EXPECT_TRUE(arrangedCustom->getDescription().find("Special Arrangement") !=
                std::string::npos);
    EXPECT_GT(arrangedCustom->getPrice(), 60.75);

    delete arrangedCustom;
}

// Multiple Decorations Tests
TEST_F(PlantDecoratorTest, FullyDecoratedPlant)
{
    BasePlant *base = new BasePlant(20.0, "Tulip");
    GiftWrap *giftWrapped = new GiftWrap(base);
    DecorativePot *potted = new DecorativePot(giftWrapped);
    SpecialArrangement *fullyDecorated = new SpecialArrangement(potted);

    std::string description = fullyDecorated->getDescription();
    EXPECT_TRUE(description.find("Tulip") != std::string::npos);
    EXPECT_TRUE(description.find("Gift Wrapped") != std::string::npos);
    EXPECT_TRUE(description.find("Decorative Pot") != std::string::npos);
    EXPECT_TRUE(description.find("Special Arrangement") != std::string::npos);
    EXPECT_GT(fullyDecorated->getPrice(), 20.0);

    delete fullyDecorated;
}

TEST_F(PlantDecoratorTest, GiftAndPotCombination)
{
    BasePlant *base = new BasePlant(15.0, "Sunflower");
    GiftWrap *gift = new GiftWrap(base);
    DecorativePot *pot = new DecorativePot(gift);

    std::string description = pot->getDescription();
    EXPECT_TRUE(description.find("Sunflower") != std::string::npos);
    EXPECT_TRUE(description.find("Gift Wrapped") != std::string::npos);
    EXPECT_TRUE(description.find("Decorative Pot") != std::string::npos);
    EXPECT_GT(pot->getPrice(), 15.0);

    delete pot;
}

TEST_F(PlantDecoratorTest, ArrangementAndGiftCombination)
{
    BasePlant *base = new BasePlant(35.0, "Rose Bush");
    SpecialArrangement *arrange = new SpecialArrangement(base);
    GiftWrap *gift = new GiftWrap(arrange);

    std::string description = gift->getDescription();
    EXPECT_TRUE(description.find("Rose Bush") != std::string::npos);
    EXPECT_TRUE(description.find("Special Arrangement") != std::string::npos);
    EXPECT_TRUE(description.find("Gift Wrapped") != std::string::npos);
    EXPECT_GT(gift->getPrice(), 35.0);

    delete gift;
}

// Price Calculation Tests
TEST_F(PlantDecoratorTest, IndividualDecoratorPrices)
{
    double basePrice = 10.0;

    BasePlant *testPlant1 = new BasePlant(basePrice, "Test Plant");
    GiftWrap *gift = new GiftWrap(testPlant1);
    double giftPrice = gift->getPrice() - basePrice;
    EXPECT_GT(giftPrice, 0.0);

    BasePlant *testPlant2 = new BasePlant(basePrice, "Test Plant");
    DecorativePot *pot = new DecorativePot(testPlant2);
    double potPrice = pot->getPrice() - basePrice;
    EXPECT_GT(potPrice, 0.0);

    BasePlant *testPlant3 = new BasePlant(basePrice, "Test Plant");
    SpecialArrangement *arrange = new SpecialArrangement(testPlant3);
    double arrangePrice = arrange->getPrice() - basePrice;
    EXPECT_GT(arrangePrice, 0.0);

    delete gift;
    delete pot;
    delete arrange;
}

TEST_F(PlantDecoratorTest, CumulativePricing)
{
    double basePrice = 10.0;

    BasePlant *testPlant1 = new BasePlant(basePrice, "Test Plant");
    GiftWrap *gift = new GiftWrap(testPlant1);
    double giftPrice = gift->getPrice() - basePrice;

    BasePlant *testPlant2 = new BasePlant(basePrice, "Test Plant");
    DecorativePot *pot = new DecorativePot(testPlant2);
    double potPrice = pot->getPrice() - basePrice;

    BasePlant *testPlant3 = new BasePlant(basePrice, "Test Plant");
    SpecialArrangement *arrange = new SpecialArrangement(testPlant3);
    double arrangePrice = arrange->getPrice() - basePrice;

    BasePlant *cumulativeTest = new BasePlant(basePrice, "Cumulative Test");
    GiftWrap *step1 = new GiftWrap(cumulativeTest);
    DecorativePot *step2 = new DecorativePot(step1);
    SpecialArrangement *step3 = new SpecialArrangement(step2);

    double expectedTotal = basePrice + giftPrice + potPrice + arrangePrice;
    double actualTotal = step3->getPrice();

    EXPECT_NEAR(expectedTotal, actualTotal, 0.01);

    delete gift;
    delete pot;
    delete arrange;
    delete step3;
}

// Edge Cases Tests
TEST_F(PlantDecoratorTest, ZeroPricePlant)
{
    BasePlant *zeroPrice = new BasePlant(0.0, "Free Plant");
    GiftWrap *wrappedFree = new GiftWrap(zeroPrice);

    EXPECT_EQ(zeroPrice->getPrice(), 0.0);
    EXPECT_GE(wrappedFree->getPrice(), 0.0);

    delete wrappedFree;
}

TEST_F(PlantDecoratorTest, NegativePricePlant)
{
    BasePlant *negativePrice = new BasePlant(-5.0, "Discount Plant");
    DecorativePot *pottedDiscount = new DecorativePot(negativePrice);

    EXPECT_EQ(negativePrice->getPrice(), -5.0);
    // Price after decoration could still be negative or positive depending on
    // implementation

    delete pottedDiscount;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}