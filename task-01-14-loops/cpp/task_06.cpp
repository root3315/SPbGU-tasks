// Задача 6. Платежи по кредиту
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

    bool inputOk = readValue("Сумма кредита (руб.) -> ", amount)
        && readValue("Срок (мес.) -> ", months)
        && readValue("Процентная ставка (годовых) -> ", rate);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (amount <= 0 || months <= 0 || rate < 0) {
        cout << "Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля\n";
    } else if (amount > 10000000) {
        cout << "Ошибка! Слишком большая сумма\n";
    } else if (rate > 100) {
        cout << "Ошибка! Слишком большая ставка\n";
    } else if (months > 1200) {
        cout << "Ошибка! Слишком большой срок\n";
    } else {
        double share = amount / months;  // равная доля долга, возвращаемая каждый месяц
        double totalInterest = 0;

        cout << "---------------------------------------\n";
        cout << "           Долг     Процент      Платеж\n";
        cout << "---------------------------------------\n";
        cout << fixed << setprecision(2);
        for (int month = 1; month <= months; month++) {
            // Проценты начисляются на остаток долга за один месяц
            double debt = amount - share * (month - 1);
            double interest = debt * rate / 100 / 12;
            totalInterest += interest;
            cout << setw(3) << month << setw(12) << debt
                 << setw(12) << interest << setw(12) << share + interest << "\n";
        }
        cout << "---------------------------------------\n";
        cout << "Всего процентов: " << totalInterest << "\n";
    }

    return 0;
}
