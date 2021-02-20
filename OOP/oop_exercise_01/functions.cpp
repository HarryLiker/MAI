#include <iostream>
#include "Rational.h"

using namespace std;

int abs(int a) // Функция нахождения модуля
{
    if(a < 0)
    {
        a = -a;
    }
    return(a);
}

int nod(int a, int b) // Функция нахождения НОД с помощью алгоритма Евклида
{
    a = abs(a);
    while(a!=0)
    {
        int t = a;
        a = b % a;
        b = t;
    }
    return b;
}

Rational reduce(int numerator, int denominator) // Функция сокращения дроби
{
    int den = nod(numerator, denominator);
    numerator /= den;
    denominator /= den;
    Rational red(numerator, denominator);
    return red;
}

void number_comparison(Rational a, Rational b) // Функция сравнения дробей
{
    if(a.numerator > 0 && b.numerator<=0)
    {
        a.print_rational();
        cout <<" > ";
        b.print_rational();
        cout << "\n"; 
    }
    else if (a.numerator <= 0 && b.numerator>0)
    {
        a.print_rational();
        cout <<" < ";
        b.print_rational();
        cout << "\n"; 
    }
    else if (a.numerator == 0 && b.numerator == 0)
    {
        a.print_rational();
        cout <<" = ";
        b.print_rational();
        cout << "\n"; 
    }
    else
    {
        int a_n = a.numerator;
        int a_d = a.denominator;
        int b_n = b.numerator;
        int b_d = b.denominator;
        int n = nod(a_d, b_d);
        int nok = (a_d / n) * b_d;
        a_n = a_n * (nok / a_d);
        b_n = b_n *(nok / b_d);
        if(a_n > b_n)
        {
            a.print_rational();
            cout << " > ";
            b.print_rational();
            cout << "\n"; 
        }
        else if(a_n < b_n)
        {
            a.print_rational();
            cout << " < ";
            b.print_rational();
            cout << "\n"; 
        }
        else
        {
            a.print_rational();
            cout << " = ";
            b.print_rational(); 
        }
    }  
}

void PrintResult(Rational a, Rational b, Rational res, char c) // Функция вывода результата после выполнения операции
{
    a.print_rational();
    cout <<" " << c << " ";
    b.print_rational(); 
    cout << " = ";
    res.print_rational();
    cout <<"\n";
}

int menu() // Меню действий
{
    while(true)
    {
        int variant;
        cout << "Choose an action:\n";
        cout << "1 - Perform operation\n";
        cout << "2 - Exit\n";
        cin >> variant;
        if(variant == 1)
        {
            cout << "Work with rational numbers(a,b - numbers):\n";
            cout << "a + b - Addition\n";
            cout << "a - b - Subtraction\n";
            cout << "a * b - Multiplication\n";
            cout << "a / b - Division\n";
            cout << "a | b - Comparing numbers\n";
            char c;
            Rational a,b;
            Rational result;
            a.get_rational();
            cin >> c;
            b.get_rational();
            switch (c)
            {
            case '+':
                {
                    result.add(a,b);
                    PrintResult(a,b,result,c);
                }
                break;
            case '-':
                {
                    result.sub(a,b);
                    PrintResult(a,b,result,c);
                }
                break;
            case '*':
                {
                    result.mul(a,b);
                    PrintResult(a,b,result,c);
                }
                break;
            case '/':
                {
                    result.div(a,b);
                    PrintResult(a,b,result,c);
                }
                break;
            case '|':
                {
                    number_comparison(a,b);
                }
                break;
            default:
                cout << "Expression entered incorrectly\n";
                break;
            }
            cout << "\n";
        }
        else if(variant == 2)
        {
            cout << "Program completed!\n";
            return 0;
        }
        else
        {
            cout << "The entered action does not exist\n";
        } 
    }
}