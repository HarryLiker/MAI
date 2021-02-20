#pragma once

#include <iostream>
using namespace std;


class Bottle{
    private:
    long double Volume; // Объём 
    long double FillingPer; // Процент наполнения
    
    public:
    Bottle(): Volume(0), FillingPer(0) {}
    Bottle(long double v): Volume(v), FillingPer(0) {}
    Bottle(long double v, long double f): Volume(v), FillingPer(f) {}
    void GetBottle(); // Функция получения данных о бутылке
    void PrintBottle(); // Функция вывода данных о бутылке
    friend int DataValidation(Bottle a, Bottle b); // Функция проверки правильности ввода данных
    friend void VolumeComparison(Bottle a, Bottle b); // Функция сравнения объёмов двух бутылок
    friend void FullnessComparison(Bottle a, Bottle b); // Функция сравнения объёмов бутылок, которые заполнены водой
    Bottle operator+ (Bottle capacity2); // Оператор сложения двух бутылок
    Bottle operator- (Bottle capacity2); // Оператор вычитания двух бытолок
    void operator> (Bottle capacity2); // Оператор сравнения статического объёма бутылок
    void operator< (Bottle capacity2); // Оператор сравнения статического объёма бутылок
    ~Bottle(){}
};

Bottle operator"" _bot(long double vol); // Пользовательский литерал для работы с бутылками