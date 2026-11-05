// Задача 14. Обработка последовательности
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
    double total = 0, minimum = 0, maximum = 0;

    cout << "Обработка последовательности дробных чисел.\n";
    bool inputOk = readValue("Введите количество чисел последовательности -> ", count);

    if (inputOk && count > 0 && count <= 1000) {
        cout << "Вводите последовательность. После ввода каждого числа нажимайте Enter\n";
        for (int i = 0; i < count && inputOk; i++) {
            double number = 0;
            inputOk = readValue("-> ", number);

            total += number;
            // Первое число сразу считаем и минимумом, и максимумом
            if (i == 0 || number < minimum) {
                minimum = number;
            }
            if (i == 0 || number > maximum) {
                maximum = number;
            }
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (count <= 0) {
        cout << "Ошибка! Количество должно быть больше нуля\n";
    } else if (count > 1000) {
        cout << "Ошибка! Слишком большое количество\n";
    } else {
        cout << "Количество чисел: " << count << "\n";
        cout << fixed << setprecision(2) << "Среднее арифметическое: " << total / count << "\n";
        cout << defaultfloat << setprecision(15);
        cout << "Минимальное число: " << minimum << "\n";
        cout << "Максимальное число: " << maximum << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
