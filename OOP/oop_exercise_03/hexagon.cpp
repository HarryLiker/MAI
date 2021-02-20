#include <iostream>
#include <iomanip>
#include <cmath>
#include "hexagon.hpp"

#define PI 3.14159265

Hexagon::Hexagon(): Figure("hexagon"), Center_x(0), Center_y(0), SideLength(0) {}

Hexagon::Hexagon(float center_x, float center_y, float side): Figure("hexagon"), Center_x(center_x), Center_y(center_y), SideLength(side) {}

void Hexagon::GetSide() {
    std::cin >> SideLength;
    while(SideLength < 0) {
        std::cout << "Entered incorrect size!\n";
        std::cout << "Pleale, re-enter side size: ";
        std::cin >> SideLength;
    }
}

void Hexagon::GetCenter() {
    std::cin >> Center_x >> Center_y;
}

void Hexagon::PrintCenter() {
    std::cout << "(" << Center_x << ", " << Center_y << ")\n";
}

void Hexagon::PrintCoordinates() {
    for (int i = 0; i < 6; i++) {
        float x = Center_x + cos(60 * i * PI / 180) * SideLength;
        float y = Center_y + sin(60 * i * PI / 180) * SideLength;
        std::cout << "(x" << i + 1 << ", y" << i + 1 << ") = ";
        std::cout << "(" << round(x * 10000) / 10000 << ", " << round(y * 10000) / 10000 << ")\n";
    }
}

float Hexagon::Square() {
    return 3 * sqrt(3) * SideLength * SideLength / 2;
}

Hexagon::~Hexagon() {}