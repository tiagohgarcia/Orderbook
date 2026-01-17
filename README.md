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

- [x] Small CLI
- [x] Hard-coded test scenarios
- [x] Text Output showing Trades

#### Improvements
- [ ] separate match Buy and match Sell