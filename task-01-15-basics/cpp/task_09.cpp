// Задача 9. Ток в электрической цепи
#include <iomanip>
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

    double power, voltage;

    cout << "Ток в электрической цепи\n";

    bool inputOk = readValue("Мощность, Вт -> ", power)
        && readValue("Напряжение, В -> ", voltage);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (voltage == 0) {
        cout << "Ошибка! Напряжение не должно быть равно нулю\n";
    } else {
        double current = power / voltage + 0.0;  // + 0.0 убирает вывод "-0.00"
        cout << fixed << setprecision(2);
        cout << "Ток: " << current << " А\n";
    }

    return 0;
}
