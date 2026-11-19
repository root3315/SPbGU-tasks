// Задача 11. Массив из семи чисел
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

    const int SIZE = 7;
    const long long LIMIT = 1000000000;
    long long numbers[SIZE] = {};
    bool inputOk = true;

    cout << "Ввод массива целых чисел\n";
    cout << "После ввода каждого числа нажмите Enter\n";
    for (int i = 0; i < SIZE && inputOk; i++) {
        inputOk = readValue("a[" + to_string(i) + "] -> ", numbers[i]);
    }

    bool inRange = true;
    long long total = 0;
    for (int i = 0; i < SIZE; i++) {
        if (numbers[i] > LIMIT || numbers[i] < -LIMIT) {
            inRange = false;
        }
        total += numbers[i];
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (!inRange) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        cout << "Массив:";
        for (int i = 0; i < SIZE; i++) {
            cout << " " << numbers[i];
        }
        cout << "\n";
        cout << fixed << setprecision(2);
        cout << "Среднее арифметическое: " << static_cast<double>(total) / SIZE << "\n";
    }

    return 0;
}
