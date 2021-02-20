#include <iostream>
#include "search.hpp"
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    std::vector<TWord> text;
    unsigned long long pattern_size = 0;
    unsigned long long text_size;
    unsigned long long line = 0;
    unsigned long long word_number = 1;
    std::string input;
    while (std::getline(std::cin, input)) {
        std::string word;
        std::stringstream temp_string(input);
        while (temp_string >> word) {
            WordToLower(word);
            TWord current_word(word, line, word_number);
            text.push_back(current_word);
            if (line != 0) {
                text_size++;
            } else {
                pattern_size++;
            }
            word_number++;
        }
        if (line == 0) {
            std::string delimiter = "$";
            TWord current_word(delimiter, line, word_number);
            text.push_back(current_word);
        }
        line++;
        word_number = 1;
    }
    auto start = high_resolution_clock::now();
    std::vector<unsigned long long> res = ZFunction(text);
    auto end = high_resolution_clock::now();
    /*
    for (unsigned long long i = pattern_size + 1; i < res.size(); i++) {
        if (res[i] == pattern_size) {
            std::cout << text[i].StringId << ", " << text[i].WordId << "\n";
        }
    }
    */
    auto duration = duration_cast<microseconds>(end-start);
    std::cout << "Time: " << duration.count() << " microseconds" << "\n";
}

