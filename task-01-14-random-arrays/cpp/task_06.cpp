// Задача 6. Максимальное число
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

    double number = 0;
    double maximum = 0;  // все числа положительные, поэтому любое из них больше нуля
    bool inputOk = true;

    cout << "Определение максимального числа из последовательности положительных чисел.\n";
    cout << "Вводите числа после стрелки. Для завершения ввода введите ноль.\n";
    while (true) {
        inputOk = readValue("> ", number) && isfinite(number);
        if (!inputOk || number <= 0) {
            break;
        }
        if (number > maximum) {
            maximum = number;
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number < 0) {
        cout << "Ошибка! Число должно быть положительным\n";
    } else if (maximum == 0) {
        cout << "Не введено ни одного числа\n";
    } else {
        cout << defaultfloat << setprecision(15) << "Максимальное число: " << maximum << "\n";
    }

    return 0;
}
