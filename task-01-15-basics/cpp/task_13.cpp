// Задача 13. Квадратное уравнение
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    double a, b, c;
    string line;

    cout << "Решение квадратного уравнения\n";
    cout << "Введите в одной строке коэффициенты и нажмите Enter -> ";
    getline(cin, line);

    istringstream stream(line);
    char extra;
    bool inputOk = (stream >> a >> b >> c) && !(stream >> extra);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (a == 0) {
        cout << "Ошибка! Коэффициент при второй степени неизвестного не должен быть равен нулю\n";
    } else {
        // Корни: x = (-b +- sqrt(D)) / (2a). Дискриминант сравниваем с допуском,
        // потому что дробные коэффициенты дают его с небольшой погрешностью
        double discriminant = b * b - 4 * a * c;
        cout << fixed << setprecision(3);
        if (discriminant < -1e-9) {
            cout << "Уравнение не имеет действительных корней\n";
        } else if (abs(discriminant) <= 1e-9) {
            double x = -b / (2 * a) + 0.0;  // + 0.0 убирает вывод "-0.000"
            cout << "Корень уравнения: x= " << x << "\n";
        } else {
            double root = sqrt(discriminant);
            double x1 = (-b + root) / (2 * a) + 0.0;
            double x2 = (-b - root) / (2 * a) + 0.0;
            cout << "Корни уравнения: x1= " << x1 << " x2= " << x2 << "\n";
        }
    }

    return 0;
}
