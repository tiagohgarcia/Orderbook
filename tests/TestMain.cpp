#include <iostream>

void testCancelSingleRestingOrder();
void testCancelLastOrderAtPriceLevel();
void testCancelNonExistentOrder();

void testModifyQuantityRestingOrder();
void testModifyPriceRestingOrder();

int main() {

    // cancel tests
    testCancelSingleRestingOrder();
    testCancelLastOrderAtPriceLevel();
    testCancelNonExistentOrder();

    // modify tests
    testModifyQuantityRestingOrder();
    testModifyPriceRestingOrder();

    std::cout << "All tests passed!!" << std::endl;
}