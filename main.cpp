#include <iostream>
#include "OrderBook.hpp"

using namespace std;

int main() {

    cout << "Welcome to the Trading System!" << endl;

    // create instance of OrderBook
    cout << "Initializing Order Book..." << endl;
    OrderBook orderBook;

    // create fake orders
    cout << "Creating fake orders..." << endl;
    for (int i = 1; i <= 6; ++i) {
        Order order = {
            static_cast<uint16_t>(i),
            (i % 2 == 0) ? SELL : BUY,
            static_cast<uint64_t>(1000 + i * 10),
            static_cast<uint32_t>(50 + i * 5)
        };
        cout << "Order " << i << " created." << endl;

        orderBook.storeOrder(order);
    }

    return 0;
}