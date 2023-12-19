#include <iostream>
#include "Array.h"

int main() {
    // Compiles successfully
    Array<int> intArray(5);
//    intArray[2] = 42;
//    std::cout << intArray[2] << std::endl;

    // Results in a compilation error
     Array<std::string> strArray(3);

    return 0;
}
