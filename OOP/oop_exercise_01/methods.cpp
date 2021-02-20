#include <iostream>
#include "Rational.h"

using namespace std;

void Rational::get_rational()
{
    char c;
    cin >> numerator >> c >> denominator;
    if(denominator < 0)
    {
        denominator = -denominator;
        numerator = -numerator;
    }
    if (denominator == 0)
    {
        denominator = 1;
    }
}

void Rational::print_rational()
{
    cout << numerator << "/" << denominator;
}

void Rational::add(Rational term1, Rational term2)
{
    Rational summ;
    summ.numerator = term1.numerator * term2.denominator + term2.numerator * term1.denominator;
    summ.denominator = term1.denominator*term2.denominator;
    summ = reduce(summ.numerator, summ.denominator);
    numerator = summ.numerator;
    denominator = summ.denominator;
}

void Rational::sub(Rational minuend, Rational subtrahend)
{
    Rational residual;
    residual.numerator = minuend.numerator * subtrahend.denominator - subtrahend.numerator * minuend.denominator;
    residual.denominator = minuend.denominator * subtrahend.denominator;
    residual = reduce(residual.numerator, residual.denominator);
    numerator = residual.numerator;
    denominator = residual.denominator;
}

void Rational::mul(Rational mult1, Rational mult2)
{
    Rational composition;
    composition.numerator = mult1.numerator * mult2.numerator;
    composition.denominator = mult1.denominator * mult2.denominator;
    composition = reduce(composition.numerator, composition.denominator);
    numerator = composition.numerator;
    denominator = composition.denominator;
}

void Rational::div(Rational dividend, Rational divisor)
{
    Rational quotient;
    quotient.numerator = dividend.numerator * divisor.denominator;
    quotient.denominator = dividend.denominator * divisor.numerator;
    quotient = reduce(quotient.numerator, quotient.denominator);
    numerator = quotient.numerator;
    denominator = quotient.denominator;
}