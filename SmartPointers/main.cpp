#include <iostream>
#include "SmartPointer.h"

class MyClass {
public:
    MyClass(int val) : data(val) {}

    void display() {
        std::cout << "Data: " << data << std::endl;
    }

private:
    int data;
};

int main() {
    // Creating a smart pointer and initializing it with a new instance of MyClass
    MySmartPointer<MyClass> mySmartPtr(new MyClass(42));

    // Creating another smart pointer and copying the first one
    MySmartPointer<MyClass> mySmartPtrCopy = mySmartPtr;

    // Displaying the data using the dereference operator
    (*mySmartPtr).display();

    // Accessing methods using the arrow operator
    mySmartPtr->display();

    // Displaying the reference count
    std::cout << "Reference Count: " << mySmartPtrCopy.pc_counter->iGet() << std::endl;

    // Modifying data through the smart pointer
    (*mySmartPtrCopy).display();
    mySmartPtrCopy->display();

    // Displaying the reference count after modifications
    std::cout << "Reference Count: " << mySmartPtrCopy.pc_counter->iGet() << std::endl;

    // Exiting the scope, the destructor will be called, and memory will be freed if necessary

    return 0;
}
