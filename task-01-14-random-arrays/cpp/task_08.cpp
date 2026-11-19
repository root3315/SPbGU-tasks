// Задача 8. Простое число
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

    const long long LIMIT = 1000000000000LL;
    long long number;

    cout << "Введите целое число и нажмите Enter\n";
    bool inputOk = readValue("> ", number);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number > LIMIT || number < -LIMIT) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        // Числа меньше 2 простыми не считаются; делители ищем до корня из числа
        bool isPrime = number >= 2;
        for (long long divisor = 2; isPrime && divisor * divisor <= number; divisor++) {
            if (number % divisor == 0) {
                isPrime = false;
            }
        }

        if (isPrime) {
            cout << number << " - простое число.\n";
        } else {
            cout << number << " - не простое число.\n";
        }
    }

    return 0;
}
