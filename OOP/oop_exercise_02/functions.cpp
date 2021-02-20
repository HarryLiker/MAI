#include <iostream>
#include "bottle.h"
#include "functions.h"

using namespace std;

// Функция проверки правильности ввода данных
int DataValidation(Bottle a, Bottle b){
    if(a.Volume < 0 | a.FillingPer < 0 | a.FillingPer > 1 | b.Volume < 0 | b.FillingPer < 0 | b.FillingPer > 1){
        cout << "Invalid data was entered!\n\n";
        return 1;
    }
    return 0;
}

void VolumeComparison(Bottle a, Bottle b){  // Функция сравнения объёмов двух бутылок
    if(a.Volume > b.Volume){
        cout << "Volume1 > Volume2\n";
    }
    else if(a.Volume < b.Volume){
        cout << "Volume1 < Volume2\n";
    }
    else{
        cout << "Volume1 == Volume2\n";
    }
}

void FullnessComparison(Bottle a, Bottle b){  // Функция сравнения объёмов бутылок, которые заполнены водой
    if(a.Volume * a.FillingPer >  b.Volume * b.FillingPer){
        cout << "Fullness1 > Fullness2\n\n";
    }
    else if(a.Volume * a.FillingPer <  b.Volume * b.FillingPer){
        cout << "Fullness1 < Fullness2\n\n";
    }
    else{
        cout <<"Fullness1 == Fullness2\n\n";
    }
}

void Comparison(Bottle a, Bottle b){  // Функция сравнения бутылок по статическому объему и объёму заполненности водой
    VolumeComparison(a, b);
    FullnessComparison(a, b);
}

Bottle Operation(Bottle a, Bottle b, char c){  // Функция выполнения арифметических операций над бутылками
    Bottle res;
    if(c == '+'){
        res = a + b;
    }
    else if(c == '-'){
        res = a - b;
    }
    else{
        cout << "Wrong operation was selected!\n";
    }
    return res;
}

void Verification(Bottle a, Bottle b, char c){  // Функция выполнения операторов сравнения бутылок
    if(c == '>'){
        a > b;
    }
    else if(c == '<'){
        a < b;
    }
}

void PrintResult(Bottle a, Bottle b, char c, Bottle result){  // Функция вывода результата выполнения арифметической операции
    cout << "Solution (Volume, Filling Persent): ";
    a.PrintBottle();
    cout << " " << c << " ";
    b.PrintBottle();
    cout << " = ";
    result.PrintBottle();
    cout <<"\n\n";
}