#include <iostream>

template <typename T>
class MyUniquePointer {
private:
    T* resource;

public:
    // przyjmujący wskaźnik do zasobu
    explicit MyUniquePointer(T* ptr = nullptr) : resource(ptr) {}

    //  przenoszący
    MyUniquePointer(MyUniquePointer&& other) noexcept : resource(nullptr) {
        *this = std::move(other);
    }

    // Przypisanie przenoszące
    MyUniquePointer& operator=(MyUniquePointer&& other) noexcept {
        if (this != &other) {
            reset();  // Zwolnienie aktualnego zasobu, jeśli istnieje
            resource = other.resource;
            other.resource = nullptr;  // Inny obiekt nie powinien zarządzać zwolnionym zasobem
        }
        return *this;
    }

    // Operator wyłuskania (operator*)
    T& operator*() const {
        if (resource) {
            return *resource;
        }
        throw std::runtime_error("Dereferencing a null pointer");
    }

    // Operator dostępu do składowej przez wskaźnik (operator->)
    T* operator->() const {
        if (resource) {
            return resource;
        }
        throw std::runtime_error("Accessing a null pointer");
    }

    // Funkcja resetująca wskaźnik
    void reset() {
        delete resource;
        resource = nullptr;
    }

    // Destruktor
    ~MyUniquePointer() {
        reset();
    }

private:
    // Blokada kopiowania
    MyUniquePointer(const MyUniquePointer& other) = delete;
    MyUniquePointer& operator=(const MyUniquePointer& other) = delete;
};

// Specjalizacja dla tablic
template <typename T>
class MyUniquePointer<T[]> {
private:
    T* resource;

public:
    explicit MyUniquePointer(T* ptr = nullptr) : resource(ptr) {}

    MyUniquePointer(MyUniquePointer&& other) noexcept : resource(nullptr) {
        *this = std::move(other);
    }

    MyUniquePointer& operator=(MyUniquePointer&& other) noexcept {
        if (this != &other) {
            reset();
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }

    T& operator[](size_t index) const {
        if (resource) {
            return resource[index];
        }
        throw std::runtime_error("Accessing elements of a null pointer");
    }

    void reset() {
        delete[] resource;
        resource = nullptr;
    }

    ~MyUniquePointer() {
        reset();
    }

private:
    MyUniquePointer(const MyUniquePointer& other) = delete;
    MyUniquePointer& operator=(const MyUniquePointer& other) = delete;
};

int main() {
    // Przykład użycia MyUniquePointer dla int
    MyUniquePointer<int> uniqueIntPtr(new int(42));
    std::cout << "Dereferencing MyUniquePointer<int>: " << *uniqueIntPtr << "\n";

    // Przykład użycia MyUniquePointer dla tablicy int
    MyUniquePointer<int[]> uniqueIntPtrArray(new int[5]{1, 2, 3, 4, 5});
    std::cout << "Accessing element of MyUniquePointer<int[]>: " << uniqueIntPtrArray[2] << "\n";

    return 0;
}
