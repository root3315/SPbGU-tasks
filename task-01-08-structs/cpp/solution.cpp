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

struct Date {
    int year;
    int month;
    int day;
};

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

string formatDate(const Date& date) {
    ostringstream out;
    out << setfill('0') << setw(2) << date.day << '.' << setw(2) << date.month << '.' << date.year;
    return out.str();
}

string formatAddress(const Address& address) {
    return address.postalCode + ", " + address.country + ", " + address.region + ", " +
           address.district + ", " + address.city + ", " + address.street +
           ", д. " + address.house + ", кв. " + address.apartment;
}

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

// Задача 1. Футболисты
struct Footballer {
    string surname;
    string name;
    string patronymic;
    string sex;
    string nationality;
    int height;
    int weight;
    Date birthDate;
    string phone;
    string team;
    int teamNumber;
    string position;
    int goals;
    int games;
};

void printFootballer(int number, const Footballer& player) {
    cout << "Футболист #" << number << '\n'
         << "  Фамилия: " << player.surname << '\n'
         << "  Имя: " << player.name << '\n'
         << "  Отчество: " << player.patronymic << '\n'
         << "  Пол: " << player.sex << '\n'
         << "  Национальность: " << player.nationality << '\n'
         << "  Рост: " << player.height << " см\n"
         << "  Вес: " << player.weight << " кг\n"
         << "  Дата рождения: " << formatDate(player.birthDate) << '\n'
         << "  Телефон: " << player.phone << '\n'
         << "  Команда: " << player.team << '\n'
         << "  Номер в команде: " << player.teamNumber << '\n'
         << "  Амплуа: " << player.position << '\n'
         << "  Голы: " << player.goals << '\n'
         << "  Игры: " << player.games << '\n'
         << SEPARATOR << '\n';
}

void task01() {
    const vector<Footballer> footballers{
        {"Смирнов", "Алексей", "Игоревич", "мужской", "русский", 182, 77,
         {1998, 3, 14}, "+7 911 100-20-30", "Зенит", 9, "нападающий", 41, 87},
        {"Кузнецов", "Денис", "Олегович", "мужской", "русский", 188, 83,
         {2003, 11, 2}, "+7 921 200-30-40", "Зенит", 4, "защитник", 2, 34},
        {"Алиев", "Руслан", "Тимурович", "мужской", "азербайджанец", 176, 70,
         {1996, 7, 21}, "+7 903 300-40-50", "Спартак", 10, "полузащитник", 18, 112},
        {"Новиков", "Павел", "Андреевич", "мужской", "русский", 191, 86,
         {2001, 1, 30}, "+7 916 400-50-60", "ЦСКА", 1, "вратарь", 0, 50},
    };

    printTitle("Футболисты, которые провели за свою команду больше 50 матчей:");
    int found = 0;
    for (const auto& player : footballers) {
        if (player.games > 50) {
            printFootballer(++found, player);
        }
    }
    if (found == 0) {
        printNotFound();
    }
}

// Задача 2. Студенты
struct Student {
    string surname;
    string name;
    string patronymic;
    string sex;
    int height;
    int weight;
    Date birthDate;
    Address address;
};

void printStudent(const Student& student) {
    cout << "  Фамилия: " << student.surname << '\n'
         << "  Имя: " << student.name << '\n'
         << "  Отчество: " << student.patronymic << '\n'
         << "  Пол: " << student.sex << '\n'
         << "  Рост: " << student.height << " см\n"
         << "  Вес: " << student.weight << " кг\n"
         << "  Дата рождения: " << formatDate(student.birthDate) << '\n'
         << "  Домашний адрес: " << formatAddress(student.address) << '\n'
         << SEPARATOR << '\n';
}

// true, если первый человек родился позже второго
bool isBornLater(const Date& first, const Date& second) {
    if (first.year != second.year) {
        return first.year > second.year;
    }
    if (first.month != second.month) {
        return first.month > second.month;
    }
    return first.day > second.day;
}

