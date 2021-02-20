cmake_minimum_required (VERSION 3.2)
project (MyStudy)
add_executable (oop_exercise_01 main.cpp functions.cpp methods.cpp)

set_target_properties(oop_exercise_01 PROPERTIES
CXX_STANDART 14
CXX_STANDART_REQUIRED ON
)