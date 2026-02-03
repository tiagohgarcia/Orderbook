#pragma once

#include <list>
#include "order.hpp"

struct OrderLocation {
    Side side;
    uint64_t price;
    std::list<Order>::iterator it;
};