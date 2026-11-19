// Задача 2. Слияние упорядоченных массивов
#include <cstdlib>
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

// Проверяет, что числа идут по неубыванию
bool isSorted(const vector<int>& numbers) {
    for (size_t i = 1; i < numbers.size(); i++) {
        if (numbers[i - 1] > numbers[i]) {
            return false;
        }
    }
    return true;
}

// Сливает два упорядоченных массива в один: каждый раз берём меньший из текущих элементов
vector<int> mergeSorted(const vector<int>& first, const vector<int>& second) {
    vector<int> result;
    size_t i = 0, j = 0;
    while (i < first.size() && j < second.size()) {
        if (first[i] <= second[j]) {
            result.push_back(first[i++]);
        } else {
            result.push_back(second[j++]);
        }
    }
    // Один из массивов закончился: дописываем остаток другого
    while (i < first.size()) {
        result.push_back(first[i++]);
    }
    while (j < second.size()) {
        result.push_back(second[j++]);
    }
    return result;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    const size_t SIZE = 5;
    vector<int> first, second;

    cout << "Объединение двух массивов, упорядоченных по возрастанию\n";
    cout << "Введите в одной строке элементы первого массива,\n";
    bool inputOk = readValues("(5 целых чисел) -> ", first);
    if (inputOk) {
        cout << "Введите в одной строке элементы второго массива,\n";
        inputOk = readValues("(5 целых чисел) -> ", second);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (first.size() != SIZE || second.size() != SIZE) {
        cout << "Ошибка! В каждом массиве должно быть 5 чисел\n";
    } else if (!(inLimit(first) && inLimit(second))) {
        cout << "Ошибка! Числа должны быть от -1000000 до 1000000\n";
    } else if (!(isSorted(first) && isSorted(second))) {
        cout << "Ошибка! Массивы должны быть упорядочены по возрастанию\n";
    } else {
        cout << "----------------------------------------\n";
        cout << "Массив - результат";
        for (int number : mergeSorted(first, second)) {
            cout << " " << number;
        }
        cout << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
