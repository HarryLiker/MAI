#include <iostream>
#include <iomanip>
#include <tuple>
#include "quadrate.hpp"
#include "rectangle.hpp"
#include "trapeze.hpp"
#include "tuple.hpp"

int main() {
    Quadrate<int> quadre1({100003, 3231}, 50);

    Quadrate<double> quadre2({3231.34, -9043.5}, 78);

    Rectangle<int> rectangle1({-32, 90}, 34, 5);

    Rectangle<double> rectangle2({-98.32, -1023.2}, 32, 10.2);

    Trapeze<int> trapeze1({1, 53}, 5, 6, 2);

    Trapeze<double> trapeze2({-23.1, -32.432}, 10.321, 11.232, 1.1);

    // Filling std::tuple by figures
    std::tuple<decltype(quadre1), decltype(quadre2), decltype(rectangle1), decltype(rectangle2), decltype(trapeze1), decltype(trapeze2)> 
    tuple {quadre1, quadre2, rectangle1, rectangle2, trapeze1, trapeze2};

    // Print coordinates of figures in tuple 
    print_tuple<decltype(tuple),0>(tuple);
    std::cout << "Total square of tuple: " << std::fixed << std::setprecision(4) << tuple_square<decltype(tuple),0>(tuple) << std::endl;
}