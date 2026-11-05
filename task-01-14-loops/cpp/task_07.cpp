// Задача 7. Цельсий и Фаренгейт
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

    double t1, t2, dt;

    bool inputOk = readValue("t1 –> ", t1)
        && readValue("t2 –> ", t2)
        && readValue("dt –> ", dt);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (dt <= 0) {
        cout << "Ошибка! Шаг должен быть больше нуля\n";
    } else if (t1 > t2) {
        cout << "Ошибка! Начальная температура больше конечной\n";
    } else if ((t2 - t1) / dt > 10000) {
        cout << "Ошибка! Слишком много строк в таблице\n";
    } else {
        // Температуру считаем через номер шага: так дробная ошибка не накапливается.
        // 1e-9 нужно, чтобы последний шаг не потерялся из-за такой же ошибки в делении
        int steps = static_cast<int>((t2 - t1) / dt + 1e-9);

        cout << "----------------\n";
        cout << "    C         F\n";
        cout << "----------------\n";
        cout << fixed << setprecision(2);
        for (int i = 0; i <= steps; i++) {
            // Округление убирает вывод "-0.00"
            double celsius = round((t1 + i * dt) * 1e9) / 1e9 + 0.0;
            double fahrenheit = 9.0 / 5 * celsius + 32;
            cout << setw(6) << celsius << setw(10) << fahrenheit << "\n";
        }
    }

    return 0;
}
