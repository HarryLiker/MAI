#include <stdio.h>

// Функция расчёта значения числа Пи с помощью формулы Валлиса
double Pi(int x) {
    double answer = 1;
    for (int i = 1; i <= x; i++) {
        answer *= 1.0 * (2 * i) / (2 * i - 1) * (2 * i) / (2 * i + 1);
    }
    return 2 * answer;
}

// Функция расчёта значения числа e через сумму ряда, где элементы ряда равны: (1/(n!))
double E(int x) {
    double answer = 0;
    long double factorial_result = 1;
    
    for (int i = 0; i <= x; ++i) {
        if (i != 0) {
            factorial_result *= 1.0 / i;
        }
        answer += factorial_result;
    }
    
    return answer;
}