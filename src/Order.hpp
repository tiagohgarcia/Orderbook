#include <cstdint>

enum Side {
    BUY,
    SELL
};

struct Order {
    uint16_t id;
    Side side;
    uint64_t price;
    uint32_t quantity;
};

