#ifndef RATIONAL_H
#define RATIONAL_H

using namespace std;

class Rational
{
    friend void number_comparison(Rational a, Rational b);
    private:
    int numerator; // Числитель
    int denominator; // Знаменатель
    
    public:
    Rational(): numerator(0), denominator(1) {}
    Rational(const int num_value): numerator(num_value), denominator(1) {}
    Rational(const int num_value, const int denom_value): numerator(num_value), denominator(denom_value)
    {
        if (denominator == 0)
        {
            cout << "Denominator value cannot be 0\n"; // Выводит сообщение, что значение знаменателя не может быть равным 0
            denominator = 1;
            cout << "The denominator has been changed to 1\n"; // Выводит сообщение о том, что значение знаменателя было изменено на 1
        }
        if (denom_value < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    void get_rational(); // Функция получения рационального числа
    void print_rational(); // Функция вывода рационального числа
    void add(Rational term1, Rational term2); // Функция сложения дробей
    void sub(Rational minuend, Rational subtrahend); // Функция вычитания дробей
    void mul(Rational mult1, Rational mult2); // Функция умножения дробей
    void div(Rational dividend, Rational divisor); // Функция деления дробей

    ~Rational() {}
};

int abs(int a);
int nod(int a, int b);
Rational reduce(int num, int den);
void PrintResult(Rational a, Rational b, Rational res, char c);
int menu();

#endif