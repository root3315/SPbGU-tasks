#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

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

// Задача 1. Печать фотографий
void task01() {
    int choice, quantity;

    cout << "Фото\n";
    cout << "Размер:\n";
    cout << "1 – 9х12\n";
    cout << "2 – 10х15\n";
    cout << "3 – 18х24\n";

    bool inputOk = readValue("Ваш выбор –> ", choice)
        && readValue("Количество –> ", quantity);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double PRICES[] = {3.50, 5.00, 10.00};  // цены из присланного образца

        if (choice < 1 || choice > 3) {
            cout << "Ошибка! Неверный выбор размера\n";
        } else if (quantity <= 0) {
            cout << "Ошибка! Количество должно быть больше нуля\n";
        } else if (quantity > 1000000) {
            cout << "Ошибка! Слишком большое количество\n";
        } else {
            double price = PRICES[choice - 1];
            double total = price * quantity;
            // Скидка 10% предоставляется, если фотографий больше 10
            double discount = quantity > 10 ? total * 0.10 : 0;

            cout << "-----------------------------\n";
            cout << fixed << setprecision(2);
            cout << "Цена: " << price << " руб.\n";
            cout << "Количество: " << quantity << " шт.\n";
            cout << "Сумма: " << total << " руб.\n";
            cout << "Скидка: " << discount << " руб.\n";
            cout << "К оплате: " << total - discount << " руб.\n";
        }
    }
}

// Задача 2. Заправка автомобиля
void task02() {
    int choice;
    double liters;

    cout << "Бензин\n";
    cout << "Марка бензина:\n";
    cout << "1 – 92\n";
    cout << "2 – 95\n";
    cout << "3 – 98\n";
    cout << "4 – DT\n";

    bool inputOk = readValue("Ваш выбор –> ", choice)
        && readValue("Литров –> ", liters);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        // В условии есть только итог для марки 95 (20.30 руб.), остальные цены приняты самостоятельно
        const double PRICES[] = {19.50, 20.30, 22.10, 18.70};

        if (choice < 1 || choice > 4) {
            cout << "Ошибка! Неверный выбор марки\n";
        } else if (liters <= 0) {
            cout << "Ошибка! Количество литров должно быть больше нуля\n";
        } else if (liters > 1000000) {
            cout << "Ошибка! Слишком большое количество\n";
        } else {
            double price = PRICES[choice - 1];
            // Округляем до копеек; 1e-6 защищает от ошибок дробных чисел (18.70 * 0.25 = 4.675)
            double total = floor(price * liters * 100 + 0.5 + 1e-6) / 100;

            cout << "-----------------------------\n";
            cout << fixed << setprecision(2) << "Цена за литр: " << price << " руб.\n";
            cout << defaultfloat << setprecision(15) << "Литров: " << liters << "\n";
            cout << fixed << setprecision(2) << "К оплате: " << total << " руб.\n";
        }
    }
}

// Задача 3. Таблица квадратов
void task03() {
    cout << "Таблица квадратов\n";
    cout << "--------------\n";
    cout << "Число Квадрат\n";
    cout << "--------------\n";
    for (int number = 1; number <= 10; number++) {
        cout << setw(3) << number << setw(9) << number * number << "\n";
    }
    cout << "--------------\n";
}

// Задача 4. Таблица квадратов нечетных чисел
void task04() {
    cout << "Таблица квадратов нечетных чисел\n";
    cout << "--------------\n";
    cout << "Число Квадрат\n";
    cout << "--------------\n";
    for (int number = 1; number <= 9; number += 2) {
        cout << setw(3) << number << setw(9) << number * number << "\n";
    }
    cout << "--------------\n";
}

// Задача 5. Скорость свободного падения
void task05() {
    const double G = 9.8;      // ускорение свободного падения, м/с2
    const double STEP = 0.5;   // шаг по времени, с

    cout << "-----------------------\n";
    cout << "Время, с Скорость, м/с\n";
    cout << "-----------------------\n";
    cout << fixed;
    // Время считаем через номер шага: так дробная ошибка не накапливается
    for (int i = 0; i < 7; i++) {
        double time = i * STEP;
        cout << setw(5) << setprecision(1) << time
             << setw(12) << setprecision(2) << G * time << "\n";
    }
    cout << "-----------------------\n";
}

