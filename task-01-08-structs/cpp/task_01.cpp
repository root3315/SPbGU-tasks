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

string formatDate(const Date& date) {
    ostringstream out;
    out << setfill('0') << setw(2) << date.day << '.' << setw(2) << date.month << '.' << date.year;
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

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    task01();
    return 0;
}
