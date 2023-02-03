#include <iostream>
#include "fx.h"
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Студента першого курсу11"
         << "\nГрупи ІР-11"
         << "\nШевченко Дениса"
         << "\nВаріант №18(В)\n\n";
    char y = 'y';
    while (y == 'y') {
        fx func;
        func.input_fx();
        cout << "\nПервісна від вашої функції: \n" << func.antiderr();

        cout << "\n\nБажаєте перезапустити?(y/n)";
        cin >> y;
    }
    cout << "\nПрограма успішно завершена!\n";
    return 0;
}