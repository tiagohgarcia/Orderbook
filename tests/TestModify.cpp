#include "../src/OrderBook.hpp"
#include <cassert>

void testModifyQuantityRestingOrder() {
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

    book.matchOrder(order1);
    book.matchOrder(order2);

    bool ok = book.modifyQuantity(order1.id, 20);

    assert(ok);
    assert(book.hasOrder(order1.id));
    assert(book.hasOrder(order2.id));
    
    // create matching order
    Order order3 = {
        3,
        SELL,
        10,
        50
    };

    book.matchOrder(order3);

    assert(book.hasOrder(order1.id));
    assert(!book.hasOrder(order2.id));
    assert(!book.hasOrder(order3.id));
    assert(!book.empty());
}

void testModifyPriceRestingOrder() {
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

    book.matchOrder(order1);
    book.matchOrder(order2);

    bool ok = book.modifyPrice(order1.id, 20);

    assert(ok);
    assert(book.hasOrder(order1.id));
    assert(book.hasOrder(order2.id));
    
    // create matching order
    Order order3 = {
        3,
        SELL,
        20,
        50
    };

    book.matchOrder(order3);

    assert(book.hasOrder(order1.id));
    assert(!book.hasOrder(order2.id));
    assert(!book.hasOrder(order3.id));
    assert(!book.empty());

    // create matching order 
    Order order4 = {
        4,
        SELL,
        20,
        50
    };
    
    book.matchOrder(order4);
    
    assert(!book.hasOrder(order1.id));
    assert(book.empty());
}