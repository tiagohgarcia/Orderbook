#pragma once

#include <list>
#include "order.hpp"

struct OrderLocation {
    Side side;
    uint64_t price;
    Order* order;
};