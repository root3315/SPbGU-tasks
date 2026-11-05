// Задача 10. Площадь кольца
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

    double ringRadius, holeRadius;

    cout << "Введите исходные данные:\n";

    bool inputOk = readValue("радиус кольца (см) -> ", ringRadius)
        && readValue("радиус отверстия (см) -> ", holeRadius);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double PI = 3.14159265358979;

        if (ringRadius <= 0 || holeRadius <= 0) {
            cout << "Ошибка! Радиус должен быть больше нуля\n";
        } else if (holeRadius > ringRadius) {
            cout << "Ошибка! Радиус отверстия больше радиуса кольца\n";
        } else if (holeRadius == ringRadius) {
            cout << "Ошибка! Радиус отверстия равен радиусу кольца\n";
        } else {
            // Площадь кольца: S = пи * (R^2 - r^2)
            double area = PI * (ringRadius * ringRadius - holeRadius * holeRadius);
            cout << fixed << setprecision(2);
            cout << "Площадь кольца: " << area << " кв.см\n";
        }
    }

    return 0;
}
