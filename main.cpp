#include <iostream>
#include "OrderBook.hpp"

int main() {

       std::cout << R"(  ____           _              ____              _
 / __ \         | |            |  _ \            | |
| |  | |_ __   _| | ___ _ __   | |_) | ___   ___ | | __
| |  | | '__|/ _` |/ _ \ '__|  |  _ < / _ \ / _ \| |/ /
| |__| | |  | (_| |  __/ |     | |_) | (_) | (_) |   <
 \____/|_|   \__,_|\___|_|     |____/ \___/ \___/|_|\_\

                designed by Red0xe
    )" << std::endl;

    // create instance of OrderBook
    std::cout << "Initializing Order Book..." << std::endl;
    OrderBook orderBook;

    // create fake orders
    int num = 20;
    std::cout << "Creating " << num << " fake orders..." << std::endl;
    for (int i = 1; i <= num; ++i) {
        Order order = {
            static_cast<uint16_t>(i),
            (i % 2 == 0) ? SELL : BUY,
            static_cast<uint64_t>(1000 + (i%5) * 10), // price
            static_cast<uint32_t>(50 + (i%5) * 5) // quantity
        };
        
        orderBook.storeOrder(order);
    }
    std::cout << "Created " << num << " orders" << std::endl;

    orderBook.printBids();
    orderBook.printAsks();

    return 0;
}