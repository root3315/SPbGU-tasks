#include <cstdlib>
#include <ctime>
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

// Номер дня от 01.01.1970 (может быть отрицательным)
long long toDays(const Date& date) {
    long long year = date.month <= 2 ? date.year - 1 : date.year;
    long long era = floorDiv(year, 400);
    long long yearOfEra = year - era * 400;
    long long monthIndex = (date.month + 9) % 12;  // март = 0
    long long dayOfYear = (153 * monthIndex + 2) / 5 + date.day - 1;
    long long dayOfEra = yearOfEra * 365 + yearOfEra / 4 - yearOfEra / 100 + dayOfYear;
    return era * 146097 + dayOfEra - 719468;
}

Date fromDays(long long days) {
    days += 719468;
    long long era = floorDiv(days, 146097);
    long long dayOfEra = days - era * 146097;
    long long yearOfEra = (dayOfEra - dayOfEra / 1460 + dayOfEra / 36524 - dayOfEra / 146096) / 365;
    long long dayOfYear = dayOfEra - (365 * yearOfEra + yearOfEra / 4 - yearOfEra / 100);
    long long monthIndex = (5 * dayOfYear + 2) / 153;
    int day = static_cast<int>(dayOfYear - (153 * monthIndex + 2) / 5 + 1);
    int month = static_cast<int>(monthIndex < 10 ? monthIndex + 3 : monthIndex - 9);
    int year = static_cast<int>(yearOfEra + era * 400 + (month <= 2 ? 1 : 0));
    return {year, month, day};
}

// Момент времени: секунды от 01.01.1970 00:00:00 по местному времени
long long toMoment(const Date& date, long long secondsOfDay) {
    return toDays(date) * SECONDS_IN_DAY + secondsOfDay;
}

Date momentDate(long long moment) {
    return fromDays(floorDiv(moment, SECONDS_IN_DAY));
}

long long momentSeconds(long long moment) {
    return floorMod(moment, SECONDS_IN_DAY);
}

long long now() {
    time_t current = time(nullptr);
    tm local = *localtime(&current);
    Date today{local.tm_year + 1900, local.tm_mon + 1, local.tm_mday};
    return toMoment(today, local.tm_hour * 3600 + local.tm_min * 60 + local.tm_sec);
}

Date today() {
    return momentDate(now());
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

string formatTime(long long seconds) {
    return twoDigits(seconds / 3600) + ':' + twoDigits(seconds % 3600 / 60) + ':' +
           twoDigits(seconds % 60);
}

// Вариант 6
void task06Part1() {
    printTitle("Вариант 6. Задача 1: текущее время");
    cout << "Текущее время: " << formatTime(momentSeconds(now())) << '\n';
}

void task06Part2() {
    printTitle("Вариант 6. Задача 2: стоимость звонка");
    long long start, end;
    int price;
    if (!readTime("Начало звонка (ЧЧ:ММ:СС): ", true, start) ||
        !readTime("Окончание звонка (ЧЧ:ММ:СС): ", true, end) ||
        !readInt("Стоимость минуты, коп.: ", 0, 100000, price)) {
        return;
    }

    long long duration = floorMod(end - start, SECONDS_IN_DAY);  // звонок мог перейти через полночь
    long long minutes = (duration + 59) / 60;  // неполная минута оплачивается как полная
    long long cost = minutes * price;
    cout << "Длительность звонка: " << duration << " с\n"
         << "Оплачено минут: " << minutes << '\n'
         << "Снято со счёта: " << cost / 100 << '.' << twoDigits(cost % 100) << " руб.\n";
}

void task06() {
    task06Part1();
    task06Part2();
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);        // ввод кириллицы в консоли Windows
    SetConsoleOutputCP(CP_UTF8);  // вывод кириллицы
#endif

    task06();
    return 0;
}
