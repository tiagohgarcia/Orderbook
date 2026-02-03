#include <cassert>

#include "price_level.hpp"

PriceLevel::PriceLevel()
{
    head = nullptr;
    tail = nullptr;
}

PriceLevel::~PriceLevel()
{
}

void PriceLevel::push_back(Order* order) {
    assert((head == nullptr) == (tail == nullptr)); // debug
    
    order->next = nullptr;

    if(head == nullptr) { // empty
        head = tail = order;
        order->prev = nullptr;
        return;
    }

    order->prev = tail;
    tail->next = order; 
    tail = order;
 
}

Order* PriceLevel::pop_front() {
    if(head == nullptr) return nullptr;

    Order* old_head = head;
    if(head == tail) { // only one element
        head = nullptr;    
        tail = nullptr;
    }
    else {
        head = old_head->next;
        head->prev = nullptr;
    }
    
    old_head->next = nullptr;
    old_head->prev = nullptr;
    return old_head;
}

void PriceLevel::remove(Order* order) {
    assert((head == nullptr) == (tail == nullptr)); // debug
    
    if(head == nullptr) return; // empty list
    
    Order* prev = order->prev;
    Order* next = order->next;

    if(next) {
        next->prev = prev;
    }
    else { // it is tail
        tail = prev;
    }

    if(prev) {
        prev->next = next;
    }
    else { // it is head
        head = next;
    }

    order->prev = nullptr;
    order->next = nullptr;

    if(head) head->prev = nullptr;
    if(tail) tail->next = nullptr;
}