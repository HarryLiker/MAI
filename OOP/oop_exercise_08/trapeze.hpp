#pragma once

#include <iostream>
#include "figure.hpp"

const unsigned int TRAPEZE_ID_TYPE = 2;

template <class T>
class Trapeze: public Figure {
private:
    std::pair<T,T> Center;
    T DownSide;
    T UpperSide;
    T Height;
public:
    Trapeze() {}
    Trapeze(std::pair<T,T> center, T down_side, T upper_side, T height): Center(center), DownSide(down_side), UpperSide(upper_side), Height(height) {}
    // Print trapeze parameters
    void Print() override {
        std::cout << *this;
    }
    // Write trapeze in file
    void Write(std::ofstream &file) override {
        file << *this;
    }

    template <class U>
    friend std::ostream &operator<< (std::ostream &out, const Trapeze<U> &trapeze) {
        out << "Trapeze: ";
        out << "{(" << trapeze.Center.first + trapeze.DownSide / 2.0 << ", " << trapeze.Center.second - trapeze.Height / 2.0 <<"), ";
        out << "(" << trapeze.Center.first + trapeze.UpperSide / 2.0 << ", " << trapeze.Center.second + trapeze.Height / 2.0 <<"), ";
        out << "(" << trapeze.Center.first - trapeze.UpperSide / 2.0 << ", " << trapeze.Center.second + trapeze.Height / 2.0 <<"), ";
        out << "(" << trapeze.Center.first - trapeze.DownSide / 2.0 << ", " << trapeze.Center.second - trapeze.Height / 2.0 <<")}\n";
        return out;
    }
};