#include <iostream>
#include "menu.h"
#include "bottle.h"
#include "functions.h"

using namespace std;

int menu() // Функция вывода меню действий
{
    while(true){
        int variant;
        cout << "Choose an action:\n";
        cout << "1 - Perform operation\n";
        cout << "2 - Compare bottle volumes\n";
        cout << "3 - Exit\n";
        cin >> variant;
        if(variant == 1){
            cout << "Work with bottles (a, b - bottles):\n";
            cout << "a + b - Addition of filling volume\n";
            cout << "a - b - Substraction of filling volume\n";
            cout << "a | b - Comparing bottles\n";
            char c;
            Bottle a, b;
            Bottle result;
            a.GetBottle();
            cin >> c;
            b.GetBottle();
            if(DataValidation(a, b) == 1){
                continue;
            }
            if(c != '+' && c != '-'){
                if(c == '|'){
                    Comparison(a, b);
                }
                else{
                    cout << "Entered invalid operation\n\n";
                }
            }
            else{
                PrintResult(a, b, c, Operation(a, b, c));
            }
        }
        else if (variant == 2){
            cout << "Compare volumes of bottles\n";
            cout << "Comparison operations: >, <\n";
            char c;
            Bottle a, b;
            a.GetBottle();
            cin >> c;
            b.GetBottle();
            if(DataValidation(a, b) == 1){
                cout << "\n";
                continue;
            }
            Verification(a, b, c);
        }
        else if (variant == 3){
            cout << "Exit completed!";
            return 0;
        }
        else{
            cout << "Entered action does not exist\n\n";
        }
   }
   return 0;
}