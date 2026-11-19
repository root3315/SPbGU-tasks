// Задача 13. Телефонный справочник
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

// Запрашивает фамилию, имя и телефон и дописывает их в справочник
void addContact() {
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
}

// Ищет в справочнике абонентов с введённой фамилией
void findContacts() {
    cout << "Поиск в телефонном справочнике\n";
    string surname = readLine("Фамилия -> ");

    if (surname.empty()) {
        cout << "Ошибка! Фамилия не введена\n";
        return;
    }

    ifstream file(CONTACTS_FILE);
    if (!file) {
        cout << "Справочник пуст\n";
        return;
    }

    // На каждого абонента в файле три строки: фамилия, имя, телефон
    int found = 0;
    string fileSurname, name, phone;
    while (getline(file, fileSurname) && getline(file, name) && getline(file, phone)) {
        if (trim(fileSurname) == surname) {
            cout << trim(fileSurname) << " " << trim(name) << ": " << trim(phone) << "\n";
            found++;
        }
    }

    if (found == 0) {
        cout << "Абонент не найден\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
    SetConsoleCP(CP_UTF8);        // ввод кириллицы тоже в UTF-8
#endif

    while (true) {
        cout << "*** Телефонный справочник ***\n";
        cout << "1 - Добавление\n";
        cout << "2 - Поиск\n";
        cout << "0 - Завершение работы\n";
        string choice = readLine("Ваш выбор -> ");
        if (cin.eof() || choice == "0") {
            break;
        }

        if (choice == "1") {
            addContact();
        } else if (choice == "2") {
            findContacts();
        } else {
            cout << "Ошибка! Неверный выбор\n";
        }
        cout << "\n";
    }

    return 0;
}
