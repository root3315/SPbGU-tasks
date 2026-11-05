// Задача 11. Таблица степеней двойки
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

    cout << "Таблица степеней двойки\n\n";
    int power = 1;
    for (int exponent = 0; exponent <= 10; exponent++) {
        cout << setw(3) << exponent << setw(7) << power << "\n";
        power *= 2;
    }

    return 0;
}
