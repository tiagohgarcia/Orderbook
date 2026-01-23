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
- [x] Create order location
- [x] Cancel order
- [x] Modify order

## Phase 3

- optimize for efficient structures
- measure "time per match", "time per insert", "time per cancel"
- preserve invariants (price-time priority, deterministic)
----------------------------------
- [ ] Measure times
- [ ] Optimize for Flat price levels + intrusive FIFO
