#pragma once

#include <iostream>

class Figure {
public:
    virtual void Print(std::ostream &output) = 0;
    virtual void Write(FILE *file) = 0;
    virtual ~Figure() = default;
};