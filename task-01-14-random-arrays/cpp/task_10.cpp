// Задача 10. Число Пи
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

    double eps;

    bool inputOk = readValue("Задайте точность вычисления Пи -> ", eps) && isfinite(eps);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (eps <= 0 || eps >= 1) {
        cout << "Ошибка! Точность должна быть больше нуля и меньше единицы\n";
    } else if (eps < 1e-6) {
        cout << "Ошибка! Точность не может быть меньше 0.000001\n";
    } else {
        // Ряд 1 - 1/3 + 1/5 - ... сходится к Пи/4. Суммируем, пока
        // только что прибавленный член не станет меньше точности
        double total = 0;
        long long count = 0;
        int sign = 1;
        while (true) {
            count++;
            double term = 1.0 / (2 * count - 1);
            total += sign * term;
            sign = -sign;
            if (term < eps) {
                break;
            }
        }

        cout << fixed << setprecision(6);
        cout << "Значение числа Пи с точностью " << eps << " равно " << 4 * total << "\n";
        cout << "Просуммировано " << count << " членов ряда.\n";
    }

    return 0;
}
