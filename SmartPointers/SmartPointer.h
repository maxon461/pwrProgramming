//
// Created by Maksym Selishchev on 07/01/2024.
//

#ifndef SMARTPOINTERS_SMARTPOINTER_H
#define SMARTPOINTERS_SMARTPOINTER_H
#include "CRefCounter.h"

template <typename T>
class MySmartPointer{
public:
    MySmartPointer(T *pcPointer)
    {
        pc_pointer = pcPointer;
        pc_counter = new CRefCounter();
        pc_counter->iAdd();
    }
    MySmartPointer(const MySmartPointer &pcOther)
    {
        pc_pointer = pcOther.pc_pointer;
        pc_counter = pcOther.pc_counter;
        pc_counter->iAdd();
    }
    MySmartPointer(MySmartPointer &&other){
        pc_counter = other.pc_counter;
        pc_pointer = other.pc_pointer;
    }
    ~MySmartPointer()
    {
        if (pc_counter->iDec() == 0) {
            delete pc_pointer;
            delete pc_counter;
        }
    }
    T& operator*() { return(*pc_pointer); }
    T* operator->() { return(pc_pointer); }
    MySmartPointer& operator=(const MySmartPointer &pcOther){
        if (pcOther.pc_pointer == pc_pointer)
            return *this;

        if (pc_counter->iDec() == 0){
            delete pc_counter;
            delete pc_pointer;
        }

        pc_counter = pcOther.pc_counter;
        pc_pointer = pcOther.pc_pointer;

        pc_counter->iAdd();

        return *this;
    }
    CRefCounter *pc_counter;
private:
//    CRefCounter *pc_counter;
    T *pc_pointer;
};


#endif //SMARTPOINTERS_SMARTPOINTER_H
