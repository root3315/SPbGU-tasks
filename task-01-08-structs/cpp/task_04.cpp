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

// Задача 4. Зоопарки
struct Species {
    string name;
    int count;
};

struct Zoo {
    string name;
    vector<Species> species;
    Address address;
    int totalAnimals;
    int workers;
};

const string TIGER = "уссурийский тигр";

void printZoo(int number, const Zoo& zoo) {
    cout << "Зоопарк #" << number << '\n'
         << "  Название: " << zoo.name << '\n'
         << "  Животные:\n";
    for (const auto& animal : zoo.species) {
        cout << "    " << animal.name << ": " << animal.count << '\n';
    }
    cout << "  Адрес: " << formatAddress(zoo.address) << '\n'
         << "  Всего животных: " << zoo.totalAnimals << '\n'
         << "  Работников: " << zoo.workers << '\n'
         << SEPARATOR << '\n';
}

bool hasTigers(const Zoo& zoo) {
    for (const auto& animal : zoo.species) {
        if (animal.name == TIGER && animal.count > 0) {
            return true;
        }
    }
    return false;
}

void task04() {
    const vector<Zoo> zoos{
        {"Северный зоопарк",
         {{"уссурийский тигр", 3}, {"бурый медведь", 2}, {"пингвин", 12}},
         {"197198", "Россия", "Ленинградская область", "Петроградский район",
          "Санкт-Петербург", "Александровский парк", "1", "1"},
         1200, 210},
        {"Южный зоопарк",
         {{"жираф", 4}, {"зебра", 6}, {"лев", 2}},
         {"344002", "Россия", "Ростовская область", "Ленинский район",
          "Ростов-на-Дону", "ул. Зоологическая", "3", "1"},
         850, 140},
        {"Приморский сафари-парк",
         {{"уссурийский тигр", 5}, {"дальневосточный леопард", 2}},
         {"692481", "Россия", "Приморский край", "Шкотовский район",
          "Шкотово", "ул. Лесная", "10", "1"},
         400, 60},
        {"Городской зоопарк",
         {{"уссурийский тигр", 0}, {"волк", 5}},
         {"620075", "Россия", "Свердловская область", "Кировский район",
          "Екатеринбург", "ул. Мамина-Сибиряка", "189", "1"},
         300, 45},
    };

    printTitle("Зоопарки, в которых есть уссурийские тигры:");
    int found = 0;
    for (const auto& zoo : zoos) {
        if (hasTigers(zoo)) {
            printZoo(++found, zoo);
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

    task04();
    return 0;
}
