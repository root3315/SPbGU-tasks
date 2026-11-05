// Задача 5. Скорость свободного падения
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

    const double G = 9.8;      // ускорение свободного падения, м/с2
    const double STEP = 0.5;   // шаг по времени, с

    cout << "-----------------------\n";
    cout << "Время, с Скорость, м/с\n";
    cout << "-----------------------\n";
    cout << fixed;
    // Время считаем через номер шага: так дробная ошибка не накапливается
    for (int i = 0; i < 7; i++) {
        double time = i * STEP;
        cout << setw(5) << setprecision(1) << time
             << setw(12) << setprecision(2) << G * time << "\n";
    }
    cout << "-----------------------\n";

    return 0;
}
