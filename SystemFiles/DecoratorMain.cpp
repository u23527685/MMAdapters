// #include "BasePlant.h"
// #include "GiftWrap.h"
// #include "DecorativePot.h"
// #include "SpecialArrangement.h"
// #include <iostream>
// #include <iomanip>
// #include <memory>

// void testBasePlant() {
//     std::cout << "=== TESTING BASE PLANT ===" << std::endl;
//     BasePlant basicPlant;
//     std::cout << "Basic Plant - Description: " << basicPlant.getDescription() 
//               << ", Price: R" << std::fixed << std::setprecision(2) << basicPlant.getPrice() << std::endl;
    
//     BasePlant customPlant(25.99, "Custom Rose");
//     std::cout << "Custom Plant - Description: " << customPlant.getDescription() 
//               << ", Price: R" << customPlant.getPrice() << std::endl;
//     std::cout << std::endl;
// }

// void testGiftWrap() {
//     std::cout << "=== TESTING GIFT WRAP ===" << std::endl;
    
//     BasePlant* basic = new BasePlant();
//     GiftWrap* giftWrappedBasic = new GiftWrap(basic);
//     std::cout << "Gift Wrapped Basic - Description: " << giftWrappedBasic->getDescription() 
//               << ", Price: R" << std::fixed << std::setprecision(2) << giftWrappedBasic->getPrice() << std::endl;
    
    
//     BasePlant* custom = new BasePlant(30.0, "Orchid");
//     GiftWrap* giftWrappedCustom = new GiftWrap(custom);
//     std::cout << "Gift Wrapped Custom - Description: " << giftWrappedCustom->getDescription() 
//               << ", Price: R" << giftWrappedCustom->getPrice() << std::endl;
    
//     delete giftWrappedBasic; 
//     delete giftWrappedCustom;
//     std::cout << std::endl;
// }

// void testDecorativePot() {
//     std::cout << "=== TESTING DECORATIVE POT ===" << std::endl;
    
//     BasePlant* basic = new BasePlant();
//     DecorativePot* pottedBasic = new DecorativePot(basic);
//     std::cout << "Potted Basic - Description: " << pottedBasic->getDescription() 
//               << ", Price: R" << std::fixed << std::setprecision(2) << pottedBasic->getPrice() << std::endl;
    
//     BasePlant* custom = new BasePlant(45.50, "Bonsai Tree");
//     DecorativePot* pottedCustom = new DecorativePot(custom);
//     std::cout << "Potted Custom - Description: " << pottedCustom->getDescription() 
//               << ", Price: R" << pottedCustom->getPrice() << std::endl;
    
//     delete pottedBasic; 
//     delete pottedCustom; 
//     std::cout << std::endl;
// }

// void testSpecialArrangement() {
//     std::cout << "=== TESTING SPECIAL ARRANGEMENT ===" << std::endl;
    
//     BasePlant* basic = new BasePlant();
//     SpecialArrangement* arrangedBasic = new SpecialArrangement(basic);
//     std::cout << "Arranged Basic - Description: " << arrangedBasic->getDescription() 
//               << ", Price: R" << std::fixed << std::setprecision(2) << arrangedBasic->getPrice() << std::endl;
    
    
//     BasePlant* custom = new BasePlant(60.75, "Exotic Flower Bouquet");
//     SpecialArrangement* arrangedCustom = new SpecialArrangement(custom);
//     std::cout << "Arranged Custom - Description: " << arrangedCustom->getDescription() 
//               << ", Price: R" << arrangedCustom->getPrice() << std::endl;
    
//     delete arrangedBasic; 
//     delete arrangedCustom; 
//     std::cout << std::endl;
// }

// void testMultipleDecorations() {
//     std::cout << "=== TESTING MULTIPLE DECORATIONS ===" << std::endl;
    
//     BasePlant* base = new BasePlant(20.0, "Tulip");
//     GiftWrap* giftWrapped = new GiftWrap(base);
//     DecorativePot* potted = new DecorativePot(giftWrapped);
//     SpecialArrangement* fullyDecorated = new SpecialArrangement(potted);
    
