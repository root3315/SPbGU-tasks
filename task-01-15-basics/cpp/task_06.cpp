// Задача 6. Вклад: ставка зависит от суммы (2 варианта)
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

    double amount;
    int months;

    cout << "Доход\n";

    bool inputOk = readValue("Сумма, руб. -> ", amount)
        && readValue("Срок вклада, мес. -> ", months);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (amount <= 0 || months <= 0) {
        cout << "Ошибка! Сумма и срок должны быть больше нуля\n";
    } else {
        // Сумма ровно 5000 руб. в условии не описана, принята ставка 13%
        int rate = amount < 5000 ? 10 : 13;
        double income = amount * rate / 100 * months / 12;

        cout << "----------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Сумма: " << amount << " руб.\n";
        cout << "Срок вклада: " << months << " мес.\n";
        cout << "Процент годовой: " << rate << "\n";
        cout << "Доход: " << income << " руб.\n";
        cout << "Сумма в конце срока вклада: " << amount + income << " руб.\n";
    }

    return 0;
}
