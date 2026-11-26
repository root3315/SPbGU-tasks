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

// Деление с округлением вниз: нужно для дат до 1970 года
long long floorDiv(long long value, long long divisor) {
    long long result = value / divisor;
    if (value % divisor != 0 && (value < 0) != (divisor < 0)) {
        --result;
    }
    return result;
}

long long floorMod(long long value, long long divisor) {
    return value - floorDiv(value, divisor) * divisor;
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

// Секунды от начала суток для ЧЧ:ММ:СС (или ЧЧ:ММ)
bool parseTime(const string& text, bool withSeconds, long long& seconds) {
    vector<int> parts;
    if (!parseParts(text, ':', withSeconds ? 3 : 2, parts)) {
        return false;
    }
    int hours = parts[0], minutes = parts[1];
    int rest = withSeconds ? parts[2] : 0;
    if (hours > 23 || minutes > 59 || rest > 59) {
        return false;
    }
    seconds = hours * 3600 + minutes * 60 + rest;
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

bool readTime(const string& prompt, bool withSeconds, long long& seconds) {
    string text = readText(prompt);
    if (!parseTime(text, withSeconds, seconds)) {
        cout << "Ошибка! Нужно время в виде " << (withSeconds ? "ЧЧ:ММ:СС" : "ЧЧ:ММ") << '\n';
        return false;
    }
    return true;
}

string twoDigits(long long value) {
    ostringstream out;
    out << setfill('0') << setw(2) << value;
    return out.str();
}

string formatHm(long long seconds) {
    return twoDigits(seconds / 3600) + ':' + twoDigits(seconds % 3600 / 60);
}

// Вариант 5
void task05Part1() {
    printTitle("Вариант 5. Задача 1: проверка значения на дату");
    string text = readText("Значение: ");

    Date date;
    if (parseDate(text, 1, 9999, date)) {
        cout << '"' << text << "\" является датой\n";
    } else {
        cout << '"' << text << "\" не является датой вида ДД.ММ.ГГГГ\n";
    }
}

void task05Part2() {
    printTitle("Вариант 5. Задача 2: расписание процедур");
    long long first, second;
    int count;
    if (!readTime("Время первой процедуры (ЧЧ:ММ): ", false, first) ||
        !readTime("Время следующей процедуры (ЧЧ:ММ): ", false, second) ||
        !readInt("Количество процедур: ", 1, 100, count)) {
        return;
    }

    long long interval = floorMod(second - first, SECONDS_IN_DAY);
    if (interval == 0) {
        cout << "Ошибка! Следующая процедура должна быть в другое время\n";
        return;
    }

    cout << "Время процедур:\n";
    for (int number = 0; number < count; ++number) {
        long long moment = first + number * interval;
        cout << setw(3) << number + 1 << ". " << formatHm(moment % SECONDS_IN_DAY);
        if (moment >= SECONDS_IN_DAY) {
            cout << " (+" << moment / SECONDS_IN_DAY << " дн.)";
        }
        cout << '\n';
    }
}

void task05() {
    task05Part1();
    task05Part2();
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);        // ввод кириллицы в консоли Windows
    SetConsoleOutputCP(CP_UTF8);  // вывод кириллицы
#endif

    task05();
    return 0;
}
