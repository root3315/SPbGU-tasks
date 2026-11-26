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

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    task06();
    return 0;
}
