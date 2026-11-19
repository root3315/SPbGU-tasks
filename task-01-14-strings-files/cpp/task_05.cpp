// Задача 5. Массив 3х5
#include <cmath>
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

    const size_t ROWS = 3, COLUMNS = 5;
    vector<vector<double>> matrix;
    bool inputOk = true;

    cout << "Ввод и обработка массива (3х5)\n";
    cout << "Введите массив по строкам\n";
    for (size_t i = 0; i < ROWS; i++) {
        vector<double> row;
        inputOk = readValues("Строка " + to_string(i + 1) + " -> ", row);
        if (!inputOk || row.size() != COLUMNS) {
            break;
        }
        matrix.push_back(row);
    }

    bool inRange = true;
    for (const vector<double>& row : matrix) {
        inRange = inRange && inLimit(row);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (matrix.size() != ROWS) {
        cout << "Ошибка! В строке должно быть 5 чисел\n";
    } else if (!inRange) {
        cout << "Ошибка! Числа должны быть от -1000000 до 1000000\n";
    } else {
        const string TITLE = "Массив: ";
        const string INDENT(8, ' ');  // ширина заголовка в символах (в байтах UTF-8 она больше)
        cout << "-------------------------------------\n";
        cout << defaultfloat << setprecision(15);
        for (size_t i = 0; i < ROWS; i++) {
            // Первая строка идёт после заголовка, остальные выровнены под неё
            cout << (i == 0 ? TITLE : INDENT);
            for (size_t j = 0; j < COLUMNS; j++) {
                cout << (j == 0 ? "" : " ") << matrix[i][j];
            }
            cout << "\n";
        }

        cout << "Среднее арифметическое:\n";
        cout << fixed << setprecision(2);
        for (size_t i = 0; i < ROWS; i++) {
            double total = 0;
            for (double number : matrix[i]) {
                total += number;
            }
            cout << "Строка " << i + 1 << ": " << total / COLUMNS << "\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