// Задача 6. Платежи по кредиту
void task06() {
    double amount, rate;
    int months;

    bool inputOk = readValue("Сумма кредита (руб.) -> ", amount)
        && readValue("Срок (мес.) -> ", months)
        && readValue("Процентная ставка (годовых) -> ", rate);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (amount <= 0 || months <= 0 || rate < 0) {
        cout << "Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля\n";
    } else if (amount > 10000000) {
        cout << "Ошибка! Слишком большая сумма\n";
    } else if (rate > 100) {
        cout << "Ошибка! Слишком большая ставка\n";
    } else if (months > 1200) {
        cout << "Ошибка! Слишком большой срок\n";
    } else {
        double share = amount / months;  // равная доля долга, возвращаемая каждый месяц
        double totalInterest = 0;

        cout << "---------------------------------------\n";
        cout << "           Долг     Процент      Платеж\n";
        cout << "---------------------------------------\n";
        cout << fixed << setprecision(2);
        for (int month = 1; month <= months; month++) {
            // Проценты начисляются на остаток долга за один месяц
            double debt = amount - share * (month - 1);
            double interest = debt * rate / 100 / 12;
            totalInterest += interest;
            cout << setw(3) << month << setw(12) << debt
                 << setw(12) << interest << setw(12) << share + interest << "\n";
        }
        cout << "---------------------------------------\n";
        cout << "Всего процентов: " << totalInterest << "\n";
    }
}

// Задача 7. Цельсий и Фаренгейт
void task07() {
    double t1, t2, dt;

    bool inputOk = readValue("t1 –> ", t1)
        && readValue("t2 –> ", t2)
        && readValue("dt –> ", dt);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (dt <= 0) {
        cout << "Ошибка! Шаг должен быть больше нуля\n";
    } else if (t1 > t2) {
        cout << "Ошибка! Начальная температура больше конечной\n";
    } else if ((t2 - t1) / dt > 10000) {
        cout << "Ошибка! Слишком много строк в таблице\n";
    } else {
        // Температуру считаем через номер шага: так дробная ошибка не накапливается.
        // 1e-9 нужно, чтобы последний шаг не потерялся из-за такой же ошибки в делении
        int steps = static_cast<int>((t2 - t1) / dt + 1e-9);

        cout << "----------------\n";
        cout << "    C         F\n";
        cout << "----------------\n";
        cout << fixed << setprecision(2);
        for (int i = 0; i <= steps; i++) {
            // Округление убирает вывод "-0.00"
            double celsius = round((t1 + i * dt) * 1e9) / 1e9 + 0.0;
            double fahrenheit = 9.0 / 5 * celsius + 32;
            cout << setw(6) << celsius << setw(10) << fahrenheit << "\n";
        }
    }
}

// Задача 8. Сумма первых n чисел
void task08() {
    int count;

    cout << "Сумма положительных чисел\n";

    bool inputOk = readValue("Введите количество суммируемых чисел -> ", count);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (count <= 0) {
        cout << "Ошибка! Количество должно быть больше нуля\n";
    } else if (count > 1000000) {
        cout << "Ошибка! Слишком большое количество\n";
    } else {
        long long total = 0;
        for (int number = 1; number <= count; number++) {
            total += number;
        }
        cout << "Сумма первых " << count << " положительных чисел равна " << total << "\n";
    }
}

// Задача 9. Сумма первых n четных чисел
void task09() {
    int count;

    cout << "Вычисление суммы четных положительных чисел\n";
    cout << "Введите количество суммируемых чисел и нажмите Enter\n";

    bool inputOk = readValue("-> ", count);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (count <= 0) {
        cout << "Ошибка! Количество должно быть больше нуля\n";
    } else if (count > 1000000) {
        cout << "Ошибка! Слишком большое количество\n";
    } else {
        long long total = 0;
        for (int i = 1; i <= count; i++) {
            total += 2 * i;
        }
        cout << "Сумма первых " << count << " положительных четных чисел равна " << total << "\n";
    }
}

// Задача 10. Сумма ряда 1, 3, 5, 7
void task10() {
    int count;

    cout << "Вычисление частичной суммы ряда: 1,3,5,7, ...\n";

    bool inputOk = readValue("Введите количество суммируемых членов ряда -> ", count);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (count <= 0) {
        cout << "Ошибка! Количество должно быть больше нуля\n";
    } else if (count > 1000000) {
        cout << "Ошибка! Слишком большое количество\n";
    } else {
        long long total = 0;
        for (int i = 1; i <= count; i++) {
            total += 2 * i - 1;
        }
        cout << "Сумма первых " << count << " членов ряда равна " << total << "\n";
    }
}

