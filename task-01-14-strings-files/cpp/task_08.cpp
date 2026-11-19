// Задача 8. Имя, отчество и фамилия
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
    SetConsoleCP(CP_UTF8);        // ввод кириллицы тоже в UTF-8
#endif

    cout << "Введите в одной строке имя, отчество и фамилию\n";
    cout << "-> ";
    string line;
    getline(cin, line);

    istringstream stream(line);
    vector<string> words;
    string word;
    while (stream >> word) {
        words.push_back(word);
    }

    if (words.size() != 3) {
        cout << "Ошибка! Нужно ввести три слова: имя, отчество и фамилию\n";
    } else {
        cout << "Имя: " << words[0] << "\n";
        cout << "Отчество: " << words[1] << "\n";
        cout << "Фамилия: " << words[2] << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
