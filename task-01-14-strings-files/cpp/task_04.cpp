// Задача 4. Результаты экзамена
#include <algorithm>
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

    const string GRADES[] = {"пятерок", "четверок", "троек", "двоек"};
    const int GRADE_COUNT = 4;
    int counts[GRADE_COUNT] = {};
    bool inputOk = true;

    cout << "Обработка результатов экзамена\n";
    cout << "Введите исходные данные:\n";
    for (int i = 0; i < GRADE_COUNT && inputOk; i++) {
        inputOk = readValue(GRADES[i] + "-> ", counts[i]);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        int total = 0, minimum = counts[0], maximum = counts[0];
        for (int count : counts) {
            total += count;
            minimum = min(minimum, count);
            maximum = max(maximum, count);
        }

        if (minimum < 0) {
            cout << "Ошибка! Количество не может быть отрицательным\n";
        } else if (maximum > 100000) {
            cout << "Ошибка! Слишком большое количество\n";
        } else if (total == 0) {
            cout << "Ошибка! Не введено ни одной оценки\n";
        } else {
            cout << "--------------------------\n";
            cout << "Результаты экзамена:\n";
            cout << fixed << setprecision(1);
            for (int i = 0; i < GRADE_COUNT; i++) {
                // Процент с точностью до десятых, половина округляется вверх (6.25 -> 6.3)
                double percent = floor(counts[i] * 1000.0 / total + 0.5) / 10;
                cout << GRADES[i] << " " << percent << "%\n";
            }
            cout << "--------------------------\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
