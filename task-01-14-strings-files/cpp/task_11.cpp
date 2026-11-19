// Задача 11. Перевод в другую систему
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Показывает подсказку и читает значение: в строке не должно быть ничего лишнего
template <typename T>
bool readValue(const string& prompt, T& value) {
    cout << prompt;

    string line;
    getline(cin, line);

    istringstream stream(line);
    char extra;
    return (stream >> value) && !(stream >> extra);
}

// Переводит неотрицательное целое число в систему с основанием base делением
string toBase(long long number, int base) {
    if (number == 0) {
        return "0";
    }

    string digits;
    while (number > 0) {
        // Остатки от деления дают цифры с конца
        digits = to_string(number % base) + digits;
        number /= base;
    }
    return digits;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    long long number;
    int base;

    bool inputOk = readValue("Введите целое число -> ", number)
        && readValue("Введите основание системы счисления -> ", base);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (llabs(number) > 1000000000) {
        cout << "Ошибка! Число должно быть от -1000000000 до 1000000000\n";
    } else if (base < 2 || base > 10) {
        cout << "Ошибка! Основание должно быть от 2 до 10\n";
    } else {
        string converted = (number < 0 ? "-" : "") + toBase(llabs(number), base);
        cout << "Десятичному числу " << number << " соответствует число " << converted
             << " по основанию " << base << "\n";
    }

    return 0;
}
