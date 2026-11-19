// Задача 14. Среднее без min и max
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int NUMBER_LIMIT = 1000000;

// Показывает подсказку и читает числа, введённые в одной строке через пробел
template <typename T>
bool readValues(const string& prompt, vector<T>& values) {
    cout << prompt;

    string line;
    getline(cin, line);

    istringstream stream(line);
    string word;
    values.clear();
    while (stream >> word) {
        // Каждое слово должно быть числом целиком, без лишних символов
        istringstream wordStream(word);
        T value;
        char extra;
        if (!(wordStream >> value) || (wordStream >> extra)) {
            return false;
        }
        values.push_back(value);
    }
    return true;
}

// Проверяет, что все числа не больше NUMBER_LIMIT по модулю
template <typename T>
bool inLimit(const vector<T>& numbers) {
    for (T number : numbers) {
        if (abs(number) > NUMBER_LIMIT) {
            return false;
        }
    }
    return true;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    const size_t SIZE = 10;
    vector<int> numbers;

    cout << "Среднее арифметическое без учета min и max значений\n";
    bool inputOk = readValues("Введите массив (10 целых чисел в одной строке) -> ", numbers);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (numbers.size() != SIZE) {
        cout << "Ошибка! Нужно ввести 10 чисел\n";
    } else if (!inLimit(numbers)) {
        cout << "Ошибка! Числа должны быть от -1000000 до 1000000\n";
    } else {
        int minimum = numbers[0], maximum = numbers[0];
        long long total = 0;
        for (int number : numbers) {
            total += number;
            minimum = min(minimum, number);
            maximum = max(maximum, number);
        }
        // Исключаем по одному вхождению минимума и максимума
        double average = static_cast<double>(total - minimum - maximum) / (SIZE - 2);
        // Округляем до сотых, половина вверх: 10.375 -> 10.38
        average = floor(average * 100 + 0.5) / 100;

        cout << "------------------------------\n";
        cout << "Минимальный элемент: " << minimum << "\n";
        cout << "Максимальный элемент: " << maximum << "\n";
        cout << fixed << setprecision(2);
        cout << "Среднее арифм. без учета min и max значений: " << average << "\n";
    }

    return 0;
}
