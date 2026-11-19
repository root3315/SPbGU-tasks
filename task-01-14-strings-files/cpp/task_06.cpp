// Задача 6. Приветствие
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
    SetConsoleCP(CP_UTF8);        // ввод кириллицы тоже в UTF-8
#endif

    cout << "Как Вас зовут?\n";
    cout << "Введите свое имя и фамилию, затем нажмите Enter\n";
    string name = readLine("-> ");

    if (name.empty()) {
        cout << "Ошибка! Имя не введено\n";
    } else {
        cout << "Здравствуйте, " << name << "!\n";
    }

    return 0;
}
