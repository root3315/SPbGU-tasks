// Задача 12. Ненулевые элементы
#include <cmath>
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

    const int SIZE = 5;
    double numbers[SIZE] = {};
    bool inputOk = true;

    cout << "Ввод массива дробных чисел\n";
    cout << "После ввода каждого числа нажмите Enter\n";
    for (int i = 0; i < SIZE && inputOk; i++) {
        inputOk = readValue("a[" + to_string(i + 1) + "] -> ", numbers[i]) && isfinite(numbers[i]);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        int nonzero = 0;
        for (int i = 0; i < SIZE; i++) {
            if (numbers[i] != 0) {
                nonzero++;
            }
        }
        cout << "------------------------\n";
        cout << "Ненулевых элементов: " << nonzero << "\n";
    }

    return 0;
}
