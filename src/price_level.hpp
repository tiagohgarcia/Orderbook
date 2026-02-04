#pragma once

#include "order.hpp"

class PriceLevel
{
private:
    Order* head;
    Order* tail;
public:
    PriceLevel(/* args */);
    ~PriceLevel();

    void push_back(Order* order);
    Order* pop_front();
    Order* front() const;
    void remove(Order* order);
    bool empty();
};


