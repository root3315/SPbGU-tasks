// Задача 3. Стоимость яблок
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

    double price;

    cout << "Введите цену одного килограмма и нажмите Enter\n";
    cout << "(копейки от рублей отделяйте точкой)\n";

    bool inputOk = readValue("-> ", price) && isfinite(price);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (price <= 0) {
        cout << "Ошибка! Цена должна быть больше нуля\n";
    } else if (price > 1000000) {
        cout << "Ошибка! Слишком большая цена\n";
    } else {
        cout << "-------------------------\n";
        cout << "Вес, гр.  Стоимость, руб.\n";
        cout << "-------------------------\n";
        cout << fixed << setprecision(2);
        for (int weight = 100; weight <= 1000; weight += 100) {
            // Округляем до копеек; 1e-6 защищает от ошибок дробных чисел
            long long kopecks = static_cast<long long>(price * weight / 10 + 0.5 + 1e-6);
            cout << setw(8) << weight << setw(17) << kopecks / 100.0 << "\n";
        }
        cout << "-------------------------\n";
    }

    return 0;
}
