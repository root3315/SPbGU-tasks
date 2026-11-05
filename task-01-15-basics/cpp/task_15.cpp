// Задача 15. Скидка 3% или 5%
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

    double total;

    cout << "Вычисление стоимости покупки с учетом скидки\n";

    bool inputOk = readValue("Введите сумму покупки и нажмите Enter -> ", total);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (total < 0) {
        cout << "Ошибка! Сумма не может быть отрицательной\n";
    } else {
        // Сначала проверяем больший порог
        int discount;
        if (total > 1000) {
            discount = 5;
        } else if (total > 500) {
            discount = 3;
        } else {
            discount = 0;
        }

        if (discount > 0) {
            cout << "Вам предоставляется скидка " << discount << "%\n";
            total = total * (100 - discount) / 100;
        } else {
            cout << "Скидка не предоставляется\n";
        }

        cout << fixed << setprecision(2);
        cout << "Сумма с учетом скидки: " << total << " руб.\n";
    }

    return 0;
}
