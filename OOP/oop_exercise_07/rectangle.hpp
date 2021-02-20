#pragma once
#include <iostream>
#include "figure.hpp"

const unsigned int RECTANGLE_ID_TYPE = 1;

template <class T>
class Rectangle: public Figure {
private:
    std::pair<T,T> Center;
    T Length;
    T Width;
public:
    Rectangle() {}
    Rectangle(std::pair<T,T> center, T length, T width): Center(center), Length(length), Width(width) {}
    // Print rectangle’s parameters
    void Print(std::ostream &out) {
        out << *this;
    }
    // Write the rectangle in file
    void Write(FILE *file) {
        fwrite(&RECTANGLE_ID_TYPE, sizeof(unsigned int), 1, file);
        fwrite(&Center.first, sizeof(T), 1, file);
        fwrite(&Center.second, sizeof(T), 1, file);
        fwrite(&Length, sizeof(T), 1, file);
        fwrite(&Width, sizeof(T), 1, file);
    }

    template <class U>
    friend std::ostream &operator << (std::ostream &out, const Rectangle<U> &rectangle) {
        out << "Rectangle: ";
        out << "{(" << rectangle.Center.first + rectangle.Length / 2.0 << ", " << rectangle.Center.second + rectangle.Width / 2.0 <<"), ";
        out << "(" << rectangle.Center.first - rectangle.Length / 2.0 << ", " << rectangle.Center.second + rectangle.Width / 2.0 <<"), ";
        out << "(" << rectangle.Center.first - rectangle.Length / 2.0 << ", " << rectangle.Center.second - rectangle.Width / 2.0 <<"), ";
        out << "(" << rectangle.Center.first + rectangle.Length / 2.0 << ", " << rectangle.Center.second - rectangle.Width / 2.0 <<")}";
        return out;
    }
}; 