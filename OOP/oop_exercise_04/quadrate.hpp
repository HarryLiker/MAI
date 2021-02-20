#pragma once
#include <iostream>

template <class T>
struct Quadrate {
    Quadrate() {}
    Quadrate(std::pair<T,T> center, T side): Center(center), Side(side) {}
    std::pair<T,T> Center;
    T Side;
};

template<class T>
void check_figure(Quadrate<T> figure) {
    if(figure.Side <= 0) {
        std::cout << "Quadrate parameters were entered incorrectly!\n";
        std::cout << "The program has been completed ahead of schedule!\n";
        exit(1);
    }
}

// Quadrate print
template <class T> 
void print(Quadrate<T>& figure) {
    check_figure(figure); 
    std::cout << "Quadrate: ";
    std::cout << "{(" << figure.Center.first + figure.Side / 2.0 << ", " << figure.Center.second + figure.Side / 2.0 << "), ";
    std::cout << "(" << figure.Center.first - figure.Side / 2.0 << ", " << figure.Center.second + figure.Side / 2.0 << "), ";
    std::cout << "(" << figure.Center.first - figure.Side / 2.0 << ", " << figure.Center.second - figure.Side / 2.0 << "), ";
    std::cout << "(" << figure.Center.first + figure.Side / 2.0 << ", " << figure.Center.second - figure.Side / 2.0 << ")}\n";
    std::cout << std::endl;
}

// Square of quadrate
template <class T>
double square(const Quadrate<T> &figure) {
    check_figure(figure); 
    return (figure.Side * figure.Side);
}