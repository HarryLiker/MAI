#include <iostream>
#include <string>
#include <vector>
#include "functions.hpp"
#include "figure.hpp"
#include "menu.hpp"

int menu() {
    std::vector<Figure*> figures;
    while(1) {
        int value;
        std::cout << "Menu:\n";
        std::cout << "1 - Enter the new figure\n";
        std::cout << "2 - Print all figures and their parameters\n";
        std::cout << "3 - Print total square of all figures\n";
        std::cout << "4 - Delete figure from array\n";
        std::cout << "5 - Exit the program\n";
        std::cin >> value;
        if (value == 1) {
            figures.push_back(figure_enter());
        }
        else if (value == 2) {
            for(int i = 0; i < figures.size(); i++) {
                figures[i]->PrintName();
                std::cout << "\n";
                std::cout << "Center (x, y): ";
                figures[i]->PrintCenter();
                figures[i]->PrintCoordinates();
                std::cout << "Square: " << figures[i]->Square() << "\n\n";
            }
        }
        else if (value == 3) {
            std::cout << "Total squre of all figures: " << square_all_figures(figures) << "\n\n";
        }
        else if (value == 4) {
            int index;
            std::cout << "Write an index of figure: ";
            std::cin >> index;
            while(index < 0 || index > figures.size() - 1) {
                std::cout << "The index is entered incorrectly\n";
                std::cout << "Please, write an index: ";
                std::cin >> index;
            }
            figure_delete(figures, index);
            std::cout << "The figure has been removed!\n";
        }
        else if (value == 5) {
            for (int i = 0; i < figures.size(); i++) {
                delete figures[i];
            }
            figures.clear();
            std::cout << "Program completed!";
            return 0;
        }
        else {
            std::cout << "The entered option does not exist\n";
            std::cout << "\n";
            continue;
        }
    }
    return 0; 
}