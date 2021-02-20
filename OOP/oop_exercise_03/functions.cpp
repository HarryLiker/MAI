#include <iostream>
#include "functions.hpp"

// Input function of all figure parameters
Figure *enter_in_figure(std::string figure) { 
    Figure *ptr_figure = nullptr;
    if (figure == "rhombus") {
        Rhombus *ptr_rhombus = new Rhombus();
        std::cout << "Write center coordinates: ";
        ptr_rhombus->GetCenter();
        std::cout << "Write side size: ";
        ptr_rhombus->GetSide();
        std::cout << "Write an angle: ";
        ptr_rhombus->GetAngle();
        ptr_figure = (Figure*)ptr_rhombus;
    }
    else if (figure == "pentagon") {
        Pentagon *ptr_pentagon = new Pentagon();
        std::cout << "Write center coordinates: ";
        ptr_pentagon->GetCenter();
        std::cout << "Write side size: ";
        ptr_pentagon->GetSide();
        ptr_figure = (Figure*)ptr_pentagon;
    }
    else if (figure == "hexagon") {
        Hexagon *ptr_hexagon = new Hexagon();
        std::cout << "Write center coordinates: ";
        ptr_hexagon->GetCenter();
        std::cout << "Write side size: ";
        ptr_hexagon->GetSide();
        ptr_figure = (Figure*)ptr_hexagon;
    }
    return ptr_figure;
}

// Enter the figure name and input all figure parameters
Figure *figure_enter() {
    std::string figure_name;
    std::cout << "Enter a name of figure (Possible names: rhombus, pentagon, hexagon): ";
    std::cin >> figure_name;
    while (figure_name != "rhombus" && figure_name != "pentagon" && figure_name != "hexagon") {
        std::cout << "Entered invalid figure name\n";
        std::cout << "Please, enter figure name: ";
        std::cin >> figure_name;
    }
    return enter_in_figure(figure_name);
}

// Summ of squares of all figures
float square_all_figures(std::vector<Figure*> vector) {
    float square = 0;
    for (int i = 0; i < vector.size(); i++) {
        square += vector[i]->Square();
    }
    return square;
}

// Delete figure in vector
void figure_delete(std::vector<Figure*> &vector, int index) {
    Figure *ptr = vector[index];
    vector.erase(vector.begin() + index);
    delete ptr;
}