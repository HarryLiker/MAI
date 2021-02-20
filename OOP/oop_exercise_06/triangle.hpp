#pragma once

#include <iostream>
#include <utility>
#include <cmath>

template <class T>
struct Triangle {
    using vertex_t = std::pair<T,T>;
    vertex_t Center;
    T Side;

    Triangle(): Center(), Side() {}
    Triangle(const vertex_t &center, const T &side): Center(center), Side(side) {}

    // Assignment operator
    Triangle& operator=(const Triangle& other) {
        Center = other.Center;
        Side = other.Side;
        return *this;
    }
};

// Operator of printing triangle coordinates
template <class T>
std::ostream& operator << (std::ostream& cout, const Triangle<T> &object) {
    double height = object.Side * sqrt(3) / 2.0;
    cout << "{";
    cout << "(" << object.Center.first + object.Side / 2.0 << ", " << object.Center.second - height / 3.0 << "), ";
    cout << "(" << object.Center.first << ", " << object.Center.second + 2 * height / 3.0 << "), ";
    cout << "(" << object.Center.first - object.Side / 2.0 << ", " << object.Center.second - height / 3.0 << ")";
    cout << "}";
    return cout;
}
