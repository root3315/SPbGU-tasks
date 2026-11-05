// Задача 2. Заправка автомобиля
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

    int choice;
    double liters;

    cout << "Бензин\n";
    cout << "Марка бензина:\n";
    cout << "1 – 92\n";
    cout << "2 – 95\n";
    cout << "3 – 98\n";
    cout << "4 – DT\n";

    bool inputOk = readValue("Ваш выбор –> ", choice)
        && readValue("Литров –> ", liters);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        // В условии есть только итог для марки 95 (20.30 руб.), остальные цены приняты самостоятельно
        const double PRICES[] = {19.50, 20.30, 22.10, 18.70};

        if (choice < 1 || choice > 4) {
            cout << "Ошибка! Неверный выбор марки\n";
        } else if (liters <= 0) {
            cout << "Ошибка! Количество литров должно быть больше нуля\n";
        } else if (liters > 1000000) {
            cout << "Ошибка! Слишком большое количество\n";
        } else {
            double price = PRICES[choice - 1];
            // Округляем до копеек; 1e-6 защищает от ошибок дробных чисел (18.70 * 0.25 = 4.675)
            double total = floor(price * liters * 100 + 0.5 + 1e-6) / 100;

            cout << "-----------------------------\n";
            cout << fixed << setprecision(2) << "Цена за литр: " << price << " руб.\n";
            cout << defaultfloat << setprecision(15) << "Литров: " << liters << "\n";
            cout << fixed << setprecision(2) << "К оплате: " << total << " руб.\n";
        }
    }

    return 0;
}
