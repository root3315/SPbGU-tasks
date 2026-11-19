// Задача 9. Проверка целого числа
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

// Проверяет посимвольно: необязательный знак + или -, затем хотя бы одна цифра
bool isInteger(const string& text) {
    size_t start = (!text.empty() && (text[0] == '+' || text[0] == '-')) ? 1 : 0;
    if (start == text.size()) {
        return false;
    }
    for (size_t i = start; i < text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    cout << "Введите число и нажмите Enter\n";
    string text = readLine("-> ");

    if (isInteger(text)) {
        cout << "Введенная строка является целым числом.\n";
    } else {
        cout << "Введенная строка не является целым числом.\n";
    }

    return 0;
}
