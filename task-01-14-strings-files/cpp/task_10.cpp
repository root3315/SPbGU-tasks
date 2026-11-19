// Задача 10. Двоичное в десятичное
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Убирает пробельные символы по краям строки
string trim(const string& text) {
    const string SPACES = " \t\r\n\v\f";
    size_t begin = text.find_first_not_of(SPACES);
    if (begin == string::npos) {
        return "";
    }
    size_t end = text.find_last_not_of(SPACES);
    return text.substr(begin, end - begin + 1);
}

// Показывает подсказку и читает строку целиком, без пробелов по краям
string readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return trim(line);
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    cout << "Введите восьмиразрядное двоичное число и нажмите Enter\n";
    string binary = readLine("-> ");

    bool isBinary = binary.size() == 8;
    for (char digit : binary) {
        if (digit != '0' && digit != '1') {
            isBinary = false;
        }
    }

    if (!isBinary) {
        cout << "Ошибка! Нужно ввести 8 цифр 0 или 1\n";
    } else {
        int decimal = 0;
        for (char digit : binary) {
            decimal = decimal * 2 + (digit == '1' ? 1 : 0);
        }
        cout << "Двоичному числу " << binary << " соответствует десятичное " << decimal << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
