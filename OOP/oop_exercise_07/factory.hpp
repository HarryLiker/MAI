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

    static std::shared_ptr<Figure> Read(FILE *file) {
        std::pair<T,T> center;
        T length;
        T width;
        fread(&center.first, sizeof(T), 1, file);
        fread(&center.second, sizeof(T), 1, file);
        fread(&length, sizeof(T), 1, file);
        fread(&width, sizeof(T), 1, file);
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

    static std::shared_ptr<Figure> Read(FILE *file) {
        std::pair<T,T> center;
        T side;
        float angle;
        fread(&center.first, sizeof(T), 1, file);
        fread(&center.second, sizeof(T), 1, file);
        fread(&side, sizeof(T), 1, file);
        fread(&angle, sizeof(float), 1, file);
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

    static std::shared_ptr<Figure> Read(FILE *file) {
        std::pair<T,T> center;
        T down_side;
        T upper_side;
        T height;
        fread(&center.first, sizeof(T), 1, file);
        fread(&center.second, sizeof(T), 1, file);
        fread(&down_side, sizeof(T), 1, file);
        fread(&upper_side, sizeof(T), 1, file);
        fread(&height, sizeof(T), 1, file);
        Trapeze<T> *trapeze = new Trapeze<T>(center, down_side, upper_side, height);
        return std::shared_ptr<Figure>(trapeze);
    }
};