//
// Created by Maksym Selishchev on 19/12/2023.
//

#include <iostream>
#include <type_traits>
#include "Array.h"



template <typename  T>
T& Array<T>::operator[](size_t index) {
        if (index < size) {
            return elements[index];
        } else {
            std::cout << "Index out of bounds\n";

        }
}




