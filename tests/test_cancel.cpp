#include "../src/order_book.hpp"
#include <cassert>

void test_cancel_single_resting_order() {
    OrderBook book;

    Order order = {
        static_cast<uint16_t>(1),
        BUY,
        static_cast<uint64_t>(10),
        static_cast<uint32_t>(50)
    };

    book.match_order(order);

    bool ok = book.cancel_order(order.id);

    assert(ok);
    assert(book.empty());
    assert(!book.has_order(order.id));
}

void test_cancel_last_order_at_price_level() {
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

    book.match_order(order1);
    book.match_order(order2);

    bool ok = book.cancel_order(order1.id);

    assert(ok);
    assert(!book.empty());
    assert(!book.has_order(order1.id));
    assert(book.has_order(order2.id));

    ok = book.cancel_order(order2.id);

    assert(ok);
    assert(book.empty());
    assert(!book.has_order(order2.id));
}

void test_cancel_non_existent_order() {
    OrderBook book;

    uint16_t orderId = 1;

    bool ok = book.cancel_order(orderId);

    assert(!ok);
    assert(book.empty());
    assert(!book.cancel_order(orderId));
}