// Задача 3. Таблица квадратов
#include <iomanip>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    cout << "Таблица квадратов\n";
    cout << "--------------\n";
    cout << "Число Квадрат\n";
    cout << "--------------\n";
    for (int number = 1; number <= 10; number++) {
        cout << setw(3) << number << setw(9) << number * number << "\n";
    }
    cout << "--------------\n";

    return 0;
}
