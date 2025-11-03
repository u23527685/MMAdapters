// #include <iostream>
// #include <string>
// #include "Transaction.h"
// #include "TransactionHistory.h"
// #include "Customer.h"
// #include "Order.h"
// #include "PaymentStrategy.h"
// #include "CreditCardPaymentStrategy.h"
// #include "EFTPaymentStrategy.h"
// #include "EWalletPaymentStrategy.h"

// int main() {
//     std::cout << "=== Memento Pattern Test with Payment Strategies ===\n";

//     std::string userInput;
//     std::cout << "Enter your name: ";
//     std::getline(std::cin, userInput);

//     if (userInput.empty()) {
//         userInput = "DefaultUser";
//     }

//     Customer customer(userInput);
//     std::cout << "Customer name set to: " << customer.getName() << "\n";
//     std::cout << "Set Name to Jerusha use setName() " << "\n";
//     customer.setName("Jerusha");  
//     std::cout << "Customer name set to: " << customer.getName() << "\n";

//     TransactionHistory history;

//     CreditCardPaymentStrategy credit("1111-2222-3333-4444");
//     EFTPaymentStrategy eft("ACC-987654321");
//     EWalletPaymentStrategy wallet("WALLET-ABC123");

//     Transaction t1("ORD001", 200.0, 2);
//     Transaction t2("ORD002", 150.5, 1);
//     Transaction t3("ORD003", 300.75, 3);

//     t1.setPaymentStrategy(&credit);
//     t2.setPaymentStrategy(&eft);
//     t3.setPaymentStrategy(&wallet);

 
//     history.addSnapshot(t1.createSnapshot());
//     history.addSnapshot(t2.createSnapshot());
//     history.addSnapshot(t3.createSnapshot());

   
//     t1.setTransaction("ORD001_MOD", 500.0, 1);
//     std::cout << "\n--- Modified Transaction ---\n";
//     t1.getDetails();

//     std::cout << "\nRestoring original snapshot...\n";
//     TransactionSnapshot snap = history.getSnapshot(0);
//     t1.restoreSnapshot(snap);
//     t1.getDetails();

//     Transaction* tClone = t2.clone();
//     std::cout << "\n--- Cloned Transaction ---\n";
//     tClone->getDetails();

//     std::cout << "\n--- Processing Payments ---\n";
//     t1.processPayment();
//     t2.processPayment();
//     t3.processPayment();

   
//     Order order(&customer, "ORDER-1001");
//     order.addTransaction(&t1);
//     order.addTransaction(&t2);
//     order.addTransaction(&t3);

//     order.processOrder();
//     order.displayOrderDetails();

   
//     customer.placeOrder(order);
//     customer.viewOrders();

//     std::cout << "\n--- Extra Coverage ---\n";
//     Customer tempCustomer;
//     tempCustomer.setName("Jerusha");
//     std::cout << "Temporary customer name: " << tempCustomer.getName() << "\n";


//     delete tClone;

//     std::cout << "\n=== End of Test ===\n";
//     return 0;
// }
