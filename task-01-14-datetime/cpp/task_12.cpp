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
const vector<string> WEEKDAYS{"понедельник", "вторник", "среда", "четверг",
                              "пятница", "суббота", "воскресенье"};
const vector<string> WEEKDAYS_SHORT{"пн", "вт", "ср", "чт", "пт", "сб", "вс"};

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

int weekday(const Date& date) {
    return static_cast<int>(floorMod(toDays(date) + 3, 7)) + 1;  // 01.01.1970 — четверг
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

bool parseDateTime(const string& text, int minYear, int maxYear, long long& moment) {
    istringstream stream(text);
    string datePart, timePart, extra;
    if (!(stream >> datePart >> timePart) || (stream >> extra)) {
        return false;
    }
    Date date;
    long long seconds;
    if (!parseDate(datePart, minYear, maxYear, date) || !parseTime(timePart, false, seconds)) {
        return false;
    }
    moment = toMoment(date, seconds);
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

bool readDateTime(const string& prompt, int minYear, int maxYear, long long& moment) {
    string text = readText(prompt);
    if (!parseDateTime(text, minYear, maxYear, moment)) {
        cout << "Ошибка! Нужны дата и время в виде ДД.ММ.ГГГГ ЧЧ:ММ, год от "
             << minYear << " до " << maxYear << '\n';
        return false;
    }
    return true;
}

string twoDigits(long long value) {
    ostringstream out;
    out << setfill('0') << setw(2) << value;
    return out.str();
}

string weekdayText(const Date& date) {
    int number = weekday(date);
    return to_string(number) + " (" + WEEKDAYS[number - 1] + ")";
}

// Вариант 12
void task12Part1() {
    printTitle("Вариант 12. Задача 1: форматирование даты");
    Date date;
    if (!readDate("Дата (ДД.ММ.ГГГГ): ", date)) {
        return;
    }

    cout << "День (01-31): " << twoDigits(date.day) << '\n'
         << "День недели (пн-вс): " << WEEKDAYS_SHORT[weekday(date) - 1] << '\n'
         << "Месяц (01-12): " << twoDigits(date.month) << '\n'
         << "Год (0000-9999): " << setfill('0') << setw(4) << date.year << setfill(' ') << '\n';
}

void task12Part2() {
    printTitle("Вариант 12. Задача 2: минута года исторического события");
    long long event;
    if (!readDateTime("Дата и время события (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1, 9999, event)) {
        return;
    }

    Date eventDate = momentDate(event);
    long long yearStart = toMoment({eventDate.year, 1, 1}, 0);
    cout << "Событие произошло на " << (event - yearStart) / 60 + 1 << "-й минуте от начала года\n"
         << "День недели: " << weekdayText(eventDate) << '\n';
}

void task12() {
    task12Part1();
    task12Part2();
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);        // ввод кириллицы в консоли Windows
    SetConsoleOutputCP(CP_UTF8);  // вывод кириллицы
#endif

    task12();
    return 0;
}
