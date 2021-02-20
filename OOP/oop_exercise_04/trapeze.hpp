#pragma once
#include <iostream>

template<class T>
struct Trapeze {
    Trapeze() {}
    Trapeze(std::pair<T,T> center, T upper_side, T down_side, T height): Center(center), UpperSide(upper_side), DownSide(down_side), Height(height) {}
    std::pair<T,T> Center;
    T UpperSide;
    T DownSide;
    T Height;
};

template<class T>
void check_figure(Trapeze<T> figure) {
    if(figure.UpperSide <= 0 || figure.DownSide <= 0 || figure.Height <=0) {
        std::cout << "Trapeze parameters were entered incorrectly!\n";
        std::cout << "The program has been completed ahead of schedule!\n";
        exit(1);
    }
}

// Trapeze print
template <class T> 
void print(Trapeze<T>& figure) {
    check_figure(figure); 
    std::cout << "Trapeze: ";
    std::cout << "{(" << figure.Center.first + figure.DownSide / 2.0 << ", " << figure.Center.second - figure.Height / 2.0 <<"), ";
    std::cout << "(" << figure.Center.first + figure.UpperSide / 2.0 << ", " << figure.Center.second + figure.Height / 2.0 <<"), ";
    std::cout << "(" << figure.Center.first - figure.UpperSide / 2.0 << ", " << figure.Center.second + figure.Height / 2.0 <<"), ";
    std::cout << "(" << figure.Center.first - figure.DownSide / 2.0 << ", " << figure.Center.second - figure.Height / 2.0 <<")}\n";
    std::cout << std::endl;
}

// Square of trapeze 
template <class T>
double square(const Trapeze<T> &figure) {
    check_figure(figure); 
    return (figure.UpperSide + figure.DownSide) / 2.0 * figure.Height;
}
