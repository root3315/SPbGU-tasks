#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const string LINE(56, '=');
const long long SECONDS_IN_DAY = 24 * 60 * 60;

struct Date {
    int year;
    int month;
    int day;
};

void printTitle(const string& title) {
    cout << LINE << '\n' << title << '\n' << LINE << '\n';
}

bool isLeap(long long year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int year, int month) {
    const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2 && isLeap(year)) ? 29 : days[month - 1];
}

string trim(const string& text) {
    const string spaces = " \t\r\n";
    size_t begin = text.find_first_not_of(spaces);
    if (begin == string::npos) {
        return "";
    }
    size_t end = text.find_last_not_of(spaces);
    return text.substr(begin, end - begin + 1);
}

// Показывает подсказку и читает строку; если ввод закрыт, завершает программу
string readText(const string& prompt) {
    cout << prompt;
    string text;
    if (!getline(cin, text)) {
        exit(0);
    }
    return trim(text);
}

bool isNumber(const string& text) {
    if (text.empty() || text.size() > 9) {
        return false;
    }
    for (char symbol : text) {
        if (symbol < '0' || symbol > '9') {
            return false;
        }
    }
    return true;
}

// Делит строку на count целых неотрицательных чисел; false, если не получилось
bool parseParts(const string& text, char separator, size_t count, vector<int>& numbers) {
    vector<string> parts{""};
    for (char symbol : text) {
        if (symbol == separator) {
            parts.push_back("");
        } else {
            parts.back() += symbol;
        }
    }
    if (parts.size() != count) {
        return false;
    }
    numbers.clear();
    for (const auto& part : parts) {
        if (!isNumber(part)) {
            return false;
        }
        numbers.push_back(stoi(part));
    }
    return true;
}

bool parseDate(const string& text, int minYear, int maxYear, Date& date) {
    vector<int> parts;
    if (!parseParts(text, '.', 3, parts)) {
        return false;
    }
    int day = parts[0], month = parts[1], year = parts[2];
    if (year < minYear || year > maxYear || month < 1 || month > 12) {
        return false;
    }
    if (day < 1 || day > daysInMonth(year, month)) {
        return false;
    }
    date = {year, month, day};
    return true;
}

bool readInt(const string& prompt, int low, int high, int& value) {
    string text = readText(prompt);
    if (!isNumber(text) || stoi(text) < low || stoi(text) > high) {
        cout << "Ошибка! Нужно целое число от " << low << " до " << high << '\n';
        return false;
    }
    value = stoi(text);
    return true;
}

bool readDate(const string& prompt, Date& date, int minYear = 1, int maxYear = 9999) {
    string text = readText(prompt);
    if (!parseDate(text, minYear, maxYear, date)) {
        cout << "Ошибка! Нужна дата в виде ДД.ММ.ГГГГ, год от " << minYear << " до " << maxYear << '\n';
        return false;
    }
    return true;
}

string twoDigits(long long value) {
    ostringstream out;
    out << setfill('0') << setw(2) << value;
    return out.str();
}

string formatTime(long long seconds) {
    return twoDigits(seconds / 3600) + ':' + twoDigits(seconds % 3600 / 60) + ':' +
           twoDigits(seconds % 60);
}

// Вариант 4
void task04Part1() {
    printTitle("Вариант 4. Задача 1: время из отдельных значений");
    int hours, minutes, seconds, milliseconds;
    if (!readInt("Часы (0-23): ", 0, 23, hours) ||
        !readInt("Минуты (0-59): ", 0, 59, minutes) ||
        !readInt("Секунды (0-59): ", 0, 59, seconds) ||
        !readInt("Миллисекунды (0-999): ", 0, 999, milliseconds)) {
        return;
    }

    long long total = hours * 3600 + minutes * 60 + seconds;
    cout << "Время: " << formatTime(total) << '.' << setfill('0') << setw(3) << milliseconds
         << setfill(' ') << '\n';
}

void task04Part2() {
    printTitle("Вариант 4. Задача 2: високосный год");
    Date date;
    if (!readDate("Дата (ДД.ММ.ГГГГ): ", date)) {
        return;
    }

    if (isLeap(date.year)) {
        cout << date.year << " год високосный\n";
        return;
    }

    int leapYear = date.year + 1;
    while (!isLeap(leapYear)) {
        ++leapYear;
    }
    cout << date.year << " год не високосный\n";
    cout << "Ближайший високосный год: " << leapYear << ", до него лет: " << leapYear - date.year << '\n';
}

void task04() {
    task04Part1();
    task04Part2();
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);        // ввод кириллицы в консоли Windows
    SetConsoleOutputCP(CP_UTF8);  // вывод кириллицы
#endif

    task04();
    return 0;
}
