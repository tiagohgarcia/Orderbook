# Baseline benchmarks — Phase 2 (std::map + std::list)

**Machine**: Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz\
**Compiler**: gcc 13.3.0\
**Flags**: -O3 -DNDEBUG\
**Iterations**: 300\
**Workload:**
- Single price level
- Market BUY consuming full FIFO
- FIFO depths: 100 / 1000 / 10000

### Match
| Depth | Mean (µs) | p50 | p95 | p99 | Max |
|------:|----------:|----:|----:|----:|----:|
| 100   | 3.963 | 3.693 | 3.767 | 7.326 | 35.108 |
| 1k    | 51.7392 | 44.069 | 92.607 | 125.217 | 222.674 |
| 10k   | 582.078 | 512.495 | 1077.67 | 1918.65 | 2884.76 |

### Insert
| Depth | Mean (µs) | p50 | p95 | p99 | Max |
|------:|----------:|----:|----:|----:|----:|
| 100   | 0.09326 | 0.091 | 0.116 | 0.17 | 0.2 |
| 1k    | 0.104397 | 0.096 | 0.135 | 0.163 | 5.422 |
| 10k   | 0.150705 | 0.15 | 0.182 | 0.204 | 5.069 |

### Cancel
| Depth | Mean (µs) | p50 | p95 | p99 | Max |
|------:|----------:|----:|----:|----:|----:|
| 100   | 0.06493 | 0.06 | 0.097 | 0.125 | 0.253 |
| 1k    | 0.059756 | 0.052 | 0.085 | 0.116 | 0.431 |
| 10k   | 0.0757988 | 0.073 | 0.116 | 0.149 | 3.132 |

### Observations
- Match latency scales linearly with FIFO depth (~50 ns/order).
- Tail latency grows superlinearly with depth.
- Insert and cancel are O(1) and negligible compared to match.
- Optimization effort should focus exclusively on match/FIFO traversal.