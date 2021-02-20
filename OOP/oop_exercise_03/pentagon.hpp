#pragma once 

#include <iostream>
#include "figure.hpp"

class Pentagon: public Figure {
private:
    float Center_x;
    float Center_y;
    float SideLength;

public:
    Pentagon();
    Pentagon(float center_x, float center_y, float side);
    void GetCenter();
    void GetSide();
    void PrintCenter() override;
    void PrintCoordinates() override;
    float Square() override;
    ~Pentagon();
};