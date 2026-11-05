// Задача 5. Сопротивление цепи
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

    double r1, r2;
    int connection;

    cout << "Вычисление сопротивления электрической цепи\n";
    cout << "Введите исходные данные:\n";

    bool inputOk = readValue("Величина первого сопротивления (Ом) -> ", r1)
        && readValue("Величина второго сопротивления (Ом) -> ", r2)
        && readValue("Тип соединения (1-последовательное, 2-параллельное) -> ", connection);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        // Последовательно: R = R1 + R2, параллельно: R = R1 * R2 / (R1 + R2)
        cout << fixed << setprecision(2);
        if (r1 <= 0 || r2 <= 0) {
            cout << "Ошибка! Сопротивление должно быть больше нуля\n";
        } else if (connection == 1) {
            cout << "Сопротивление цепи: " << r1 + r2 << " Ом\n";
        } else if (connection == 2) {
            cout << "Сопротивление цепи: " << r1 * r2 / (r1 + r2) << " Ом\n";
        } else {
            cout << "Ошибка! Неверный тип соединения\n";
        }
    }

    return 0;
}
