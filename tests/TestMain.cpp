#include <iostream>

void testCancelSingleRestingOrder();
void testCancelLastOrderAtPriceLevel();
void testCancelNonExistentOrder();

void testModifyQuantityRestingOrder();
void testModifyPriceRestingOrder();
void testModifyPriceNonExistentOrder();
void testModifyPriceRestingOrderWithImmediateFullMatch();

int main() {

    // cancel tests
    testCancelSingleRestingOrder();
    testCancelLastOrderAtPriceLevel();
    testCancelNonExistentOrder();

    // modify tests
    testModifyQuantityRestingOrder();
    testModifyPriceRestingOrder();
    testModifyPriceNonExistentOrder();
    testModifyPriceRestingOrderWithImmediateFullMatch();

    std::cout << "All tests passed!!" << std::endl;
}