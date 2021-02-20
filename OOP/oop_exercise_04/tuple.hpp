#pragma once
#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>

// Tuple print
template<class T, size_t index> 
typename std::enable_if<index == std::tuple_size<T>::value, void>::type print_tuple(T&) {}

template <class T, size_t index> 
typename std::enable_if<(index < std::tuple_size<T>::value), void>::type print_tuple(T& tuple) {
    auto figure = std::get<index>(tuple);
    print(figure);
    print_tuple<T,index+1>(tuple);
}

// The whole square of tuple
template <class T, size_t index = 0>
long double tuple_square(T& tuple) {
    if constexpr (index < std::tuple_size<T>::value) {
        return (long double)square(std::get<index>(tuple)) + tuple_square<T, index + 1>(tuple);
    }
    else {
        return 0;
    }
}