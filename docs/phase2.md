# Phase 2 - design

## index map
Create map<OrderId, OrderLocation> index

OrderLocation:
- Side
- Price
- iterator

So i need to change the ask and bid maps from deque<Order> to list<Order>
This allows erasing in O(1) given an iterator
Not so great for searching though due to heap fragmentation, cache fragmentation, pointer chasing

## Invariants
1. Every entry in index must point to valid resting order in the book
2. Every resting order in the book must have exatly one entry in index
3. Any operation that removes the order from the book must remove it from index too
4. No empty price levels
5. Index and book agree on side/price

## Modify semnatics

Guiding principle:
Time priority is a reward for being earlier

- Every modification will put the order at the back of the FIFO


## Testing

1. Testing cancel correctness

- Precondition: the order exists and its cancelable
- Action: cancel(id)
- Postconditions:
    1. Cancel returns true
    2. index does not contain id
    3. book does not contain id
    4. book invariants still hold
    5. if the price level becomes empty, it was removed

2. Testing modify quantity

- Precondition: two orders at the same price level (A and B)
- Action: modify(id of A)
- Postconditions:
    1. Modify returns true
    2. Index still contains id of A
    3. book contains A behind order B in FIFO
    4. price level still exists

3. Testing modify price

- Precondition: two orders at the different price levels (A and B)
- Action: modify(id of A) -> to match B price level
- Postconditions:
    1. Modify returns true
    2. Index still contains id of A
    3. book contains A behind order B in FIFO
    4. old price level of A was deleted

## Implementation

1. Cancel flow

    - Cancel and full-fill removal are the only two code paths that erase resting orders.

    1. Lookup id in index
    2. If not found → return “not canceled” (false)
    3. Read OrderLocation (side, price, iterator)
    4. Use side and price to access the correct price-level FIFO container
    5. Erase using iterator
    6. If FIFO becomes empty → erase price level
    7. Erase the index entry
    8. Return “canceled” (true)

    - Edge cases
        1. Cancel already-filled order
            - remove entry on full fill
        2. Cancel partially filled order
        3. Cancel the last order at a price level

2. Modify flow

    - A modified order is treated as a new order and re-enters the matching flow

    1. Lookup id in index
    2. if not found → return "not modified" (false)
    3. Read OrderLocation (side, price, iterator)
    4. Use side and price to access the correct price-level FIFO container
    5. Erase using iterator
    6. If FIFO becomes empty → erase price level
    7. Create new order with modified fields
    8. Submit new order through matchOrder
    9. Return "modified" (true)

# Phase 2 - part 1

- [x] Change deque → list
- [x] Introduce OrderLocation and index map
- [x] Write cancel(id) and tests
- [x] Write modify(id) and tests
