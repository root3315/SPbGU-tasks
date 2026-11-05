// Задача 8. Сумма первых n чисел
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

    int count;

    cout << "Сумма положительных чисел\n";

    bool inputOk = readValue("Введите количество суммируемых чисел -> ", count);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (count <= 0) {
        cout << "Ошибка! Количество должно быть больше нуля\n";
    } else if (count > 1000000) {
        cout << "Ошибка! Слишком большое количество\n";
    } else {
        long long total = 0;
        for (int number = 1; number <= count; number++) {
            total += number;
        }
        cout << "Сумма первых " << count << " положительных чисел равна " << total << "\n";
    }

    return 0;
}
