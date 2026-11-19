// Задача 12. Добавление в справочник
#include <fstream>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const string CONTACTS_FILE = "contacts.txt";

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

    cout << "Добавление информации в телефонный справочник\n";
    string surname = readLine("Фамилия -> ");
    string name = readLine("Имя -> ");
    string phone = readLine("Телефон -> ");

    if (surname.empty() || name.empty() || phone.empty()) {
        cout << "Ошибка! Все поля должны быть заполнены\n";
    } else {
        // Режим app дописывает в конец файла и создаёт файл, если его нет
        ofstream file(CONTACTS_FILE, ios::app);
        file << surname << "\n" << name << "\n" << phone << "\n";

        if (!file) {
            cout << "Ошибка! Не удалось записать файл\n";
        } else {
            cout << "Информация добавлена\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);

    return 0;
}
