// Задача 1. Печать фотографий
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

    int choice, quantity;

    cout << "Фото\n";
    cout << "Размер:\n";
    cout << "1 – 9х12\n";
    cout << "2 – 10х15\n";
    cout << "3 – 18х24\n";

    bool inputOk = readValue("Ваш выбор –> ", choice)
        && readValue("Количество –> ", quantity);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double PRICES[] = {3.50, 5.00, 10.00};  // цены из присланного образца

        if (choice < 1 || choice > 3) {
            cout << "Ошибка! Неверный выбор размера\n";
        } else if (quantity <= 0) {
            cout << "Ошибка! Количество должно быть больше нуля\n";
        } else if (quantity > 1000000) {
            cout << "Ошибка! Слишком большое количество\n";
        } else {
            double price = PRICES[choice - 1];
            double total = price * quantity;
            // Скидка 10% предоставляется, если фотографий больше 10
            double discount = quantity > 10 ? total * 0.10 : 0;

            cout << "-----------------------------\n";
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
