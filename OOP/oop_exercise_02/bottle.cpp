#include <iostream>
#include "bottle.h"

using namespace std;

void Bottle::GetBottle(){  // Функция получения данных о бутылке
    cin >> Volume >> FillingPer;
}

void Bottle::PrintBottle(){  // Функция вывода данных о бутылке
    cout << Volume << " " << FillingPer;
}

Bottle Bottle::operator+ (Bottle capacity2){ // Оператор сложения двух бутылок
    Bottle t;
    t.Volume = Volume;
    t.FillingPer = FillingPer;
    t.FillingPer = (t.Volume * t.FillingPer + capacity2.Volume * capacity2.FillingPer) / Volume;
    if(t.FillingPer > 1){
        t.FillingPer = 1;
    }
    return t; 
}

Bottle Bottle::operator- (Bottle capacity2){  // Оператор вычитания двух бутылок
    Bottle t;
    t.Volume = Volume;
    t.FillingPer = FillingPer;
    t.FillingPer = (t.Volume * t.FillingPer - (capacity2.Volume * (1 - capacity2.FillingPer))) / Volume;
    if (t.FillingPer < 0){
        t.FillingPer = 0;
    }
    return t;
}

void Bottle::Bottle::operator>(Bottle capacity2){  // Оператор сравнения статического объёма бутылок
    if(Volume > capacity2.Volume){
        cout << "The statement is true!\n\n";
    }
    else{
        cout << "The statement is wrong!\n\n";
    }
}

void Bottle::Bottle::operator<(Bottle capacity2){  // Оператор сравнения статического объёма бутылок
    if(Volume < capacity2.Volume){
        cout << "The statement is true!\n\n";
    }
    else{
        cout << "The statement is wrong!\n\n";
    }
}

Bottle operator"" _bot(long double vol){  // Пользовательский литерал для работы с бутылками
    return Bottle(vol, 1); 
}

