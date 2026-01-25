#include <chrono>
#include <cstdint>
#include <vector>

using Clock = std::chrono::steady_clock;

struct Stats {
    double p50_us = 0,
    double p95_us = 0,
    double p99_us = 0,
    double mean_us = 0,
    double max_us = 0
};


static Stats computeStats(std:vector<uint64_t>& samples_ns) {
    std::sort(samples_ns.begin(), samples_ns.end());
    auto n = samples_ns.size();

    auto at = [&](double q) -> double {
        size_t idx = (size_t)((n - 1) * q);
        return samples_ns[idx] / 1000.0; // ns -> us
    }

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

static void printStats(const char* name, const Stats& s) {
    std::cout << name
              << " mean(us)=" << s.mean_us
              << " p50=" << s.p50_us
              << " p95=" << s.p95_us
              << " p99=" << s.p99_us
              << " max=" << s.max_us
              << "\n";
}

int main() {

}