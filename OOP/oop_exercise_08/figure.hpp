#pragma once

#include <iostream>
#include <fstream>

class Figure {
public:
    virtual void Print() = 0;
    virtual void Write(std::ofstream &file) = 0;
    virtual ~Figure() = default;
};