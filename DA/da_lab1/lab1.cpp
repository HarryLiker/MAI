#include <iostream>
#include "vector.hpp"
#include "pair.hpp"
#include "sorts.hpp"


int main()
{
    NVector::TVector<NPair::TPair<unsigned long long, unsigned long long>> vec;
    unsigned long long key;
    unsigned long long value;
    while(std::cin >> key >> value){
        vec.PushBack(NPair::TPair<unsigned long long, unsigned long long>(key, value));
    }
    
    NSort::RadixSort(vec, vec.Length());
    for (int i=0; i<vec.Length(); i++){
        std::cout << vec.Data[i].Key << "\t" << vec.Data[i].Value << "\n";
    }
    return 0;
}