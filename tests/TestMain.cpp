#include <iostream>

void testCancelSingleRestingOrder();
void testCancelLastOrderAtPriceLevel();
void testCancelNonExistentOrder();

int main() {

    // cancel tests
    testCancelSingleRestingOrder();
    testCancelLastOrderAtPriceLevel();
    testCancelNonExistentOrder();

    std::cout << "All tests passed!!" << std::endl;
}