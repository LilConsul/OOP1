#include <iostream>
#include <string>
#include <windows.h>
#include "fx.h"

namespace std {
    void fx::check(void) {
        isX = fx_str.find('x') != string::npos;
        isNum = !fx_str.empty() && any_of(fx_str.begin(), fx_str.end(), ::isdigit);
        isDivX = fx_str.find('/') != string::npos;
        isXPow = fx_str.find("x^") != string::npos;
        isPowX = fx_str.find("^x") != string::npos;
        isCos = fx_str.find("cos") != string::npos;
        isSin = fx_str.find("sin") != string::npos;
    }

    string fx::p_Check(string output) {
        output.append(" + C;");
        if (fx_str.find('-') != string::npos) {
            if (output.find('-') != string::npos)
                return output.erase(output.find('-'), 1);
            return output.insert(0, "-");
        }
        return output;
    }

    string fx::num(void) {
        *x = stoi(fx_str);
        if (*x == 0)
            return "C;";
        else {
            fx_str.append("x");
            return p_Check(fx_str);
        }
    }

    string fx::divv(void) {
        for (int i = 0; fx_str[i] != '/'; i++)
            buffer.push_back(fx_str[i]);
        *x = stoi(buffer);
        if (*x == 1)
            return p_Check("ln|x|");
        else {
            buffer.append(" * ln|x|");
            return p_Check(buffer);
        }
    }

    string fx::xPow(void) {
        for (int i = fx_str.find_first_of('^') + 1; fx_str[i] != '\0'; i++)
            buffer.push_back(fx_str[i]);
        *n = stoi(buffer);
        if (*n == -1)
            return "Сталася помилка!\nСтепінь не може доорівнювати -1.";
        else {
            *n += 1;
            buffer = "";
            if (fx_str.find_first_of('x') - 1 != string::npos) {
                for (int i = 0; fx_str[i] != 'x'; i++)
                    buffer.push_back(fx_str[i]);
                *x = stoi(buffer);
            } else
                *x = 1;
            if (!(*x % *n)) {
                *x /= *n;
                buffer = to_string(*x);
                buffer.append("x ^ ");
                buffer.append(to_string(*n));
                return p_Check(buffer);
            } else {
                buffer = "(";
                buffer.append(to_string(*x));
                buffer.append("x ^ ");
                buffer.append(to_string(*n));
                buffer.append(") / ");
                buffer.append(to_string(*n));
                return p_Check(buffer);
            }
        }
    }

    string fx::powX(void) {
        if (fx_str.find("e^x") != string::npos)
            return p_Check(fx_str);
        else {
            for (int i = 0; fx_str[i] != '^'; i++)
                buffer.push_back(fx_str[i]);
            string buffer1 = buffer;
            buffer.append(" ^ x / ln ");
            buffer.append(buffer1);
            return p_Check(buffer);
        }
    }

    string fx::cosX(void) {
        if (fx_str.find("1/cos^2") != string::npos) {
            for (int i = fx_str.find_first_of('2') + 1; fx_str[i] != 'x'; i++)
                buffer.push_back(fx_str[i]);
            if (buffer.empty())
                return p_Check("tg (x)");
            *x = stoi(buffer);
            buffer = "(tg (";
            buffer.append(to_string(*x));
            buffer.append("x)) / ");
            return p_Check(buffer.append(to_string(*x)));
        }
        if (fx_str.find('^') != string::npos)
            return "Программа не можне знайти первісну від cos у степені!\nСпробуйте ще раз за табличними значеннями.";
        if (isNum && !isDivX) {
            for (int i = fx_str.find_first_of('s') + 1; fx_str[i] != 'x'; i++)
                buffer.push_back(fx_str[i]);
            *x = stoi(buffer);
        } else
            *x = 1;

        buffer = "Sin ";
        buffer.append(to_string(*x));
        buffer.append("x");
        return p_Check(buffer);
    }

    string fx::sinX(void) {
        if (fx_str.find("1/sin^2") != string::npos) {
            for (int i = fx_str.find_first_of('2') + 1; fx_str[i] != 'x'; i++)
                buffer.push_back(fx_str[i]);
            if (buffer.empty())
                return p_Check("-ctg (x)");
            *x = stoi(buffer);
            buffer = "(-ctg (";
            buffer.append(to_string(*x));
            buffer.append("x)) / ");
            return p_Check(buffer.append(to_string(*x)));
        }

        if (fx_str.find('^') != string::npos)
            return "Программа не можне знайти первісну від cos у степені!\nСпробуйте ще раз за табличними значеннями.";
        if (isNum && !isDivX) {
            for (int i = fx_str.find_first_of('n') + 1; fx_str[i] != 'x'; i++)
                buffer.push_back(fx_str[i]);
            *x = stoi(buffer);
        } else
            *x = 1;

        buffer = "- Cos ";
        buffer.append(to_string(*x));
        buffer.append("x");
        return p_Check(buffer);
    }

    fx::fx(void) : x(new int(0)), n(new int(0)), isX(0), isDivX(0), fx_str(""), buffer("") {}

    fx::~fx(void) {
        //cout << "Destructed!\n";
        delete x;
        delete n;
        x = nullptr;
        n = nullptr;
    }

    void fx::input_fx(void) {
        SetConsoleOutputCP(1251);
        cout << "Введіть функцію f(x): ";
        cin >> fx_str;
    }

    string fx::antiderr(void) {
        check();
        if (isCos)
            return cosX();
        if (isSin)
            return sinX();
        if (!isX && isNum)
            return num();
        if (isDivX && isX)
            return divv();
        if (isPowX)
            return powX();
        if (isXPow)
            return xPow();
        if (isX) {
            fx_str.append("^1");
            return xPow();
        } else
            return "Сталася помилка при підрахунку первісної!";
    }
}