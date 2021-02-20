#include <iostream>
#include <cmath>
#include "figure.hpp"
#include "pentagon.hpp"
#include <iomanip>

#define PI 3.14159265

Pentagon::Pentagon(): Center_x(0), Center_y(0), SideLength(0), Figure("pentagon") {}

Pentagon::Pentagon(float center_x, float center_y, float side): Figure("pentagon"), Center_x(center_x), Center_y(center_y), SideLength(side) {}

void Pentagon::GetCenter() {
    std::cin >> Center_x >> Center_y;
}

void Pentagon::GetSide() {
    std::cin >> SideLength;
    while(SideLength < 0) {
        std::cout << "Entered incorrect size!\n";
        std::cout << "Pleale, re-enter side size: ";
        std::cin >> SideLength;
    }
}

void Pentagon::PrintCenter() {
    std::cout << "(" << Center_x << ", " << Center_y << ")\n";
}

void Pentagon::PrintCoordinates() {
    float radius = SideLength / sqrt(2 * (1 - cos(72 * PI / 180))); // Radius to get coorditates
    for(int i = 0; i < 5; i++) {
        float x = Center_x + cos(72 * i * PI / 180) * radius;
        float y = Center_y + sin(72 * i * PI / 180) * radius;
        std::cout << "(x" << i + 1 << ", y" << i + 1 << ") = ";
        std::cout << "(" << round(x * 10000) / 10000 << ", " << round(y * 10000) / 10000 << ")\n";
    }
}

float Pentagon::Square() {
    float radius = SideLength / sqrt(2 * (1 - cos(72 * PI / 180))); // Radius to get square
    return radius * radius * sin(72 * PI / 180) / 2 * 5;
}

Pentagon::~Pentagon() {}