// Converted from gtest to doctest for inclusion in TestingMain.cpp

#include "../BasePlant.h"
#include "../DecorativePot.h"
#include "../GiftWrap.h"
#include "../SpecialArrangement.h"
#include <cmath>
#include <memory>

TEST_CASE("Decorator: Basic Plant Default Constructor")
{
    BasePlant basicPlant;
    CHECK(basicPlant.getDescription() == "Basic Plant");
    CHECK(basicPlant.getPrice() == doctest::Approx(0.0));
}

TEST_CASE("Decorator: Basic Plant Custom Constructor")
{
    BasePlant customPlant(25.99, "Custom Rose");
    CHECK(customPlant.getDescription() == "Custom Rose");
    CHECK(customPlant.getPrice() == doctest::Approx(25.99));
}

TEST_CASE("Decorator: Gift Wrap Basic Plant")
{
    BasePlant *basic = new BasePlant();
    GiftWrap *giftWrappedBasic = new GiftWrap(basic);

    CHECK(giftWrappedBasic->getDescription().find("Gift Wrapped") !=
          std::string::npos);
    CHECK(giftWrappedBasic->getPrice() > basic->getPrice());

    delete giftWrappedBasic;
}

TEST_CASE("Decorator: Gift Wrap Custom Plant")
{
    BasePlant *custom = new BasePlant(30.0, "Orchid");
    GiftWrap *giftWrappedCustom = new GiftWrap(custom);

    CHECK(giftWrappedCustom->getDescription().find("Orchid") !=
          std::string::npos);
    CHECK(giftWrappedCustom->getDescription().find("Gift Wrapped") !=
          std::string::npos);
    CHECK(giftWrappedCustom->getPrice() > 30.0);

    delete giftWrappedCustom;
}

TEST_CASE("Decorator: Decorative Pot Basic Plant")
{
    BasePlant *basic = new BasePlant();
    DecorativePot *pottedBasic = new DecorativePot(basic);

    CHECK(pottedBasic->getDescription().find("Decorative Pot") !=
          std::string::npos);
    CHECK(pottedBasic->getPrice() > basic->getPrice());

    delete pottedBasic;
}

TEST_CASE("Decorator: Decorative Pot Custom Plant")
{
    BasePlant *custom = new BasePlant(45.50, "Bonsai Tree");
    DecorativePot *pottedCustom = new DecorativePot(custom);

    CHECK(pottedCustom->getDescription().find("Bonsai Tree") !=
          std::string::npos);
    CHECK(pottedCustom->getDescription().find("Decorative Pot") !=
          std::string::npos);
    CHECK(pottedCustom->getPrice() > 45.50);

    delete pottedCustom;
}

TEST_CASE("Decorator: Special Arrangement Basic Plant")
{
    BasePlant *basic = new BasePlant();
    SpecialArrangement *arrangedBasic = new SpecialArrangement(basic);

    CHECK(arrangedBasic->getDescription().find("Special Arrangement") !=
          std::string::npos);
    CHECK(arrangedBasic->getPrice() > basic->getPrice());

    delete arrangedBasic;
}

TEST_CASE("Decorator: Special Arrangement Custom Plant")
{
    BasePlant *custom = new BasePlant(60.75, "Exotic Flower Bouquet");
    SpecialArrangement *arrangedCustom = new SpecialArrangement(custom);

    CHECK(arrangedCustom->getDescription().find("Exotic Flower Bouquet") !=
          std::string::npos);
    CHECK(arrangedCustom->getDescription().find("Special Arrangement") !=
          std::string::npos);
    CHECK(arrangedCustom->getPrice() > 60.75);

    delete arrangedCustom;
}

TEST_CASE("Decorator: Fully Decorated Plant")
{
    BasePlant *base = new BasePlant(20.0, "Tulip");
    GiftWrap *giftWrapped = new GiftWrap(base);
    DecorativePot *potted = new DecorativePot(giftWrapped);
    SpecialArrangement *fullyDecorated = new SpecialArrangement(potted);

    std::string description = fullyDecorated->getDescription();
    CHECK(description.find("Tulip") != std::string::npos);
    CHECK(description.find("Gift Wrapped") != std::string::npos);
    CHECK(description.find("Decorative Pot") != std::string::npos);
    CHECK(description.find("Special Arrangement") != std::string::npos);
    CHECK(fullyDecorated->getPrice() > 20.0);

    delete fullyDecorated;
}

TEST_CASE("Decorator: Gift and Pot Combination")
{
    BasePlant *base = new BasePlant(15.0, "Sunflower");
    GiftWrap *gift = new GiftWrap(base);
    DecorativePot *pot = new DecorativePot(gift);

    std::string description = pot->getDescription();
    CHECK(description.find("Sunflower") != std::string::npos);
    CHECK(description.find("Gift Wrapped") != std::string::npos);
    CHECK(description.find("Decorative Pot") != std::string::npos);
    CHECK(pot->getPrice() > 15.0);

    delete pot;
}

TEST_CASE("Decorator: Arrangement and Gift Combination")
{
    BasePlant *base = new BasePlant(35.0, "Rose Bush");
    SpecialArrangement *arrange = new SpecialArrangement(base);
    GiftWrap *gift = new GiftWrap(arrange);

    std::string description = gift->getDescription();
    CHECK(description.find("Rose Bush") != std::string::npos);
    CHECK(description.find("Special Arrangement") != std::string::npos);
    CHECK(description.find("Gift Wrapped") != std::string::npos);
    CHECK(gift->getPrice() > 35.0);

    delete gift;
}

TEST_CASE("Decorator: Individual Decorator Prices")
{
    double basePrice = 10.0;

    BasePlant *testPlant1 = new BasePlant(basePrice, "Test Plant");
    GiftWrap *gift = new GiftWrap(testPlant1);
    double giftPrice = gift->getPrice() - basePrice;
    CHECK(giftPrice > 0.0);

    BasePlant *testPlant2 = new BasePlant(basePrice, "Test Plant");
    DecorativePot *pot = new DecorativePot(testPlant2);
    double potPrice = pot->getPrice() - basePrice;
    CHECK(potPrice > 0.0);

    BasePlant *testPlant3 = new BasePlant(basePrice, "Test Plant");
    SpecialArrangement *arrange = new SpecialArrangement(testPlant3);
    double arrangePrice = arrange->getPrice() - basePrice;
    CHECK(arrangePrice > 0.0);

    delete gift;
    delete pot;
    delete arrange;
}

TEST_CASE("Decorator: Cumulative Pricing")
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

    CHECK(actualTotal == doctest::Approx(expectedTotal).epsilon(0.01));

    delete gift;
    delete pot;
    delete arrange;
    delete step3;
}

TEST_CASE("Decorator: Zero Price Plant")
{
    BasePlant *zeroPrice = new BasePlant(0.0, "Free Plant");
    GiftWrap *wrappedFree = new GiftWrap(zeroPrice);

    CHECK(zeroPrice->getPrice() == 0.0);
    CHECK(wrappedFree->getPrice() >= 0.0);

    delete wrappedFree;
}

TEST_CASE("Decorator: Negative Price Plant")
{
    BasePlant *negativePrice = new BasePlant(-5.0, "Discount Plant");
    DecorativePot *pottedDiscount = new DecorativePot(negativePrice);

    CHECK(negativePrice->getPrice() == -5.0);

    delete pottedDiscount;
}
