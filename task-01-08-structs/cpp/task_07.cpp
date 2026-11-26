#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const string LINE(56, '=');
const string SEPARATOR(56, '-');

void printTitle(const string& title) {
    cout << LINE << '\n' << title << '\n' << LINE << '\n';
}

void printNotFound() {
    cout << "Подходящих записей нет\n";
}

// Задача 7. Области
struct Region {
    string name;
    string center;
    int population;
    int area;
    string governor;
};

void printRegion(int number, const Region& region) {
    cout << "Область #" << number << '\n'
         << "  Название: " << region.name << '\n'
         << "  Областной центр: " << region.center << '\n'
         << "  Население: " << region.population << " чел.\n"
         << "  Площадь: " << region.area << " кв. км\n"
         << "  Губернатор: " << region.governor << '\n'
         << SEPARATOR << '\n';
}

void task07() {
    const vector<Region> regions{
        {"Псковская область", "Псков", 570000, 55399, "Иванов Иван Иванович"},
        {"Ленинградская область", "Гатчина", 2040000, 83908, "Петров Пётр Петрович"},
        {"Новгородская область", "Великий Новгород", 580000, 54501, "Сидоров Сергей Олегович"},
        {"Свердловская область", "Екатеринбург", 4240000, 194307, "Козлов Андрей Николаевич"},
        {"Мурманская область", "Мурманск", 650000, 144902, "Фёдоров Михаил Юрьевич"},
    };

    printTitle("Области, население которых меньше 1 млн жителей:");
    int found = 0;
    for (const auto& region : regions) {
        if (region.population < 1000000) {
            printRegion(++found, region);
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

    task07();
    return 0;
}
