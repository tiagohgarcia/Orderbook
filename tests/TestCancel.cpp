#include "../src/OrderBook.hpp"
#include <cassert>

void testCancelSingleRestingOrder() {
    OrderBook book;

    Order order = {
        static_cast<uint16_t>(1),
        BUY,
        static_cast<uint64_t>(10),
        static_cast<uint32_t>(50)
    };

    book.matchOrder(order);

    bool ok = book.cancelOrder(order.id);

    assert(ok);
    assert(book.empty());
    assert(!book.hasOrder(order.id));
}

void testCancelLastOrderAtPriceLevel() {
    OrderBook book;

    Order order1 = {
        static_cast<uint16_t>(1),
        BUY,
        static_cast<uint64_t>(10),
        static_cast<uint32_t>(50)
    };

    Order order2 = {
        static_cast<uint16_t>(2),
        BUY,
        static_cast<uint64_t>(10),
        static_cast<uint32_t>(50)
    };

    book.matchOrder(order1);
    book.matchOrder(order2);

    bool ok = book.cancelOrder(order1.id);

    assert(ok);
    assert(!book.empty());
    assert(!book.hasOrder(order1.id));
    assert(book.hasOrder(order2.id));

    ok = book.cancelOrder(order2.id);

    assert(ok);
    assert(book.empty());
    assert(!book.hasOrder(order2.id));
}

void testCancelNonExistentOrder() {
    OrderBook book;

    uint16_t orderId = 1;

    bool ok = book.cancelOrder(orderId);

    assert(!ok);
    assert(book.empty());
    assert(!book.cancelOrder(orderId));
}