//     std::cout << "Fully Decorated Plant - Description: " << fullyDecorated->getDescription() 
//               << ", Price: R" << std::fixed << std::setprecision(2) << fullyDecorated->getPrice() << std::endl;
    
    
//     std::cout << "\n--- Testing Different Combinations ---" << std::endl;
    
    
//     BasePlant* base2 = new BasePlant(15.0, "Sunflower");
//     GiftWrap* gift2 = new GiftWrap(base2);
//     DecorativePot* pot2 = new DecorativePot(gift2);
//     std::cout << "Gift + Pot - Description: " << pot2->getDescription() 
//               << ", Price: R" << pot2->getPrice() << std::endl;
    
//     BasePlant* base3 = new BasePlant(35.0, "Rose Bush");
//     SpecialArrangement* arrange3 = new SpecialArrangement(base3);
//     GiftWrap* gift3 = new GiftWrap(arrange3);
//     std::cout << "Arrange + Gift - Description: " << gift3->getDescription() 
//               << ", Price: R" << gift3->getPrice() << std::endl;
    
//     delete fullyDecorated; 
//     delete pot2; 
//     delete gift3; 
//     std::cout << std::endl;
// }

// void testPriceCalculations() {
//     std::cout << "=== TESTING PRICE CALCULATIONS ===" << std::endl;
    
//     BasePlant basePlant(10.0, "Test Plant");
//     double basePrice = basePlant.getPrice();
    
//     BasePlant* testPlant = new BasePlant(10.0, "Test Plant");
//     GiftWrap* gift = new GiftWrap(testPlant);
//     double giftPrice = gift->getPrice() - basePrice;
    
//     BasePlant* testPlant2 = new BasePlant(10.0, "Test Plant");
//     DecorativePot* pot = new DecorativePot(testPlant2);
//     double potPrice = pot->getPrice() - basePrice;
    
//     BasePlant* testPlant3 = new BasePlant(10.0, "Test Plant");
//     SpecialArrangement* arrange = new SpecialArrangement(testPlant3);
//     double arrangePrice = arrange->getPrice() - basePrice;
    
//     std::cout << "Base Price: R" << std::fixed << std::setprecision(2) << basePrice << std::endl;
//     std::cout << "Gift Wrap Additional Cost: R" << giftPrice << std::endl;
//     std::cout << "Decorative Pot Additional Cost: R" << potPrice << std::endl;
//     std::cout << "Special Arrangement Additional Cost: R" << arrangePrice << std::endl;
    
//     BasePlant* cumulativeTest = new BasePlant(10.0, "Cumulative Test");
//     GiftWrap* step1 = new GiftWrap(cumulativeTest);
//     DecorativePot* step2 = new DecorativePot(step1);
//     SpecialArrangement* step3 = new SpecialArrangement(step2);
    
//     double expectedTotal = basePrice + giftPrice + potPrice + arrangePrice;
//     double actualTotal = step3->getPrice();
    
//     std::cout << "\nCumulative Pricing Test:" << std::endl;
//     std::cout << "Expected Total: R" << expectedTotal << std::endl;
//     std::cout << "Actual Total: R" << actualTotal << std::endl;
//     std::cout << "Match: " << (std::abs(expectedTotal - actualTotal) < 0.01 ? "YES" : "NO") << std::endl;
    
//     delete step3; 
//     std::cout << std::endl;
// }

// void testEdgeCases() {
//     std::cout << "=== TESTING EDGE CASES ===" << std::endl;
    
//     BasePlant* zeroPrice = new BasePlant(0.0, "Free Plant");
//     GiftWrap* wrappedFree = new GiftWrap(zeroPrice);
//     std::cout << "Free Plant + Gift Wrap - Description: " << wrappedFree->getDescription() 
//               << ", Price: R" << std::fixed << std::setprecision(2) << wrappedFree->getPrice() << std::endl;
    
//     BasePlant* negativePrice = new BasePlant(-5.0, "Discount Plant");
//     DecorativePot* pottedDiscount = new DecorativePot(negativePrice);
//     std::cout << "Discount Plant + Pot - Description: " << pottedDiscount->getDescription() 
//               << ", Price: R" << pottedDiscount->getPrice() << std::endl;
    
//     delete wrappedFree;
//     delete pottedDiscount;
//     std::cout << std::endl;
// }

// int main() {
//     std::cout << "PLANT DECORATOR PATTERN TEST SUITE\n" << std::endl;
    
//     testBasePlant();
//     testGiftWrap();
//     testDecorativePot();
//     testSpecialArrangement();
//     testMultipleDecorations();
//     testPriceCalculations();
//     testEdgeCases();
    
//     std::cout << "=== ALL TESTS COMPLETED ===" << std::endl;
//     return 0;
// }