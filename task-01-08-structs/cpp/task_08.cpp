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

// Задача 8. Мотоциклы
struct Motorcycle {
    string brand;
    string color;
    string serialNumber;
    string registrationNumber;
    int manufactureYear;
    int inspectionYear;
    double price;
};

void printMotorcycle(int number, const Motorcycle& motorcycle) {
    cout << "Мотоцикл #" << number << '\n'
         << "  Марка: " << motorcycle.brand << '\n'
         << "  Цвет: " << motorcycle.color << '\n'
         << "  Серийный номер: " << motorcycle.serialNumber << '\n'
         << "  Регистрационный номер: " << motorcycle.registrationNumber << '\n'
         << "  Год выпуска: " << motorcycle.manufactureYear << '\n'
         << "  Год техосмотра: " << motorcycle.inspectionYear << '\n'
         << "  Цена: " << formatMoney(motorcycle.price) << " руб.\n"
         << SEPARATOR << '\n';
}

void task08() {
    const vector<Motorcycle> motorcycles{
        {"HarleyDavidson", "чёрный", "HD100234", "1234АВ78", 2021, 2025, 1850000},
        {"Yamaha", "синий", "YM987654", "5678ВЕ78", 2020, 2024, 850000},
        {"HarleyDavidson", "красный", "HD200567", "9012КМ78", 2023, 2026, 2150000},
        {"Honda", "белый", "HN456789", "3456НО78", 2019, 2023, 720000},
        {"HarleyDavidson", "серебристый", "HD300890", "7890РС78", 2022, 2026, 1950000},
    };

    printTitle("Мотоциклы марки \"HarleyDavidson\":");
    int found = 0;
    for (const auto& motorcycle : motorcycles) {
        if (motorcycle.brand == "HarleyDavidson") {
            printMotorcycle(++found, motorcycle);
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

    task08();
    return 0;
}
