// Задача 2. Минуты в часы и минуты
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

    int interval;

    bool inputOk = readValue("Введите временной интервал (в минутах) -> ", interval);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (interval < 0) {
        cout << "Ошибка! Интервал не может быть отрицательным\n";
    } else {
        cout << interval << " минут - это " << interval / 60 << " ч. " << interval % 60 << " мин.\n";
    }

    return 0;
}
