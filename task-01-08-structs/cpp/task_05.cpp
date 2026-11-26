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
const string SEPARATOR(56, '-');

string formatMoney(double value) {
    ostringstream out;
    out << fixed << setprecision(2) << value;
    return out.str();
}

void printTitle(const string& title) {
    cout << LINE << '\n' << title << '\n' << LINE << '\n';
}

void printNotFound() {
    cout << "Подходящих записей нет\n";
}

// Задача 5. Мультфильмы
struct Cartoon {
    string title;
    string studio;
    string directorSurname;
    string directorName;
    int year;
    string country;
    double budget;
    double revenue;

    double profit() const {
        return revenue - budget;
    }
};

void printCartoon(int number, const Cartoon& cartoon) {
    cout << "Мультфильм #" << number << '\n'
         << "  Название: " << cartoon.title << '\n'
         << "  Студия: " << cartoon.studio << '\n'
         << "  Режиссёр: " << cartoon.directorSurname << ' ' << cartoon.directorName << '\n'
         << "  Год выхода: " << cartoon.year << '\n'
         << "  Страна: " << cartoon.country << '\n'
         << "  Стоимость: " << formatMoney(cartoon.budget) << " млн долл.\n"
         << "  Доход: " << formatMoney(cartoon.revenue) << " млн долл.\n"
         << "  Прибыль: " << formatMoney(cartoon.profit()) << " млн долл.\n"
         << SEPARATOR << '\n';
}

void task05() {
    const vector<Cartoon> cartoons{
        {"Король Лев", "Walt Disney", "Аллерс", "Роджер", 1994, "США", 45, 968.5},
        {"Шрек", "DreamWorks", "Адамсон", "Эндрю", 2001, "США", 60, 484.4},
        {"Холодное сердце", "Walt Disney", "Бак", "Крис", 2013, "США", 150, 1280.8},
        {"Как приручить дракона", "DreamWorks", "Деблуа", "Дин", 2010, "США", 165, 494.9},
    };

    printTitle("Мультфильмы компании \"Walt Disney\":");
    int found = 0;
    for (const auto& cartoon : cartoons) {
        if (cartoon.studio == "Walt Disney") {
            printCartoon(++found, cartoon);
        }
    }
    if (found == 0) {
        printNotFound();
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    task05();
    return 0;
}
