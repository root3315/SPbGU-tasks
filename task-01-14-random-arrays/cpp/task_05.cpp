// Задача 5. Сумма и среднее до нуля
#include <cmath>
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

    int count = 0;
    double number = 0, total = 0;
    bool inputOk = true;

    cout << "Вычисление среднего арифметического последовательности положительных чисел.\n";
    cout << "Вводите после стрелки числа. Для завершения ввода введите ноль.\n";
    while (true) {
        inputOk = readValue("> ", number) && isfinite(number);
        if (!inputOk || number <= 0) {
            break;
        }
        count++;
        total += number;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number < 0) {
        cout << "Ошибка! Число должно быть положительным\n";
    } else if (count == 0) {
        cout << "Не введено ни одного числа\n";
    } else {
        cout << "Введено чисел: " << count << "\n";
        cout << defaultfloat << setprecision(15) << "Сумма чисел: " << total << "\n";
        cout << fixed << setprecision(2) << "Среднее арифметическое: " << total / count << "\n";
    }

    return 0;
}
