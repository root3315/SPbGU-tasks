// Задача 12. Високосный год
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

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    int year;

    cout << "Введите год, например 2000,\n";

    bool inputOk = readValue("и нажмите Enter -> ", year);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        // Високосный год делится на 4, но не на 100, либо делится на 400
        if (year <= 0) {
            cout << "Ошибка! Год должен быть больше нуля\n";
        } else if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            cout << year << " год – високосный\n";
        } else {
            cout << year << " год – не високосный\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    cin.get();

    return 0;
}
