# Phase 3 - design

## The goal of Phase 3

> **Phase 3 changes only data representation and memory behavior, not matching semantics**


- Preserve invariants (price-time priority, determinism)
- Measure:
    - time per match
    - time per insert
    - time per cancel
- Replace “conceptually clean” structures with physically efficient ones
- Be able to explain why something got faster (or didn’t)

### What to fix

- `std::map` → pointer-heavy, cache-hostile
    - Tree traversal on every price access
- `std::list` → pointer chasing on every match
    - Pointer chasing during FIFO traversal
- Each order = multiple heap allocations
    - Heap allocation on every order insertion
- Poor spatial locality
    - Poor cache line reuse
- Branch-heavy traversal
    - Branch misprediction in ordered containers

## Change FIFO representation

> **Reduce pointer indirection and allocations on the hot path**

### FIFO evolution

**Current:**
- `std::list<Order>`
- One allocation per Order
- Each match step = pointer chasing

**Hypothesis:**
- FIFO traversal dominates match latency
- Remove node allocations and reducing indirection improves:
    - Match latency
    - Latency tail (p99+)

## Change price level indexing

> **What do I gain and what do I lose?**

