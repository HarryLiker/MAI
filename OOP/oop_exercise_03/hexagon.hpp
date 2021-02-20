#pragma once

#include <iostream>
#include "figure.hpp"

class Hexagon: public Figure { // Сторона шестиугольника равна расстоянию от его центра до вершины
private:
    float Center_x;
    float Center_y;
    float SideLength;

public:
    Hexagon();
    Hexagon(float center_x, float center_y, float side);
    void GetSide();
    void GetCenter();
    void PrintCenter() override;
    void PrintCoordinates() override;
    float Square() override;
    ~Hexagon();
};