#pragma once

#include <iostream>
#include <cmath>
#include "figure.hpp"

#define PI 3.14159265

const unsigned int RHOMBUS_ID_TYPE = 3;

template <class T>
class Rhombus: public Figure {
private:
    std::pair<T,T> Center;
    T Side;
    float Angle;
public:
    Rhombus(): Center(), Side(), Angle(90) {}
    Rhombus(std::pair<T,T> center, T side, float angle): Center(center), Side(side), Angle(angle) {}

    void Print() override {
        std::cout << *this;
    }

    void Write(std::ofstream &file) override {
        file << *this;
    }

    template <class U>
    friend std::ostream &operator << (std::ostream &out, const Rhombus<U> &rhombus) {
        float angle = rhombus.Angle / 2;
        float radius_x = cos(angle * PI / 180) * rhombus.Side;
        float radius_y = sin(angle * PI / 180) * rhombus.Side;

        out << "Rhombus: ";
        out << "{";
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) {
                out << "(" << rhombus.Center.first + radius_x << ", " << 0 << "), ";
                radius_x *= -1;
            }
            else {
                out << "(" << 0 << ", " << rhombus.Center.second + radius_y << ")";
                if (i != 3) {
                    out << ", ";
                }
                radius_y *= -1;
            }
        }
        out << "}\n";
        return out;
    }
};