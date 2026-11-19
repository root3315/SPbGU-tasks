// Задача 7. Код символа
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Если строка в UTF-8 состоит ровно из одного символа, записывает его код Unicode в code
bool decodeSingleChar(const string& text, long& code) {
    if (text.empty()) {
        return false;
    }

    // По первому байту определяем, сколько байт занимает символ
    unsigned char first = text[0];
    size_t length;
    if (first < 0x80) {
        length = 1;
        code = first;
    } else if ((first & 0xE0) == 0xC0) {
        length = 2;
        code = first & 0x1F;
    } else if ((first & 0xF0) == 0xE0) {
        length = 3;
        code = first & 0x0F;
    } else if ((first & 0xF8) == 0xF0) {
        length = 4;
        code = first & 0x07;
    } else {
        return false;
    }

    if (text.size() != length) {
        return false;
    }
    // Каждый следующий байт имеет вид 10xxxxxx и добавляет 6 бит кода
    for (size_t i = 1; i < length; i++) {
        unsigned char next = text[i];
        if ((next & 0xC0) != 0x80) {
            return false;
        }
        code = (code << 6) | (next & 0x3F);
    }
    return true;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
    SetConsoleCP(CP_UTF8);        // ввод кириллицы тоже в UTF-8
#endif

    cout << "Введите символ и нажмите Enter.\n";
    cout << "Для завершения введите точку.\n";
    while (true) {
        cout << "-> ";
        string symbol;
        if (!getline(cin, symbol) || symbol == ".") {
            break;
        }

        long code;
        if (decodeSingleChar(symbol, code)) {
            cout << "Символ: " << symbol << " Код: " << code << "\n";
        } else {
            cout << "Ошибка! Введите один символ\n";
        }
    }

    return 0;
}
