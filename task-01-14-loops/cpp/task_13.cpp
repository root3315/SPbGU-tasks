// Задача 13. Среднее арифметическое пяти чисел
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

    const int COUNT = 5;
    double total = 0;
    bool inputOk = true;

    cout << "Среднее арифметическое последовательности дробных чисел.\n";
    cout << "После ввода каждого числа нажимайте Enter\n";
    for (int i = 0; i < COUNT && inputOk; i++) {
        double number = 0;
        inputOk = readValue("-> ", number);
        total += number;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        cout << fixed << setprecision(2);
        cout << "Среднее арифметическое введенной последовательности: " << total / COUNT << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
