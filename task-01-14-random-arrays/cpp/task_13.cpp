// Задача 13. Минимальный элемент массива
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Показывает подсказку и читает целые числа из одной строки; false, если в строке не только числа
bool readNumbersLine(const string& prompt, vector<long long>& numbers) {
    cout << prompt;

    string line;
    getline(cin, line);

    // Каждое слово строки должно целиком быть целым числом
    istringstream stream(line);
    string word;
    while (stream >> word) {
        istringstream wordStream(word);
        long long number;
        char extra;
        if (!(wordStream >> number) || (wordStream >> extra)) {
            return false;
        }
        numbers.push_back(number);
    }
    return true;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    const size_t SIZE = 5;
    const long long LIMIT = 1000000000;
    vector<long long> numbers;

    cout << "Поиск минимального элемента массива\n";
    cout << "Введите в одной строке " << SIZE << " целых чисел и нажмите Enter\n";
    bool inputOk = readNumbersLine("-> ", numbers);

    bool inRange = true;
    long long minimum = numbers.empty() ? 0 : numbers[0];
    for (long long number : numbers) {
        if (number > LIMIT || number < -LIMIT) {
            inRange = false;
        }
        if (number < minimum) {
            minimum = number;
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (numbers.size() != SIZE) {
        cout << "Ошибка! Нужно ввести ровно " << SIZE << " чисел\n";
    } else if (!inRange) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        cout << "Минимальный элемент массива: " << minimum << "\n";
    }

    return 0;
}
