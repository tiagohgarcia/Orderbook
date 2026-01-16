#include "Order.hpp"
#include <map>
#include <deque>

using namespace std;

class OrderBook
{
private:
    map<uint64_t, deque<Order>> asks; // sell orders
    map<uint64_t, deque<Order>, greater<>> bids; // buy orders
public:
    OrderBook(/* args */);
    ~OrderBook();

    void storeOrder(Order order);
};
