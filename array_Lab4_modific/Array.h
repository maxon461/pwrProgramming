//
// Created by Maksym Selishchev on 19/12/2023.
//

#ifndef ARRAY_LAB4_MODIFIC_ARRAY_H
#define ARRAY_LAB4_MODIFIC_ARRAY_H

template <typename T>
class Array {
private:
    T *elements;
    size_t size;
public:
    // Constructor with the number of elements
    explicit Array(size_t sz) : size(sz) {
//        static_assert(!std::is_same<T, std::string>::value, "Array of std::string is not allowed");
        elements = new T[size];
        for(int i=0;i<size;i++){
            elements[i] = i;
        }
    }

    ~Array() {
        delete[] elements;
    }

    T &operator[](size_t index);
};
#endif //ARRAY_LAB4_MODIFIC_ARRAY_H
