#include <iostream>

void test_cancel_single_resting_order();
void test_cancel_last_order_at_price_level();
void test_cancel_non_existent_order();

void test_modify_quantity_resting_order();
void test_modify_price_resting_order();
void test_modify_price_non_existent_order();
void test_modify_price_resting_order_with_immediate_full_match();

int main() {

    // cancel tests
    test_cancel_single_resting_order();
    test_cancel_last_order_at_price_level();
    test_cancel_non_existent_order();

    // modify tests
    test_modify_quantity_resting_order();
    test_modify_price_resting_order();
    test_modify_price_non_existent_order();
    test_modify_price_resting_order_with_immediate_full_match();

    std::cout << "All tests passed!!" << std::endl;
}