#include "Transaction.h"
#include "CreditCardPaymentStrategy.h"
#include "EWalletPaymentStrategy.h"
#include "EFTPaymentStrategy.h"

int main() {
 
    Transaction tx("Alice", "Plant Pack A", 25.50, 2);
    tx.getDetails();

    CreditCardPaymentStrategy creditCard("1234-5678-9012-3456");
    tx.setPaymentMethod(&creditCard);
    tx.processPayment();

    EWalletPaymentStrategy ewallet("wallet123");
    tx.setPaymentMethod(&ewallet);
    tx.processPayment();

    EFTPaymentStrategy eft("9876543210");
    tx.setPaymentMethod(&eft);
    tx.processPayment();

    return 0;
}
