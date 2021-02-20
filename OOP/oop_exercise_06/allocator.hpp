#pragma once 

#include <iostream>
#include <vector>

template<class T, size_t BLOCK_SIZE>
class allocator {
private:
    T* Buffer;
    std::vector<T*> Vector;
public:
    using allocator_type = allocator;
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    allocator(): Vector(), Buffer(nullptr) {
        static_assert(BLOCK_SIZE > 0);
    }

    explicit allocator (const allocator<T, BLOCK_SIZE> &another_allocator): allocator() {
        Buffer = new T[BLOCK_SIZE];
        for (std::size_t i = 0; i < BLOCK_SIZE; ++i) {
            Buffer[i] = another_allocator.Buffer[i];
            Vector.push_back(&Buffer[i]);
        }
    }

    T *allocate(const std::size_t &size) {
        if (Buffer == nullptr) {
            Buffer = new T[BLOCK_SIZE];
            for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
                Vector.push_back(&Buffer[i]);
            }
        }
        if (Vector.size() < size) {
            throw("There is no free blocks to allocate memory! Please, remove an item from the collection to add a new item.");
        }
        else {
            T* pointer = Vector.back();
            for (std::size_t i = 0; i < size; ++i) {
                Vector.pop_back();
            }
            return pointer;
        }
    }

    template<class U>
    struct rebind {
        using other = allocator<U, BLOCK_SIZE>;
    };

    void deallocate(T* pointer, std::size_t) {
        ;
    }

    template<class OTHER_T, class... ARGS>
    void construct(OTHER_T* p, ARGS... arguments) {
        *p = OTHER_T(std::forward<ARGS>(arguments)...);
    }

    ~allocator() {
        delete [] Buffer;
    }
};