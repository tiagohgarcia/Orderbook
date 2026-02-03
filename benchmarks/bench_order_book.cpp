#include <chrono>
#include <cstdint>
#include <vector>
#include <iostream>
#include <cassert>

#include "../src/order_book.hpp"

using Clock = std::chrono::steady_clock;

struct Stats {
    double p50_us = 0;
    double p95_us = 0;
    double p99_us = 0;
    double mean_us = 0;
    double max_us = 0;
};

static Stats compute_stats(std::vector<uint64_t>& samples_ns) {
    std::sort(samples_ns.begin(), samples_ns.end());
    auto n = samples_ns.size();

    auto at = [&](double q) -> double {
        size_t idx = (size_t)((n - 1) * q);
        return samples_ns[idx] / 1000.0; // ns -> us
    };

    double sum = 0;
    for(auto ns : samples_ns) {
        sum += (double)ns;
    }

    Stats s;
    s.p50_us = at(0.50);
    s.p95_us = at(0.95);
    s.p99_us = at(0.99);
    s.mean_us = (sum / (double)n) / 1000.0;
    s.max_us = samples_ns.back() / 1000.0;
    return s;
}

static void print_stats(const char* name, const Stats& s) {
    std::cout << name << ": \n"
              << " mean(us) = " << s.mean_us << "\n"
              << " p50 = " << s.p50_us << "\n"
              << " p95 = " << s.p95_us << "\n"
              << " p99 = " << s.p99_us << "\n"
              << " max = " << s.max_us
              << "\n\n";
}

Stats benchmark_match(size_t depth, uint32_t qty_each) {
    const uint64_t price = 100;
    const size_t iters = 300;   // start small, scale later

    std::vector<uint64_t> samples;
    samples.reserve(iters);

    for (size_t i = 0; i < iters; ++i) {
        OrderBook book;

        // preload one deep FIFO
        for (uint32_t j = 0; j < depth; ++j) {
            Order sell {
                static_cast<uint16_t>(j),
                SELL,
                price,
                qty_each
            };
            book.match_order(sell); // rests
        }

        size_t total = depth * qty_each;
        assert(total <= std::numeric_limits<uint32_t>::max());
        uint32_t total_qty = static_cast<uint32_t>(total);

        Order buy {
            9999,
            BUY,
            UINT64_MAX,           // sentinel market price
            total_qty
        };

        auto t0 = Clock::now();
        book.match_order(buy);
        auto t1 = Clock::now();

        samples.push_back(
            std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()
        );
    }

    return compute_stats(samples);
}

Stats benchmark_insert(size_t depth) {
    std::vector<uint64_t> samples;
    samples.reserve(depth);

    OrderBook book;

    for (uint32_t j = 0; j < depth; ++j) {
        Order order {
            static_cast<uint16_t>(j),
            SELL,
            100,
            10
        };

        auto t0 = Clock::now();
        book.match_order(order);
        auto t1 = Clock::now();

        samples.push_back(
            std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()
        );
    }

    return compute_stats(samples);
}

Stats benchmark_cancel(size_t depth) {
    std::vector<uint64_t> samples;
    samples.reserve(depth);

    OrderBook book;

    for (uint32_t j = 0; j < depth; ++j) {
        Order order {
            static_cast<uint16_t>(j),
            SELL,
            100,
            10
        };

        book.match_order(order);
    }

    for (uint32_t j = 0; j < depth; ++j) {
        auto t0 = Clock::now();
        book.cancel_order(static_cast<uint16_t>(j));
        auto t1 = Clock::now();

        samples.push_back(
            std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()
        );
    }

    return compute_stats(samples);
}

int main() {
    size_t depth = 100;
    uint32_t qty = 10;

    auto stats = benchmark_match(depth, qty);
    print_stats("match depth=100", stats);
    stats = benchmark_insert(depth);
    print_stats("insert depth=100", stats);
    stats = benchmark_cancel(depth);
    print_stats("cancel depth=100", stats);

    depth = 1000;
    stats = benchmark_match(depth, qty);
    print_stats("match depth=1000", stats);
    stats = benchmark_insert(depth);
    print_stats("insert depth=1000", stats);
    stats = benchmark_cancel(depth);
    print_stats("cancel depth=1000", stats);

    depth = 10000;
    stats = benchmark_match(depth, qty);
    print_stats("match depth=10000", stats);
    stats = benchmark_insert(10000);
    print_stats("insert depth=10000", stats);
    stats = benchmark_cancel(depth);
    print_stats("cancel depth=10000", stats);
}