#include <iostream>
#include "fx.h"

using namespace std;

int main() {
    system("chcp 1251");
    cout << "�������� ������� �����"
         << "\n����� ��-11"
         << "\n�������� ������"
         << "\n������ �18(�)\n\n";
    char y = 'y';
    while (y == 'y') {
        fx func;
        func.input_fx();
        cout << "\n������� �� ���� �������: \n" << func.antiderr();

        cout << "\n\n������ �������������?(y/n)";
        cin >> y;
    }
    cout << "\n�������� ������ ���������!\n";
    return 0;
}