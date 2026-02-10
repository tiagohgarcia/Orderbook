# Phase 4 - design

## The goal of phase 4

0 allocations during:
- add()
- match()
- cancel()
- modify()

- **Hot path**: orders + intrusive list operations + best level selection
- **Cold path**: occasional level creation / map rehashing / resize

### Order pool

- Allocate one contiguous block: OrderNode[N] (aligned)
- Maintain a free list of indices (or pointers)
- alloc() pops from free list; free() pushes back
- Deterministic, constant time, no fragmentation \

**When pool is empty:**
- return error (Rejected::OutOfCapacity) deterministically
- do not fall back to new

### Make price levels non-allocating in the hot path

- Pre-allocating a Level pool too (like orders)
- Making price->level map fixed-capacity (open addressing array)
- Or at minimum reserve() enough capacity at startup and never exceed it

### Remove "surpise allocations"

- unordered_map rehash
- vector growth
- string formatting in logs
- std::function captures, etc.

A. Pre-reserve everything that stays

If you keep unordered_map<OrderId, OrderNode*> index:
- index.reserve(MAX_ORDERS * 1.3) (or similar load factor headroom)
- set index.max_load_factor(0.7f) to reduce rehash risk
- never exceed MAX_ORDERS
- This is acceptable if you can guarantee capacity.

B. Add an allocation guard

- Override global operator new/delete in your binary with counters.
- At startup: allow allocations (setup)
- After warm-up: set alloc_guard = true
- In operator new: if guard is enabled → increment counter and optionally std::abort() in debug builds

Then your tests become:
- warm up + reserve
- guard_on()
- run scenarios
- assert(alloc_count == 0)


What I’d do next in your repo (concrete checklist)

Add MAX_ORDERS and MAX_LEVELS constants (or derive from tick range).

Implement OrderPool (slab + free list).

Switch your book to store OrderNode* from the pool (not heap).

Ensure cancel/modify/match return nodes to pool correctly.

Add global allocation counter + “guard” mode.

Add a test: warm-up → guard-on → run 10k operations → assert 0 allocations.

Only then: optimize layout / level representation / branchy code.