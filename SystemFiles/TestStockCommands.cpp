#include "AddStock.h"
#include "RemoveStock.h"
#include "PlantStock.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "=== Testing PlantStock and Command Pattern ===" << endl;

    PlantStock stock;

    cout << "\n[TEST] Directly calling PlantStock methods:" << endl;
    stock.addStock("Rose", 20);
    stock.removeStock("Lily", 5);

    cout << "\n[TEST] Creating Command objects..." << endl;
    addStock addCmd1(&stock, "Tulip", 15);
    removeStock removeCmd1(&stock, "Tulip", 5);

    cout << "\n[TEST] Executing commands individually:" << endl;
    addCmd1.execute();
    removeCmd1.execute();

    cout << "\n[TEST] Executing a sequence of commands:" << endl;
    vector<StockCommand*> commandList;

    commandList.push_back(new addStock(&stock, "Lavender", 30));
    commandList.push_back(new addStock(&stock, "Sunflower", 25));
    commandList.push_back(new removeStock(&stock, "Lavender", 10));

    for (int i = 0; i < commandList.size(); i++) {
        commandList[i]->execute();
    }

    for (int i = 0; i < commandList.size(); i++) {
        delete commandList[i];
    }

    cout << "\n=== All tests executed successfully ===" << endl;
    return 0;
}
