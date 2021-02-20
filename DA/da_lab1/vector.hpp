#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>

namespace NVector{
    template<class T>
    class TVector{
    private:
        size_t Capasity;
        size_t Size;
    public:
        T *Data;
        TVector(){
            Size = 0;
            Capasity = 1;
            Data = new T[Capasity];
        }
        TVector(size_t size){
            Size = size;
            Capasity = size;
            Data = new T[Capasity];
            for (int i = 0; i < Capasity; ++i){
                Data[i] = 0;
            }
        }
        int Length(){
            return Size;
        }
        void PushBack(T elem){
            Size++;
            if(Size <= Capasity){
                Data[Size-1] = elem;
            }
            else{
                Capasity *= 2;
                T *newdata = new T[Capasity];
                std::memcpy(newdata, Data, Capasity/2 * sizeof(T));
                delete [] Data;
                Data = newdata;
                Data[Size-1] = elem;
            }
        }
        // Очистка вектора из памяти
        void Clear(){
            delete[] Data;
            Capasity = 0;
            Size = 0;
            Data = nullptr;
        }
        ~TVector() {
            Clear();
        }
    };
} // namespace vector