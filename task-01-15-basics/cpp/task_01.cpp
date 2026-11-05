// Задача 1. Доход по вкладу
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

    double amount, rate;
    int months;

    cout << "Вычисление дохода по вкладу\n";
    cout << "Введите исходные данные:\n";

    bool inputOk = readValue("Сумма вклада (руб.) -> ", amount)
        && readValue("Срок вклада (месяцев) -> ", months)
        && readValue("Процентная ставка (годовых) -> ", rate);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (amount <= 0 || months <= 0 || rate < 0) {
        cout << "Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля\n";
    } else {
        double income = amount * rate / 100 * months / 12;
        cout << "-------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Доход: " << income << " руб.\n";
        cout << "Сумма по окончании срока вклада: " << amount + income << " руб.\n";
    }

    return 0;
}
