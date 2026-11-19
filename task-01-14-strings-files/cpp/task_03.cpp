// Задача 3. Рост учеников
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

    vector<double> heights;
    double total = 0;
    bool inputOk = true, inRange = true;

    cout << "*** Анализ роста учеников ***\n";
    cout << "Введите рост (см) учеников\n";
    cout << "Для завершения введите 0 и нажмите Enter\n";
    while (true) {
        double height = 0;
        inputOk = readValue("-> ", height);
        if (!inputOk || height == 0) {
            break;
        }
        if (height < 0 || height > 300) {
            inRange = false;
            break;
        }
        heights.push_back(height);
        total += height;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (!inRange) {
        cout << "Ошибка! Рост должен быть больше 0 и не больше 300 см\n";
    } else if (heights.empty()) {
        cout << "Ошибка! Не введен рост ни одного ученика\n";
    } else {
        double count = heights.size();
        // Сравниваем без деления, чтобы на результат не влияла погрешность среднего
        int taller = 0;
        for (double height : heights) {
            if (height * count > total) {
                taller++;
            }
        }

        cout << "-----------------------------\n";
        cout << fixed << setprecision(1) << "Средний рост: " << total / count << " см\n";
        cout << "У " << taller << " человек рост превышает средний\n";
    }

    return 0;
}
