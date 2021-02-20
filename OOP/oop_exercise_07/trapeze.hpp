#pragma once

#include <iostream>
#include "figure.hpp"

const unsigned int TRAPEZE_ID_TYPE = 2;

template <class T>
class Trapeze: public Figure {
private:
    std::pair<T,T> Center;
    T UpperSide;
    T DownSide;
    T Height;
public:
    Trapeze() {}
    Trapeze(std::pair<T,T> center, T down_side, T upper_side, T height): Center(center), DownSide(down_side), UpperSide(upper_side), Height(height) {}
    // Print trapeze parameters
    void Print(std::ostream &out) {
        out << *this;
    }
    // Write trapeze in file
    void Write(FILE *out) override {
        fwrite(&TRAPEZE_ID_TYPE, sizeof(unsigned int), 1, out);
        fwrite(&Center.first, sizeof(T), 1, out);
        fwrite(&Center.second, sizeof(T), 1, out);
        fwrite(&DownSide, sizeof(T), 1, out);
        fwrite(&UpperSide, sizeof(T), 1, out);
        fwrite(&Height, sizeof(T), 1, out);
    }

    template <class U>
    friend std::ostream &operator<< (std::ostream &out, const Trapeze<U> &trapeze) {
        out << "Trapeze: ";
        out << "{(" << trapeze.Center.first + trapeze.DownSide / 2.0 << ", " << trapeze.Center.second - trapeze.Height / 2.0 <<"), ";
        out << "(" << trapeze.Center.first + trapeze.UpperSide / 2.0 << ", " << trapeze.Center.second + trapeze.Height / 2.0 <<"), ";
        out << "(" << trapeze.Center.first - trapeze.UpperSide / 2.0 << ", " << trapeze.Center.second + trapeze.Height / 2.0 <<"), ";
        out << "(" << trapeze.Center.first - trapeze.DownSide / 2.0 << ", " << trapeze.Center.second - trapeze.Height / 2.0 <<")}";
        return out;
    }
};