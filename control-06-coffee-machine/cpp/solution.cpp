// Текущий контроль. Задание 6: класс «Кофейный автомат»
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int WATER_CAPACITY = 2000;  // мл
const int BEANS_CAPACITY = 500;   // г

struct Drink {
    string name;
    int water;  // мл
    int beans;  // г
};

const Drink DRINKS[] = {
    {"Эспрессо", 30, 9},
    {"Двойной эспрессо", 60, 18},
    {"Американо", 150, 9},
};
const int DRINK_COUNT = sizeof(DRINKS) / sizeof(DRINKS[0]);

class CoffeeMachine {
public:
    CoffeeMachine(int waterCapacity, int beansCapacity)
        : waterCapacity_(waterCapacity), beansCapacity_(beansCapacity),
          water_(waterCapacity), beans_(beansCapacity) {}

    // Доливает воду, но не больше объема бака. Возвращает, сколько долито
    int refillWater(int amount) {
        int added = min(amount, waterCapacity_ - water_);
        water_ += added;
        return added;
    }

    // Досыпает зерна, но не больше объема контейнера. Возвращает, сколько добавлено
    int refillBeans(int amount) {
        int added = min(amount, beansCapacity_ - beans_);
        beans_ += added;
        return added;
    }

    // Чего не хватает на напиток; пустая строка, если хватает всего
    string missingFor(const Drink& drink) const {
        bool noWater = water_ < drink.water;
        bool noBeans = beans_ < drink.beans;
        if (noWater && noBeans) {
            return "воды и зерен";
        }
        if (noWater) {
            return "воды";
        }
        if (noBeans) {
            return "зерен";
        }
        return "";
    }

    // Готовит напиток, если хватает ресурсов. Возвращает true при успехе
    bool makeDrink(const Drink& drink) {
        if (!missingFor(drink).empty()) {
            return false;
        }
        water_ -= drink.water;
        beans_ -= drink.beans;
        return true;
    }

    string remaining() const {
        ostringstream out;
        out << "Вода: " << water_ << " из " << waterCapacity_ << " мл\n"
            << "Зерна: " << beans_ << " из " << beansCapacity_ << " г";
        return out.str();
    }

private:
    int waterCapacity_;
    int beansCapacity_;
    int water_;
    int beans_;
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

void makeDrinkMenu(CoffeeMachine& machine) {
    cout << "Напиток:\n";
    for (int i = 0; i < DRINK_COUNT; ++i) {
        cout << i + 1 << " – " << DRINKS[i].name << " (" << DRINKS[i].water
             << " мл, " << DRINKS[i].beans << " г)\n";
    }

    int choice;
    if (!readValue("Ваш выбор –> ", choice)) {
        cout << "Ошибка! Неверный формат числа\n";
        return;
    }
    if (choice < 1 || choice > DRINK_COUNT) {
        cout << "Ошибка! Неверный выбор напитка\n";
        return;
    }

    const Drink& drink = DRINKS[choice - 1];
    string missing = machine.missingFor(drink);
    if (!missing.empty()) {
        cout << "Не хватает " << missing << ", заправьте автомат\n";
    } else {
        machine.makeDrink(drink);
        cout << "Готово: " << drink.name << '\n';
    }
    cout << machine.remaining() << '\n';
}

void refillMenu(CoffeeMachine& machine) {
    int water, beans;
    bool inputOk = readValue("Сколько воды долить, мл –> ", water)
        && readValue("Сколько зерен досыпать, г –> ", beans);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
        return;
    }
    if (water < 0 || beans < 0) {
        cout << "Ошибка! Количество не может быть отрицательным\n";
        return;
    }

    int addedWater = machine.refillWater(water);
    int addedBeans = machine.refillBeans(beans);
    cout << "Долито воды: " << addedWater << " мл, досыпано зерен: "
         << addedBeans << " г\n";
    cout << machine.remaining() << '\n';
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    CoffeeMachine machine(WATER_CAPACITY, BEANS_CAPACITY);
    cout << "Кофейный автомат\n";

    while (true) {
        cout << "-----------------------------\n";
        cout << "1 – Приготовить напиток\n";
        cout << "2 – Заправить\n";
        cout << "3 – Остаток\n";
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
        } else if (choice == 1) {
            makeDrinkMenu(machine);
        } else if (choice == 2) {
            refillMenu(machine);
        } else if (choice == 3) {
            cout << machine.remaining() << '\n';
        } else {
            cout << "Ошибка! Неверный выбор\n";
        }
    }

    return 0;
}
