//
// Created by Maksym Selishchev on 09/01/2024.
//

#ifndef SMARTPOINTERS_SMARTMPOINTER_H
#define SMARTPOINTERS_SMARTMPOINTER_H
#include <iostream>
template <typename T>
class SmartMPointer {
public:

    // przyjmujący wskaźnik do zasobu
    explicit SmartMPointer(T* ptr) : pc_pointer(ptr) {}

    //  przenoszący
    SmartMPointer(SmartMPointer&& other) noexcept : pc_pointer(nullptr) {
        *this = std::move(other);
    }
    ~SmartMPointer()
    {
        delete pc_pointer;
    }

//przypis przenosz
    SmartMPointer& operator=(SmartMPointer&& other) noexcept {
        if (this != &other) {
            reset();
            pc_pointer = other.pc_pointer;
            other.pc_pointer = nullptr;
        }
        return *this;
    }

    T& operator*() { return(*pc_pointer); }

    T* operator->() { return(pc_pointer); }


    void reset() {
        delete pc_pointer;
        pc_pointer = nullptr;
    }

private:
    T* pc_pointer;
private:
    // Blokada kopiowania
    SmartMPointer(const SmartMPointer& other) {};
    SmartMPointer& operator=(const SmartMPointer& other)  {};
};



#endif //SMARTPOINTERS_SMARTMPOINTER_H
