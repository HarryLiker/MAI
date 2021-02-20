#pragma once
#include <iostream>
#include <vector>
#include <cstring>

struct TWord {
    std::string Word;
    unsigned long long StringId;
    unsigned long long WordId;
    TWord(std::string &word, unsigned long long string_id, unsigned long long word_id): Word(word), StringId(string_id), WordId(word_id) {}
    TWord(): Word(""), StringId(0), WordId(0) {}
};

void WordToLower(std::string &string);

std::vector<unsigned long long> ZFunction(const std::vector<TWord> & text);