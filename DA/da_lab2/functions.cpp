#include "functions.hpp"

bool Strings_compare(const char *string1, const char *string2) {
    int i = 0;
    while(string1[i] == string2[i]) {
        i++;
    }
    if(string1[i] < string2[i]) {
        return 0;
    }
    else {
        return 1;
    }
}

int Equal_strings(const char *string1, const char *string2) {
    int i = 0;
    while ((string1[i] == string2[i]) && (string1[i] != '\0') && i != 257) {
        i++;
    }
    if (string1[i] == string2[i]) {
        return 0;
    }
    else if (string1[i] < string2[i]) {
        return -1;
    }
    else {
        return 1;
    }
}


void Str_copy(const char *line, char *string) { 
    
    int i = 0;
    while (i < 256 && line[i] != '\0') {
        if ('A' <= line[i] && line[i] <= 'Z') {
            string[i] = line[i] - 'A' + 'a';
        }
        else {
            string[i] = line[i];
        }
        i++;
    }
    string[i] = '\0';
    while(i != 257) {
        string[i] = 0;
        i++;
    }
}

