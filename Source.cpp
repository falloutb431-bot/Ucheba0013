#include <iostream>
#include <stdexcept>

template <typename T>
class SimpleVector {
private:
    T* data;
    size_t sz;      // текущее количество элементов
    size_t cap;     // выделенная ёмкость

    void grow() {
        size_t new_cap = (cap == 0) ? 1 : cap * 2;
        T* new_data = new T[new_cap];

        for (size_t i = 0; i < sz; ++i) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        cap = new_cap;
    }

public:
    SimpleVector() : data(nullptr), sz(0), cap(0) {}

    ~SimpleVector() {
        delete[] data;
    }

    // Запретим копирование, чтобы не усложнять управление памятью
    SimpleVector(const SimpleVector&) = delete;
    SimpleVector& operator=(const SimpleVector&) = delete;

    size_t size() const {
        return sz;
    }

    size_t capacity() const {
        return cap;
    }

    T& at(size_t index) {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= sz) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void push_back(const T& value) {
        if (sz == cap) {
            grow();
        }
        data[sz] = value;
        ++sz;
    }
};

int main() {
    SimpleVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    std::cout << "size: " << v.size() << "\n";
    std::cout << "capacity: " << v.capacity() << "\n";

    std::cout << "v.at(0): " << v.at(0) << "\n";
    std::cout << "v.at(1): " << v.at(1) << "\n";
    std::cout << "v.at(2): " << v.at(2) << "\n";

    v.at(1) = 99;
    std::cout << "After update, v.at(1): " << v.at(1) << "\n";

    return 0;
}