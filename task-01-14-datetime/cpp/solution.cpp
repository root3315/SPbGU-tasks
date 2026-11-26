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

bool isBefore(const Date& first, const Date& second) {
    return toDays(first) < toDays(second);
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

bool readTime(const string& prompt, bool withSeconds, long long& seconds) {
    string text = readText(prompt);
    if (!parseTime(text, withSeconds, seconds)) {
        cout << "Ошибка! Нужно время в виде " << (withSeconds ? "ЧЧ:ММ:СС" : "ЧЧ:ММ") << '\n';
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

string formatDate(const Date& date) {
    ostringstream out;
    out << twoDigits(date.day) << '.' << twoDigits(date.month) << '.'
        << setfill('0') << setw(4) << date.year;
    return out.str();
}

string formatTime(long long seconds) {
    return twoDigits(seconds / 3600) + ':' + twoDigits(seconds % 3600 / 60) + ':' +
           twoDigits(seconds % 60);
}

string formatHm(long long seconds) {
    return twoDigits(seconds / 3600) + ':' + twoDigits(seconds % 3600 / 60);
}

string formatDateTime(long long moment) {
    return formatDate(momentDate(moment)) + ' ' + formatTime(momentSeconds(moment));
}

string weekdayText(const Date& date) {
    int number = weekday(date);
    return to_string(number) + " (" + WEEKDAYS[number - 1] + ")";
}

// Тот же день и месяц в другом году; 29 февраля в невисокосном году — 28 февраля
Date sameDayInYear(const Date& date, int year) {
    int day = date.day;
    if (day > daysInMonth(year, date.month)) {
        day = daysInMonth(year, date.month);
    }
    return {year, date.month, day};
}

// Вариант 1
void task01Part1() {
    printTitle("Вариант 1. Задача 1: более поздняя из двух дат");
    Date first, second;
    if (!readDate("Первая дата (ДД.ММ.ГГГГ): ", first) ||
        !readDate("Вторая дата (ДД.ММ.ГГГГ): ", second)) {
        return;
    }

    if (isBefore(second, first)) {
        cout << "Более поздняя дата: " << formatDate(first) << " (первая)\n";
    } else if (isBefore(first, second)) {
        cout << "Более поздняя дата: " << formatDate(second) << " (вторая)\n";
    } else {
        cout << "Даты совпадают\n";
    }
}

void task01Part2() {
    printTitle("Вариант 1. Задача 2: контроль батареи ноутбука");
    long long start;
    int declaredHours;
    if (!readDateTime("Дата и время включения от батареи (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1900, 2100, start) ||
        !readInt("Заявленное время работы от батареи, ч: ", 1, 100, declaredHours)) {
        return;
    }

    long long worked = now() - start;
    if (worked < 0) {
        cout << "Ошибка! Время включения ещё не наступило\n";
        return;
    }

    cout << "Ноутбук работает от батареи: " << worked / 3600 << " ч " << worked % 3600 / 60 << " мин\n";
    long long left = declaredHours * 3600LL - worked;
    if (left > 0) {
        cout << "До полного разряда осталось: " << left / 60 << " мин\n";
    } else {
        cout << "Батарея полностью разряжена\n";
    }
}

void task01() {
    task01Part1();
    task01Part2();
}

// Вариант 2
void task02Part1() {
    printTitle("Вариант 2. Задача 1: текущие дата и время");
    cout << "Сейчас: " << formatDateTime(now()) << '\n';
}

void task02Part2() {
    printTitle("Вариант 2. Задача 2: срок действия пакета связи");
    Date callDate;
    long long callTime;
    if (!readDate("Дата последнего исходящего звонка (ДД.ММ.ГГГГ): ", callDate, 1900, 2100) ||
        !readTime("Время звонка (ЧЧ:ММ): ", false, callTime)) {
        return;
    }

    Date endDate = sameDayInYear(callDate, callDate.year + 1);
    cout << "Пакет действует до: " << formatDate(endDate) << ' ' << formatHm(callTime) << '\n';
    cout << "День недели: " << weekdayText(endDate) << '\n';
}

void task02() {
    task02Part1();
    task02Part2();
}

// Вариант 3
void task03Part1() {
    printTitle("Вариант 3. Задача 1: время без ведущих нулей");
    long long seconds;
    if (!readTime("Время (ЧЧ:ММ:СС): ", true, seconds)) {
        return;
    }

    long long hours = seconds / 3600, minutes = seconds % 3600 / 60, rest = seconds % 60;
    cout << "Часы (0-23): " << hours << '\n'
         << "Минуты (0-59): " << minutes << '\n'
         << "Секунды (0-59): " << rest << '\n'
         << "Время: " << hours << ':' << minutes << ':' << rest << '\n';
}

void task03Part2() {
    printTitle("Вариант 3. Задача 2: срок давности правонарушения");
    Date offence;
    if (!readDate("Дата правонарушения (ДД.ММ.ГГГГ): ", offence, 1900, 2100)) {
        return;
    }

    Date current = today();
    if (isBefore(current, offence)) {
        cout << "Ошибка! Дата правонарушения ещё не наступила\n";
        return;
    }

    int months = (current.year - offence.year) * 12 + current.month - offence.month;
    if (current.day < offence.day) {
        --months;
    }
    cout << "Прошло полных дней: " << toDays(current) - toDays(offence) << '\n'
         << "Прошло полных месяцев: " << months << '\n'
         << "Прошло полных лет: " << months / 12 << '\n';
}

void task03() {
    task03Part1();
    task03Part2();
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

// Вариант 7
void task07Part1() {
    printTitle("Вариант 7. Задача 1: составляющие даты");
    Date date;
    if (!readDate("Дата (ДД.ММ.ГГГГ): ", date)) {
        return;
    }

    cout << "День: " << date.day << '\n'
         << "Месяц: " << date.month << '\n'
         << "Год: " << date.year << '\n';
}

void task07Part2() {
    printTitle("Вариант 7. Задача 2: срок годности продукта");
    long long made;
    int shelfHours;
    if (!readDateTime("Дата и время производства (ДД.ММ.ГГГГ ЧЧ:ММ): ", 1900, 2100, made) ||
        !readInt("Срок годности, ч: ", 1, 87600, shelfHours)) {
        return;
    }

    long long current = now();
    if (made > current) {
        cout << "Ошибка! Дата производства ещё не наступила\n";
        return;
    }

    long long expiry = made + shelfHours * 3600LL;
    long long left = expiry - current;
    if (left > 0) {
        cout << "Годен до: " << formatDateTime(expiry) << '\n'
             << "До истечения срока годности осталось: " << left / 3600 << " ч\n";
    } else {
        cout << "Внимание! Срок годности истёк " << formatDateTime(expiry) << '\n';
    }
}

void task07() {
    task07Part1();
    task07Part2();
}

// Вариант 8
void task08Part1() {
    printTitle("Вариант 8. Задача 1: текущая дата");
    cout << "Сегодня: " << formatDate(today()) << '\n';
}

void task08Part2() {
    printTitle("Вариант 8. Задача 2: расчёт телепередачи");
    long long start;
    int duration;
    if (!readTime("Начало эфира (ЧЧ:ММ:СС): ", true, start) ||
        !readInt("Продолжительность, с: ", 1, static_cast<int>(SECONDS_IN_DAY), duration)) {
        return;
    }

    long long end = start + duration;
    cout << "Окончание: " << formatTime(end % SECONDS_IN_DAY);
    if (end >= SECONDS_IN_DAY) {
        cout << " (на следующий день)";
    }
    cout << '\n'
         << "Продолжительность: " << duration / 60 << " мин " << duration % 60 << " с\n"
         // пауза ставится после каждых полных 5 минут, но не в самом конце передачи
         << "Рекламных пауз: " << (duration - 1) / 300 << '\n';
}

void task08() {
    task08Part1();
    task08Part2();
}

// Вариант 9
void task09Part1() {
    printTitle("Вариант 9. Задача 1: проверка значения на время");
    string text = readText("Значение: ");

    long long seconds;
    if (parseTime(text, true, seconds) || parseTime(text, false, seconds)) {
        cout << '"' << text << "\" является временем\n";
    } else {
        cout << '"' << text << "\" не является временем вида ЧЧ:ММ или ЧЧ:ММ:СС\n";
    }
}

void task09Part2() {
    printTitle("Вариант 9. Задача 2: отложенный запуск посудомоечной машины");
    int washMinutes, delayHours;
    if (!readInt("Длительность мойки, мин: ", 1, 1440, washMinutes) ||
        !readInt("Отсрочка запуска, ч: ", 0, 24, delayHours)) {
        return;
    }

    long long pressed = now();
    long long start = pressed + delayHours * 3600LL;
    long long end = start + washMinutes * 60LL;
    cout << "Кнопка «Пуск» нажата: " << formatDateTime(pressed) << '\n'
         << "Начало мойки: " << formatDateTime(start) << '\n'
         << "Окончание мойки: " << formatDateTime(end) << '\n';
}

void task09() {
    task09Part1();
    task09Part2();
}

// Вариант 10
void task10Part1() {
    printTitle("Вариант 10. Задача 1: номер дня недели");
    Date date;
    if (!readDate("Дата (ДД.ММ.ГГГГ): ", date)) {
        return;
    }

    cout << "День недели: " << weekdayText(date) << '\n';
}

void task10Part2() {
    printTitle("Вариант 10. Задача 2: дни до дня рождения");
    Date birth;
    if (!readDate("Дата рождения (ДД.ММ.ГГГГ): ", birth, 1900, 2100)) {
        return;
    }

    Date current = today();
    if (isBefore(current, birth)) {
        cout << "Ошибка! Дата рождения ещё не наступила\n";
        return;
    }

    long long difference = toDays(sameDayInYear(birth, current.year)) - toDays(current);
    if (difference == 0) {
        cout << "День рождения сегодня!\n";
    } else if (difference > 0) {
        cout << "До дня рождения осталось дней: " << difference << '\n';
    } else {
        cout << "День рождения в этом году уже прошёл, прошло дней: " << -difference << '\n';
    }
}

void task10() {
    task10Part1();
    task10Part2();
}

// Вариант 11
void task11Part1() {
    printTitle("Вариант 11. Задача 1: секунды между двумя значениями времени");
    long long first, second;
    if (!readTime("Первое время (ЧЧ:ММ:СС): ", true, first) ||
        !readTime("Второе время (ЧЧ:ММ:СС): ", true, second)) {
        return;
    }

    cout << "Между ними секунд: " << llabs(second - first) << '\n';
}

void task11Part2() {
    printTitle("Вариант 11. Задача 2: бегущая строка вокзала");
    string direction = readText("Направление поезда: ");
    if (direction.empty()) {
        cout << "Ошибка! Направление не может быть пустым\n";
        return;
    }
    long long departure;
    int platform, track;
    if (!readTime("Время отправления (ЧЧ:ММ): ", false, departure) ||
        !readInt("Номер платформы: ", 1, 99, platform) ||
        !readInt("Номер пути: ", 1, 99, track)) {
        return;
    }

    // если время отправления уже прошло, поезд уходит завтра
    long long currentMinute = momentSeconds(now()) / 60;
    long long minutesLeft = floorMod(departure / 60 - currentMinute, 24 * 60);
    cout << "«Поезд следованием " << direction << " отправляется от " << platform << " платформы "
         << track << " пути через " << minutesLeft << " мин»\n";
}

void task11() {
    task11Part1();
    task11Part2();
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

// Вариант 13
void task13Part1() {
    printTitle("Вариант 13. Задача 1: время с ведущими нулями");
    long long seconds;
    if (!readTime("Время (ЧЧ:ММ:СС): ", true, seconds)) {
        return;
    }

    cout << "Часы (00-23): " << twoDigits(seconds / 3600) << '\n'
         << "Минуты (00-59): " << twoDigits(seconds % 3600 / 60) << '\n'
         << "Секунды (00-59): " << twoDigits(seconds % 60) << '\n'
         << "Время: " << formatTime(seconds) << '\n';
}

void task13Part2() {
    printTitle("Вариант 13. Задача 2: предвыборная агитация");
    Date voting;
    if (!readDate("Дата голосования (ДД.ММ.ГГГГ): ", voting, 1900, 2100)) {
        return;
    }

    long long daysLeft = toDays(voting) - toDays(today());
    if (daysLeft > 0) {
        cout << "До голосования осталось дней: " << daysLeft << '\n';
    } else if (daysLeft == 0) {
        cout << "Голосование проходит сегодня\n";
    } else {
        cout << "Голосование уже прошло\n";
    }
    cout << "Агитация прекращается " << formatDate(fromDays(toDays(voting) - 1)) << " в 00:00\n";
}

void task13() {
    task13Part1();
    task13Part2();
}

// Вариант 14
void task14Part1() {
    printTitle("Вариант 14. Задача 1: минуты между двумя значениями времени");
    long long first, second;
    if (!readTime("Первое время (ЧЧ:ММ): ", false, first) ||
        !readTime("Второе время (ЧЧ:ММ): ", false, second)) {
        return;
    }

    cout << "Между ними минут: " << llabs(second - first) / 60 << '\n';
}

void task14Part2() {
    printTitle("Вариант 14. Задача 2: перенос праздника с воскресенья");
    int day, month;
    if (!readInt("День праздника (1-31): ", 1, 31, day) ||
        !readInt("Месяц праздника (1-12): ", 1, 12, month)) {
        return;
    }

    int year = today().year;
    if (day > daysInMonth(year, month)) {
        cout << "Ошибка! В " << year << " году в этом месяце нет такого дня\n";
        return;
    }

    Date holiday{year, month, day};
    cout << "В " << year << " году праздник выпадает на день недели: " << weekdayText(holiday) << '\n';
    if (weekday(holiday) == 7) {
        cout << "Праздник в воскресенье, выходной переносится на понедельник "
             << formatDate(fromDays(toDays(holiday) + 1)) << '\n';
    } else {
        cout << "Праздник не в воскресенье, переноса нет\n";
    }
}

void task14() {
    task14Part1();
    task14Part2();
}

// Номер варианта из строки; -1, если в строке не одно целое число
int parseChoice(const string& line) {
    istringstream stream(line);
    int choice;
    char extra;
    if ((stream >> choice) && !(stream >> extra)) {
        return choice;
    }
    return -1;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);        // ввод кириллицы в консоли Windows
    SetConsoleOutputCP(CP_UTF8);  // вывод кириллицы
#endif

    while (true) {
        cout << "\n=============================================\n";
        cout << " 1. Поздняя дата, батарея ноутбука\n";
        cout << " 2. Текущие дата и время, пакет связи\n";
        cout << " 3. Время без нулей, срок давности\n";
        cout << " 4. Время из частей, високосный год\n";
        cout << " 5. Проверка даты, расписание процедур\n";
        cout << " 6. Текущее время, стоимость звонка\n";
        cout << " 7. Части даты, срок годности\n";
        cout << " 8. Текущая дата, телепередача\n";
        cout << " 9. Проверка времени, посудомойка\n";
        cout << "10. День недели, день рождения\n";
        cout << "11. Секунды между временами, вокзал\n";
        cout << "12. Формат даты, минута года\n";
        cout << "13. Время с нулями, выборы\n";
        cout << "14. Минуты между временами, праздник\n";
        cout << " 0. Выход\n";
        cout << "=============================================\n";

        cout << "Номер варианта -> ";
        string line;
        if (!getline(cin, line)) {
            break;  // ввод закрыт: просто завершаем программу
        }

        int choice = parseChoice(line);
        if (choice == 0) {
            break;
        }

        cout << "\n";
        switch (choice) {
            case 1: task01(); break;
            case 2: task02(); break;
            case 3: task03(); break;
            case 4: task04(); break;
            case 5: task05(); break;
            case 6: task06(); break;
            case 7: task07(); break;
            case 8: task08(); break;
            case 9: task09(); break;
            case 10: task10(); break;
            case 11: task11(); break;
            case 12: task12(); break;
            case 13: task13(); break;
            case 14: task14(); break;
            default: cout << "Нет такого варианта\n";
        }
    }

    return 0;
}
