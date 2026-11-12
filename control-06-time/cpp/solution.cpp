// Текущий контроль. Задание 6: класс «Время»
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const long long SECONDS_IN_MINUTE = 60;
const long long MINUTES_IN_HOUR = 60;
const long long HOURS_IN_DAY = 24;
const long long MINUTES_IN_DAY = MINUTES_IN_HOUR * HOURS_IN_DAY;
const long long SECONDS_IN_DAY = SECONDS_IN_MINUTE * MINUTES_IN_DAY;

// Деление с округлением вниз и неотрицательный остаток, чтобы время можно было отматывать назад
long long floorDiv(long long value, long long divisor) {
    long long quotient = value / divisor;
    if (value % divisor < 0) {
        --quotient;
    }
    return quotient;
}

long long floorMod(long long value, long long divisor) {
    return value - floorDiv(value, divisor) * divisor;
}

class Time {
public:
    static bool isValid(int hours, int minutes, int seconds) {
        return hours >= 0 && hours < HOURS_IN_DAY
            && minutes >= 0 && minutes < MINUTES_IN_HOUR
            && seconds >= 0 && seconds < SECONDS_IN_MINUTE;
    }

    Time(int hours, int minutes, int seconds) {
        if (!isValid(hours, minutes, seconds)) {
            throw invalid_argument("время вне допустимого диапазона");
        }
        hours_ = hours;
        minutes_ = minutes;
        seconds_ = seconds;
    }

    void addSeconds(long long amount) {
        // Полные сутки не меняют время, а без них сумма не переполнится
        long long total = seconds_ + amount % SECONDS_IN_DAY;
        seconds_ = floorMod(total, SECONDS_IN_MINUTE);
        // Лишние секунды переходят в минуты: 65 секунд = 1 минута и 5 секунд
        addMinutes(floorDiv(total, SECONDS_IN_MINUTE));
    }

    void addMinutes(long long amount) {
        long long total = minutes_ + amount % MINUTES_IN_DAY;
        minutes_ = floorMod(total, MINUTES_IN_HOUR);
        addHours(floorDiv(total, MINUTES_IN_HOUR));
    }

    void addHours(long long amount) {
        hours_ = floorMod(hours_ + amount % HOURS_IN_DAY, HOURS_IN_DAY);
    }

    string toString() const {
        ostringstream out;
        out << setfill('0') << setw(2) << hours_ << ':'
            << setw(2) << minutes_ << ':' << setw(2) << seconds_;
        return out.str();
    }

private:
    int hours_;
    int minutes_;
    int seconds_;
};

// Показывает подсказку и читает значение: в строке не должно быть ничего лишнего
template <typename T>
bool readValue(const string& prompt, T& value) {
    cout << prompt;

    string line;
    getline(cin, line);

    istringstream stream(line);
    char extra;
    return (stream >> value) && !(stream >> extra);
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    int hours, minutes, seconds;

    cout << "Начальное время\n";
    bool inputOk = readValue("Часы –> ", hours)
        && readValue("Минуты –> ", minutes)
        && readValue("Секунды –> ", seconds);

    if (!inputOk || !Time::isValid(hours, minutes, seconds)) {
        cout << "Ошибка! Неверное время\n";
        return 0;
    }

    Time time(hours, minutes, seconds);

    cout << "Время: " << time.toString() << '\n';

    while (true) {
        cout << "-----------------------------\n";
        cout << "1 – Добавить секунды\n";
        cout << "2 – Добавить минуты\n";
        cout << "0 – Выход\n";

        int choice;
        if (!readValue("Ваш выбор –> ", choice)) {
            if (!cin) {
                break;  // ввод закончился
            }
            cout << "Ошибка! Неверный выбор\n";
            continue;
        }

        if (choice == 0) {
            break;
        }
        if (choice != 1 && choice != 2) {
            cout << "Ошибка! Неверный выбор\n";
            continue;
        }

        long long amount;
        string prompt = choice == 1 ? "Сколько секунд –> " : "Сколько минут –> ";
        if (!readValue(prompt, amount)) {
            cout << "Ошибка! Неверный формат числа\n";
            continue;
        }

        if (choice == 1) {
            time.addSeconds(amount);
        } else {
            time.addMinutes(amount);
        }
        cout << "Время: " << time.toString() << '\n';
    }

    return 0;
}
