#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const string LINE(56, '=');
const string SEPARATOR(56, '-');

struct Address {
    string postalCode;
    string country;
    string region;
    string district;
    string city;
    string street;
    string house;
    string apartment;
};

string formatAddress(const Address& address) {
    return address.postalCode + ", " + address.country + ", " + address.region + ", " +
           address.district + ", " + address.city + ", " + address.street +
           ", д. " + address.house + ", кв. " + address.apartment;
}

void printTitle(const string& title) {
    cout << LINE << '\n' << title << '\n' << LINE << '\n';
}

void printNotFound() {
    cout << "Подходящих записей нет\n";
}

// Задача 3. Международные компании
struct Company {
    string name;
    string website;
    Address headOffice;
    int yearsOnMarket;
    int employees;
    int europeBranches;
};

void printCompany(int number, const Company& company) {
    cout << "Компания #" << number << '\n'
         << "  Название: " << company.name << '\n'
         << "  Сайт: " << company.website << '\n'
         << "  Адрес главного офиса: " << formatAddress(company.headOffice) << '\n'
         << "  Лет на мировом рынке: " << company.yearsOnMarket << '\n'
         << "  Сотрудников: " << company.employees << '\n'
         << "  Филиалов в Европе: " << company.europeBranches << '\n'
         << SEPARATOR << '\n';
}

void task03() {
    const vector<Company> companies{
        {"Nordic Logistics", "https://nordic-logistics.example",
         {"10115", "Германия", "Берлин", "Митте", "Берлин", "Friedrichstrasse", "120", "4"},
         35, 24500, 18},
        {"Volga Software", "https://volga-software.example",
         {"420111", "Россия", "Республика Татарстан", "Вахитовский район",
          "Казань", "ул. Баумана", "44", "3"},
         12, 3200, 2},
        {"Atlantic Foods", "https://atlantic-foods.example",
         {"75008", "Франция", "Иль-де-Франс", "8-й округ", "Париж", "Rue de Rivoli", "15", "2"},
         58, 10000, 27},
        {"Baltic Energy", "https://baltic-energy.example",
         {"00100", "Финляндия", "Уусимаа", "Центр", "Хельсинки", "Mannerheimintie", "8", "11"},
         41, 15800, 9},
    };

    printTitle("Международные компании, в которых больше 10000 сотрудников:");
    int found = 0;
    for (const auto& company : companies) {
        if (company.employees > 10000) {
            printCompany(++found, company);
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

    task03();
    return 0;
}
