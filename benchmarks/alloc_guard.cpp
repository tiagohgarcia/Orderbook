#include <atomic>
#include <cstdlib>
#include <new>
#include <cstddef>

std::atomic<uint64_t> g_new_calls{0};
std::atomic<bool> g_guard_on{false};

void* operator new(std::size_t sz) {
    g_new_calls.fetch_add(1, std::memory_order_relaxed);

    if (g_guard_on.load(std::memory_order_relaxed)) {
        //std::abort();
    }

    if (void* p = std::malloc(sz)) return p;
    throw std::bad_alloc{};
}

void operator delete(void* p) noexcept {
    std::free(p);
}

void operator delete(void* p, std::size_t) noexcept {
    std::free(p);
}

void operator delete[](void* p, std::size_t) noexcept {
    std::free(p);
}

void* operator new[](std::size_t sz) {
    g_new_calls.fetch_add(1, std::memory_order_relaxed);

    if (g_guard_on.load(std::memory_order_relaxed)) {
        //std::abort();
    }

    if (void* p = std::malloc(sz)) return p;
    throw std::bad_alloc{};
}

void operator delete[](void* p) noexcept {
    std::free(p);
}