#pragma once
#include "bottle.h"

int DataValidation(Bottle a, Bottle b); // Функция проверки правильности ввода данных
void VolumeComparison(Bottle a, Bottle b); // Функция сравнения объёмов двух бутылок
void FullnessComparison(Bottle a, Bottle b);  // Функция сравнения объёмов бутылок, которые заполнены водой
void Comparison(Bottle a, Bottle b); // Функция сравнения бутылок по статическому объему и объёму заполненности водой
Bottle Operation(Bottle a, Bottle b, char c); // Функция выполнения арифметических операций над бутылками
void Verification(Bottle a, Bottle b, char c); // Функция выполнения операторов сравнения бутылок
void PrintResult(Bottle a, Bottle b, char c, Bottle result); // Функция вывода результата выполнения арифметической операции
