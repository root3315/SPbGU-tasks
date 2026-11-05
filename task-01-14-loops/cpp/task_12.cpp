// Задача 12. Факториал
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

    int number;

    cout << "Вычисление факториала\n";
    cout << "Введите число, факториал которого надо вычислить\n";

    bool inputOk = readValue("-> ", number);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number < 0) {
        cout << "Ошибка! Число не может быть отрицательным\n";
    } else if (number > 20) {  // 21! уже не помещается в long long
        cout << "Ошибка! Слишком большое число\n";
    } else {
        long long factorial = 1;
        for (int i = 2; i <= number; i++) {
            factorial *= i;
        }
        cout << "Факториал " << number << " равен " << factorial << "\n";
    }

    return 0;
}
