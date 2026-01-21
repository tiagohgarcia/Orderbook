# Orderbook


## Data Model

### Order
- id
- side (buy or sell)
- quantity
- price

### Order Book
- Bids sorted descending (Buy)
- Asks sorted ascending (Sell)

`map<Price, deque<Order>>`


## Phase 1
- matching semantics
- maintain book invariants
- reason about state
----------------------------------
- [x] Small CLI
- [x] Hard-coded test scenarios
- [x] Text Output showing Trades

#### Improvements
- [x] separate match Buy and match Sell


## Phase 2

- Manage order lifecycle
- Maintain multiple indices consistently
- Design correct mutable systems
----------------------------------
[ ] Create order location
[ ] Cancel order
[ ] Modify order