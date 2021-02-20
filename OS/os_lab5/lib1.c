#include <stdio.h>
#include <math.h>

#include "lib.h"

// Функция расчёта значения числа Пи при заданной длине ряда x с помощью Ряда Лейбница
double Pi(int x) {
    double series_sum = 0;
    int operation = 0;
    for (int i = 1; i <= x; i++) {
        if (operation == 1) {
            series_sum -= 1.0 / (i * 2 - 1);
            operation = 0;
        } else {
            series_sum += 1.0 / (i * 2 - 1);
            operation = 1;
        }
    }
    return series_sum * 4;
}

// Функция расчёта значения числа e через (1 + 1/x)^x
double E(int x) {
    return pow(1 + 1.0 / x, x);
}