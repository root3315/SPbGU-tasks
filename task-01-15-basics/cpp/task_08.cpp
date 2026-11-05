// Задача 8. Печать фотографий
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

    int photoFormat, quantity;

    cout << "Фотографии\n";

    bool inputOk = readValue("Формат (1 – 9х12; 2 – 10х15) -> ", photoFormat)
        && readValue("Количество, шт. -> ", quantity);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double PRICE_9X12 = 2.50;  // в условии цены нет, значение принято самостоятельно
        const double PRICE_10X15 = 3.20;

        if (photoFormat != 1 && photoFormat != 2) {
            cout << "Ошибка! Неверный формат\n";
        } else if (quantity <= 0) {
            cout << "Ошибка! Количество должно быть больше нуля\n";
        } else {
            double price = photoFormat == 1 ? PRICE_9X12 : PRICE_10X15;
            double total = price * quantity;
            // Скидка 5% предоставляется, если фотографий больше 10
            double discount = quantity > 10 ? total * 0.05 : 0;

            cout << "----------------------------\n";
            cout << fixed << setprecision(2);
            cout << "Цена: " << price << " руб.\n";
            cout << "Количество: " << quantity << " шт.\n";
            cout << "Сумма: " << total << " руб.\n";
            cout << "Скидка: " << discount << " руб.\n";
            cout << "К оплате: " << total - discount << " руб.\n";
        }
    }

    return 0;
}
