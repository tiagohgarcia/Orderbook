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

**Invariants:**
- Price–time priority is preserved
- FIFO order is preserved within a price level
- Cancel and modify remain O(1)
- Phase-2 tests pass unchanged
- Deterministic outcomes for identical input

**Outcomes:**

Expected:
- Match latency decreases noticeably
- Tail latency tightens

Possible:
- Insert latency slightly worse

Unacceptable:
- Non-deterministic behavior
- Cancel complexity regression
- Test instability

## Change price level indexing

> **What do I gain and what do I lose?**

## Price Level Indexing

**current**:
- Ordered tree
- O(log n) inserts
- Pointer-heavy traversal

**Hypothesis:**
- Matching benefits from cache-friendly sequential access
- inserts may become more expensive
- Overall throughput improves under realistic flows

## Measurement

**Metrics:**
- Time per match
- Time per insert
- Time per cancel
- Latency distribution (not just average)

> All benchmarks will be run after warm-up to avoid allocator and cache cold-start artifacts.

**Workload assumptions:**
- Ratio of market vs limit orders
- Typical book depth
- Price distribution
- Cancel/modify frequency

**Questions to answer:**
Q: Which operation improved the most?
A: Match operation

Q: Which got worse?
A: Match operation at 100 depth

Q: Did tail latency improve?
A: yes

Q: Was deterministic preserved?
A: yes

## Non-goals of Phase 3

- No threading
- No lock-free structures
- No semantic changes
- No feature additions