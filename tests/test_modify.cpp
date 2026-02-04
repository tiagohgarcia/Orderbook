#include "../src/order_book.hpp"
#include <cassert>

void test_modify_quantity_resting_order() {
    OrderBook book;

    Order order1 = {
        1,
        BUY,
        10,
        50
    };

    Order order2 = {
        2,
        BUY,
        10,
        50
    };

    book.match_order(order1);
    book.match_order(order2);

    bool ok = book.modify_quantity(order1.id, 20);

    assert(ok);
    assert(book.has_order(order1.id));
    assert(book.has_order(order2.id));
    
    // create matching order
    Order order3 = {
        3,
        SELL,
        10,
        50
    };

    book.match_order(order3);

    assert(book.has_order(order1.id));
    assert(!book.has_order(order2.id));
    assert(!book.has_order(order3.id));
    assert(!book.empty());
}

void test_modify_price_resting_order() {
    OrderBook book;

    Order order1 = {
        1,
        BUY,
        10,
        50
    };

    Order order2 = {
        2,
        BUY,
        20,
        50
    };

    book.match_order(order1);
    book.match_order(order2);

    bool ok = book.modify_price(order1.id, 20);

    assert(ok);
    assert(book.has_order(order1.id));
    assert(book.has_order(order2.id));
    
    // create matching order
    Order order3 = {
        3,
        SELL,
        20,
        50
    };

    book.match_order(order3);

    assert(book.has_order(order1.id));
    assert(!book.has_order(order2.id));
    assert(!book.has_order(order3.id));
    assert(!book.empty());

    // create matching order 
    Order order4 = {
        4,
        SELL,
        20,
        50
    };
    
    book.match_order(order4);

    assert(!book.has_order(order1.id));
    assert(book.empty());
}

void test_modify_price_non_existent_order() {
    OrderBook book;

    bool ok = book.modify_price(1, 20);

    assert(!ok);
    assert(!book.has_order(1));
    assert(book.empty());
}

void test_modify_price_resting_order_with_immediate_full_match() {
    OrderBook book;

    Order order1 = {
        1,
        BUY,
        10,
        50
    };

    Order order2 = {
        2,
        SELL,
        20,
        50
    };

    book.match_order(order1);
    book.match_order(order2);

    assert(book.has_order(order1.id));
    assert(book.has_order(order2.id));

    bool ok = book.modify_price(order1.id, 20);

    assert(ok);
    assert(!book.has_order(order1.id)); // immediate match of order1 with order2, so they dont exist in the book anymore
    assert(!book.has_order(order2.id));
    assert(book.empty());
}