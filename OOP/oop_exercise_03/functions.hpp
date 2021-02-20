#pragma once 

#include <string>
#include <vector>
#include "figure.hpp"
#include "rhombus.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"

Figure * enter_in_figure(std::string figure); // Input function of all figure parameters

Figure * figure_enter(); // Enter the figure name and input all figure parameters

float square_all_figures(std::vector<Figure*> vector); // Summ of squares of all figures

void figure_delete(std::vector<Figure*> &vector, int index); // Delete figure in vector
