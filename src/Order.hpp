#pragma once

#include <cstdint>

enum Side : uint8_t {
    BUY,
    SELL
};

struct Order {
    uint16_t id;
    Side side;
    uint64_t price;
    uint32_t quantity;
};

