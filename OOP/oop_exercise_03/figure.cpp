#include <iostream>
#include "figure.hpp"

Figure::Figure(const char *figure): Name(figure) {}

void Figure::PrintName() {
    std::cout << Name;
}

Figure::~Figure() {}
