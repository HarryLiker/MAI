#pragma once 

#include <iostream>
#include "figure.hpp"

class Rhombus: public Figure {
private:
    float Center_x;
    float Center_y;
    float SideLength;
    float Angle;

public:
    Rhombus();
    void GetCenter();
    void GetSide();
    void GetAngle();
    void PrintCenter() override;
    void PrintCoordinates() override;
    float Square() override;
    ~Rhombus();
};