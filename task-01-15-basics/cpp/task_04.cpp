// Задача 4. Фунты в килограммы
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

    double pounds;

    cout << "Пересчет веса из фунтов в килограммы\n";

    bool inputOk = readValue("Введите вес в фунтах и нажмите Enter -> ", pounds);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double GRAMS_IN_POUND = 405.9;

        if (pounds < 0) {
            cout << "Ошибка! Вес не может быть отрицательным\n";
        } else if (pounds > 1e12) {
            cout << "Ошибка! Слишком большое число\n";
        } else {
            // По образцу доли грамма отбрасываются; 1e-6 защищает от ошибок дробных чисел
            long long grams = static_cast<long long>(pounds * GRAMS_IN_POUND + 1e-6);
            cout << setprecision(15) << pounds << " фунт(а/ов) - это " << grams / 1000 << " кг " << grams % 1000 << " гр.\n";
        }
    }

    return 0;
}
