// Задача 1. Десять случайных чисел
#include <iomanip>
#include <iostream>
#include <random>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Генератор случайных чисел
mt19937 generator(random_device{}());

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    const int COUNT = 10;
    uniform_int_distribution<int> distribution(1, 10);
    int total = 0;

    cout << "Случайные числа\n";
    for (int i = 0; i < COUNT; i++) {
        int number = distribution(generator);
        cout << number << "\n";
        total += number;
    }
    cout << fixed << setprecision(2) << "Сред. арифм.: " << static_cast<double>(total) / COUNT << "\n";

    return 0;
}