void task02() {
    const vector<Student> students{
        {"Орлова", "Екатерина", "Сергеевна", "женский", 168, 55, {2005, 9, 12},
         {"199034", "Россия", "Ленинградская область", "Василеостровский район",
          "Санкт-Петербург", "Университетская наб.", "7", "12"}},
        {"Васильев", "Илья", "Дмитриевич", "мужской", 180, 72, {2006, 4, 3},
         {"188300", "Россия", "Ленинградская область", "Гатчинский район",
          "Гатчина", "ул. Чкалова", "15", "48"}},
        {"Ким", "Анна", "Викторовна", "женский", 162, 50, {2006, 4, 27},
         {"690091", "Россия", "Приморский край", "Ленинский район",
          "Владивосток", "ул. Светланская", "21", "5"}},
        {"Попов", "Максим", "Петрович", "мужской", 185, 80, {2004, 12, 30},
         {"150000", "Россия", "Ярославская область", "Кировский район",
          "Ярославль", "ул. Свободы", "3", "101"}},
    };

    const Student* youngest = &students[0];
    for (const auto& student : students) {
        if (isBornLater(student.birthDate, youngest->birthDate)) {
            youngest = &student;
        }
    }

    printTitle("Самый молодой студент:");
    printStudent(*youngest);
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

// Задача 6. Баскетболисты
struct BasketballPlayer {
    string surname;
    string name;
    string patronymic;
    string sex;
    string nationality;
    int height;
    int weight;
    Date birthDate;
    string phone;
    string team;
    int teamNumber;
    string position;
    int points;
    int games;
};

void printBasketballPlayer(int number, const BasketballPlayer& player) {
    cout << "Баскетболист #" << number << '\n'
         << "  Фамилия: " << player.surname << '\n'
         << "  Имя: " << player.name << '\n'
         << "  Отчество: " << player.patronymic << '\n'
         << "  Пол: " << player.sex << '\n'
         << "  Национальность: " << player.nationality << '\n'
         << "  Рост: " << player.height << " см\n"
         << "  Вес: " << player.weight << " кг\n"
         << "  Дата рождения: " << formatDate(player.birthDate) << '\n'
         << "  Телефон: " << player.phone << '\n'
         << "  Команда: " << player.team << '\n'
         << "  Номер в команде: " << player.teamNumber << '\n'
         << "  Амплуа: " << player.position << '\n'
         << "  Очки: " << player.points << '\n'
         << "  Игры: " << player.games << '\n'
         << SEPARATOR << '\n';
}

void task06() {
    const vector<BasketballPlayer> players{
        {"Морозов", "Артём", "Сергеевич", "мужской", "русский", 205, 102,
         {1999, 6, 8}, "+7 911 500-60-70", "Зенит", 23, "центровой", 412, 38},
        {"Лебедев", "Никита", "Ильич", "мужской", "русский", 191, 85,
         {2004, 2, 17}, "+7 921 600-70-80", "Зенит", 7, "разыгрывающий", 96, 21},
        {"Ахмедов", "Тимур", "Рустамович", "мужской", "татарин", 198, 94,
         {2000, 10, 5}, "+7 917 700-80-90", "УНИКС", 11, "форвард", 150, 30},
        {"Григорьев", "Олег", "Петрович", "мужской", "русский", 201, 98,
         {1997, 12, 19}, "+7 926 800-90-00", "ЦСКА", 14, "форвард", 287, 42},
    };

    printTitle("Баскетболисты, которые набрали за свою команду больше 150 очков:");
    int found = 0;
    for (const auto& player : players) {
        if (player.points > 150) {
            printBasketballPlayer(++found, player);
        }
    }
    if (found == 0) {
        printNotFound();
    }
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

// Номер задачи из строки; -1, если в строке не одно целое число
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
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    while (true) {
        cout << "\n=============================================\n";
        cout << " 1. Футболисты\n";
        cout << " 2. Студенты\n";
        cout << " 3. Международные компании\n";
        cout << " 4. Зоопарки\n";
        cout << " 5. Мультфильмы\n";
        cout << " 6. Баскетболисты\n";
        cout << " 7. Области\n";
        cout << " 8. Мотоциклы\n";
        cout << " 0. Выход\n";
        cout << "=============================================\n";

        cout << "Номер задачи -> ";
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
            default: cout << "Нет такой задачи\n";
        }
    }

    return 0;
}
