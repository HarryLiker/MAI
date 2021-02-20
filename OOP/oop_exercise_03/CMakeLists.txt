 
cmake_minimum_required (VERSION 3.2)
project (OOP)
add_executable (oop_exercise_03 main.cpp menu.cpp functions.cpp figure.cpp rhombus.cpp hexagon.cpp pentagon.cpp)

set_target_properties(oop_exercise_03 PROPERTIES CXX_STANDART 14 CXX_STANDART_REQUIRED ON)