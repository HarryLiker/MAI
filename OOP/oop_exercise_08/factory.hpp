#pragma once

#include <memory>
#include "figure.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"
#include "trapeze.hpp"
// Class for creating graphical primitives
template <class T, class FIGURE>
class Factory;

template <class T>
class Factory<T, Rectangle<T>> {
public:
    static std::shared_ptr<Figure> CreateFigure() {
        std::pair<T,T> center;
        T length;
        T width;
        std::cout << "Enter the center coordinates: ";
        std::cin >> center.first >> center.second;
        std::cout << "Enter lenght and width: ";
        std::cin >> length >> width;
        Rectangle<T> *rectangle = new Rectangle<T>(center, length, width);
        return std::shared_ptr<Figure>(rectangle);
    }
};

template <class T>
class Factory<T, Rhombus<T>> {
public:
    static std::shared_ptr<Figure> CreateFigure() {
        std::pair<T,T> center;
        T side;
        float angle;
        std::cout << "Enter the center coordinates: ";
        std::cin >> center.first >> center.second;
        std::cout << "Enter the side: ";
        std::cin >> side;
        std::cout << "Enter an angle: ";
        std::cin >> angle;
        Rhombus<T> *rhombus = new Rhombus<T>(center, side, angle);
        return std::shared_ptr<Figure>(rhombus);
    }
};

template <class T>
class Factory<T, Trapeze<T>> {
public:
    static std::shared_ptr<Figure> CreateFigure() {
        std::pair<T,T> center;
        T down_side;
        T upper_side;
        T height;
        std::cout << "Enter the center coordinates: ";
        std::cin >> center.first >> center.second;
        std::cout << "Enter down side, upper side and height: ";
        std::cin >> down_side >> upper_side;
        std::cin >> height;
        Trapeze<T> *trapeze = new Trapeze<T>(center, down_side, upper_side, height);
        return std::shared_ptr<Figure>(trapeze);
    }
};