// Задача 11. Таблица степеней двойки
void task11() {
    cout << "Таблица степеней двойки\n\n";
    int power = 1;
    for (int exponent = 0; exponent <= 10; exponent++) {
        cout << setw(3) << exponent << setw(7) << power << "\n";
        power *= 2;
    }
}

// Задача 12. Факториал
void task12() {
    int number;

    cout << "Вычисление факториала\n";
    cout << "Введите число, факториал которого надо вычислить\n";

    bool inputOk = readValue("-> ", number);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number < 0) {
        cout << "Ошибка! Число не может быть отрицательным\n";
    } else if (number > 20) {  // 21! уже не помещается в long long
        cout << "Ошибка! Слишком большое число\n";
    } else {
        long long factorial = 1;
        for (int i = 2; i <= number; i++) {
            factorial *= i;
        }
        cout << "Факториал " << number << " равен " << factorial << "\n";
    }
}

// Задача 13. Среднее арифметическое пяти чисел
void task13() {
    const int COUNT = 5;
    double total = 0;
    bool inputOk = true;

    cout << "Среднее арифметическое последовательности дробных чисел.\n";
    cout << "После ввода каждого числа нажимайте Enter\n";
    for (int i = 0; i < COUNT && inputOk; i++) {
        double number = 0;
        inputOk = readValue("-> ", number);
        total += number;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        cout << fixed << setprecision(2);
        cout << "Среднее арифметическое введенной последовательности: " << total / COUNT << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

// Задача 14. Обработка последовательности
void task14() {
    int count = 0;
    double total = 0, minimum = 0, maximum = 0;

    cout << "Обработка последовательности дробных чисел.\n";
    bool inputOk = readValue("Введите количество чисел последовательности -> ", count);

    if (inputOk && count > 0 && count <= 1000) {
        cout << "Вводите последовательность. После ввода каждого числа нажимайте Enter\n";
        for (int i = 0; i < count && inputOk; i++) {
            double number = 0;
            inputOk = readValue("-> ", number);

            total += number;
            // Первое число сразу считаем и минимумом, и максимумом
            if (i == 0 || number < minimum) {
                minimum = number;
            }
            if (i == 0 || number > maximum) {
                maximum = number;
            }
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (count <= 0) {
        cout << "Ошибка! Количество должно быть больше нуля\n";
    } else if (count > 1000) {
        cout << "Ошибка! Слишком большое количество\n";
    } else {
        cout << "Количество чисел: " << count << "\n";
        cout << fixed << setprecision(2) << "Среднее арифметическое: " << total / count << "\n";
        cout << defaultfloat << setprecision(15);
        cout << "Минимальное число: " << minimum << "\n";
        cout << "Максимальное число: " << maximum << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    while (true) {
        // Задачи меняют формат вывода чисел: возвращаем обычный перед каждым запуском
        cout << defaultfloat << setprecision(6);

        cout << "\n=============================================\n";
        cout << " 1. Печать фотографий\n";
        cout << " 2. Заправка автомобиля\n";
        cout << " 3. Таблица квадратов\n";
        cout << " 4. Таблица квадратов нечетных чисел\n";
        cout << " 5. Скорость свободного падения\n";
        cout << " 6. Платежи по кредиту\n";
        cout << " 7. Цельсий и Фаренгейт\n";
        cout << " 8. Сумма первых n чисел\n";
        cout << " 9. Сумма первых n четных чисел\n";
        cout << "10. Сумма ряда 1, 3, 5, 7\n";
        cout << "11. Таблица степеней двойки\n";
        cout << "12. Факториал\n";
        cout << "13. Среднее арифметическое пяти чисел\n";
        cout << "14. Обработка последовательности\n";
        cout << " 0. Выход\n";
        cout << "=============================================\n";
        int choice = -1;
        bool inputOk = readValue("Номер задачи -> ", choice);
        if (cin.eof() || (inputOk && choice == 0)) {
            break;
        }

        if (!inputOk) {
            choice = -1;
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
            case 9: task09(); break;
            case 10: task10(); break;
            case 11: task11(); break;
            case 12: task12(); break;
            case 13: task13(); break;
            case 14: task14(); break;
            default: cout << "Нет такой задачи\n";
        }
    }

    return 0;
}
