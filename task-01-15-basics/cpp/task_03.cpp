// Задача 3. Денежный формат
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

    double value;

    cout << "Преобразование числа в денежный формат\n";

    bool inputOk = readValue("Введите дробное число -> ", value);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (value < 0) {
        cout << "Ошибка! Число не может быть отрицательным\n";
    } else if (value > 1e12) {
        cout << "Ошибка! Слишком большое число\n";
    } else {
        // Считаем в копейках: + 0.5 защищает от ошибок дробных чисел (1.15 * 100 = 114.99...)
        long long total = static_cast<long long>(value * 100 + 0.5);
        cout << setprecision(15) << value << " руб. - это " << total / 100 << " руб. "
             << setw(2) << setfill('0') << total % 100 << setfill(' ') << " коп.\n";
    }

    return 0;
}
