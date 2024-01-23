#include <iostream>
#include "SmartPointer.h"
#include "SmartMPointer.h"
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

    MySmartPointer<MyClass> mySmartPtr(new MyClass(42));

    std::cout<<mySmartPtr.pc_counter->iGet()<<std::endl;

    MySmartPointer<MyClass> mySmartPtrCopy = mySmartPtr;


    (*mySmartPtr).display();


    mySmartPtr->display();


    std::cout << "Reference Count: " << mySmartPtrCopy.pc_counter->iGet() << std::endl;


    (*mySmartPtrCopy).display();
    mySmartPtrCopy->display();


    std::cout << "Reference Count: " << mySmartPtrCopy.pc_counter->iGet() << std::endl;

    // Przykład
    SmartMPointer<int> uniqueIntPtr(new int(42));
    std::cout << " MyUniquePointer<int>: " << *uniqueIntPtr << "\n";
    SmartMPointer<int> un2(std::move(uniqueIntPtr));
    //copy doesn't work
//    SmartMPointer<int> un3(uniqueIntPtr);
    SmartMPointer<int> un4 = std::move(uniqueIntPtr);
    //copy doesn't work
//    SmartMPointer<int> un5 = uniqueIntPtr;

// dla tablicy int
    SmartMPointer<int[]> uniqueIntPtrArray(new int[5]{1, 2, 3, 4, 5});
    std::cout << "MyUniquePointer<int[]>: " << uniqueIntPtrArray[1] << "\n";

    return 0;
}
