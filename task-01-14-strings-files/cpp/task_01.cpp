// Задача 1. Средняя температура за неделю
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

    const string DAYS[] = {"Понедельник", "Вторник", "Среда", "Четверг",
                           "Пятница", "Суббота", "Воскресенье"};
    const int DAY_COUNT = 7;
    double total = 0;
    bool inputOk = true, inRange = true;

    cout << "Введите температуру воздуха за неделю\n";
    for (int i = 0; i < DAY_COUNT && inputOk && inRange; i++) {
        double temperature = 0;
        inputOk = readValue(DAYS[i] + " -> ", temperature);
        inRange = temperature >= -100 && temperature <= 100;
        total += temperature;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (!inRange) {
        cout << "Ошибка! Температура должна быть от -100 до 100 град.\n";
    } else {
        cout << "------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Средняя температура за неделю: " << total / DAY_COUNT << " град.\n";
    }

    return 0;
}
