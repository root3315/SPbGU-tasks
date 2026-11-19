// Задача 14. Среднее ненулевых элементов
#include <iomanip>
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

    const size_t SIZE = 10;
    const long long LIMIT = 1000000000;
    vector<long long> numbers;

    cout << "Введите элементы массива (" << SIZE << " целых чисел в одной строке) и нажмите Enter\n";
    bool inputOk = readNumbersLine("-> ", numbers);

    bool inRange = true;
    long long total = 0;
    int nonzero = 0;
    for (long long number : numbers) {
        if (number > LIMIT || number < -LIMIT) {
            inRange = false;
        }
        total += number;
        if (number != 0) {
            nonzero++;
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (numbers.size() != SIZE) {
        cout << "Ошибка! Нужно ввести ровно " << SIZE << " чисел\n";
    } else if (!inRange) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        cout << "-------------------------------\n";
        if (nonzero == 0) {
            cout << "Ненулевых элементов нет\n";
        } else {
            cout << "Сумма элементов массива: " << total << "\n";
            cout << "Количество ненулевых элементов: " << nonzero << "\n";
            cout << fixed << setprecision(2);
            cout << "Среднее арифметическое ненулевых элементов: "
                 << static_cast<double>(total) / nonzero << "\n";
        }
    }

    return 0;
}
