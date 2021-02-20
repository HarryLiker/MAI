#pragma once
#include <iostream>
#include "vector.hpp"
#include "pair.hpp"
namespace NSort {
    void CountingSort(NVector::TVector<NPair::TPair<unsigned long long, unsigned long long>> &vector, long long n, int pos) { 
        NVector::TVector<int> byte(256); // Для хранения количества вхождения байта каждого числа определённое количество раз
        int b; // Значение байта в числе
        int bits; // Количество бит, на которое нужно сделать сдвиг
        unsigned long long conc; // Число, с которым проиходит конкатенация
        NVector::TVector<NPair::TPair<unsigned long long, unsigned long long>> v;
        for (long long i = 0; i < n; i++){
            int b;
            // В зависимости от позиции 
            switch (pos)
            {
            case 1:
                conc = 0x00000000000000FF;
                bits = 0;
                break;
            case 2:
                conc = 0x000000000000FF00;
                bits = 8;
                break; 
            case 3:
                conc = 0x0000000000FF0000;
                bits = 16;
                break;
            case 4:
                conc = 0x00000000FF000000;
                bits = 24;
                break;
            case 5:
                conc = 0x000000FF00000000;
                bits = 32;
                break;
            case 6:
                conc = 0x0000FF0000000000;
                bits = 40;
                break;
            case 7:
                conc = 0x00FF000000000000;
                bits = 48;
                break;
            case 8:
                conc = 0xFF00000000000000;
                bits = 56;
                break;
            default:
                break;
            }
            b = ((vector.Data[i].Key & conc) >> bits);
            v.PushBack(vector.Data[i]);
            byte.Data[b] += 1;
        }
        for(int i = 1; i < 256; i++){
            byte.Data[i] = byte.Data[i] + byte.Data[i-1];
        }
        for (long long i = n-1; i>=0; i--){
            int k = ((vector.Data[i].Key & conc) >> bits);
            byte.Data[k] -=1;
            v.Data[byte.Data[k]] = vector.Data[i];
        }
        for (long long i = 0; i < n; i++){
            vector.Data[i] = v.Data[i];
        }
    }

    void RadixSort(NVector::TVector<NPair::TPair<unsigned long long, unsigned long long>> &vector, long long n){
        // Выполняет сортировку подсчётом для каждого байта чисел
        for(int pos = 1; pos < 9; pos++){
            CountingSort(vector, n, pos);
        }
    }
} // namespace NSort
