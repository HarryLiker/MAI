cmake_minimum_required (VERSION 3.2)
project (DA)
add_executable (da_lab4 main.cpp search.cpp)

set_target_properties(da_lab4 PROPERTIES CXX_STANDART 17 CXX_STANDART_REQUIRED ON)