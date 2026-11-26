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

void printTitle(const string& title) {
    cout << LINE << '\n' << title << '\n' << LINE << '\n';
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

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    task02();
    return 0;
}
