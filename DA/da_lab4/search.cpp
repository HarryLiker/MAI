#include "search.hpp"

#include <algorithm>
#include <iostream>

void WordToLower(std::string &string) {
    for (size_t i = 0; i < string.size(); i++) {
        string[i] = std::tolower(string[i]);
    }
}

bool operator == (const TWord &left_value, const TWord &right_value) {
    if (left_value.Word == right_value.Word) {
        return true;
    }
    return false;
}

bool operator != (const TWord &left_value, const TWord &right_value) {
    return !(left_value == right_value);
}

std::vector<unsigned long long> ZFunction(const std::vector<TWord> &text) {
    unsigned long long size = text.size();
    unsigned long long left = 0;
    unsigned long long right = 0;
    std::vector<unsigned long long> z_function(size);
    for (unsigned long long i = 1; i < size; ++i) {
        if (i <= right) {
            z_function[i] = std::min(z_function[i-left], right - i + 1);
        }
        while ((z_function[i] + i < size) && (text[z_function[i]].Word == text[z_function[i] + i].Word)) {
            ++z_function[i];
        }
        if (i + z_function[i] - 1 > right) {
            left = i;
            right = z_function[i] + i - 1;
        }
    }
    return z_function;
}
