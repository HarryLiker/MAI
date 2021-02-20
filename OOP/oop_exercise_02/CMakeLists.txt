cmake_minimum_required (VERSION 3.2)
project (OOP)
add_executable (oop_exercise_02 main.cpp menu.cpp functions.cpp bottle.cpp)

set_target_properties(oop_exercise_02 PROPERTIES CXX_STANDART 14 CXX_STANDART_REQUIRED ON)