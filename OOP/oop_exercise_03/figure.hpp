#pragma once

#include <string>

class Figure {
protected:
    std::string Name;

public:
    Figure(const char *figure);

    void PrintName();

    virtual void PrintCenter() = 0;

    virtual void PrintCoordinates() = 0;

    virtual float Square() = 0;

    virtual ~Figure();
};

