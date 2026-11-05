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

// Задача 1. Доход по вкладу
void task01() {
    double amount, rate;
    int months;

    cout << "Вычисление дохода по вкладу\n";
    cout << "Введите исходные данные:\n";

    bool inputOk = readValue("Сумма вклада (руб.) -> ", amount)
        && readValue("Срок вклада (месяцев) -> ", months)
        && readValue("Процентная ставка (годовых) -> ", rate);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (amount <= 0 || months <= 0 || rate < 0) {
        cout << "Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля\n";
    } else {
        double income = amount * rate / 100 * months / 12;
        cout << "-------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Доход: " << income << " руб.\n";
        cout << "Сумма по окончании срока вклада: " << amount + income << " руб.\n";
    }
}

// Задача 2. Минуты в часы и минуты
void task02() {
    int interval;

    bool inputOk = readValue("Введите временной интервал (в минутах) -> ", interval);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (interval < 0) {
        cout << "Ошибка! Интервал не может быть отрицательным\n";
    } else {
        cout << interval << " минут - это " << interval / 60 << " ч. " << interval % 60 << " мин.\n";
    }
}

// Задача 3. Денежный формат
void task03() {
    double value;

    cout << "Преобразование числа в денежный формат\n";

    bool inputOk = readValue("Введите дробное число -> ", value);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (value < 0) {
        cout << "Ошибка! Число не может быть отрицательным\n";
    } else if (value > 1e12) {
        cout << "Ошибка! Слишком большое число\n";
    } else {
        // Считаем в копейках: + 0.5 защищает от ошибок дробных чисел (1.15 * 100 = 114.99...)
        long long total = static_cast<long long>(value * 100 + 0.5);
        cout << setprecision(15) << value << " руб. - это " << total / 100 << " руб. "
             << setw(2) << setfill('0') << total % 100 << setfill(' ') << " коп.\n";
    }
}

// Задача 4. Фунты в килограммы
void task04() {
    double pounds;

    cout << "Пересчет веса из фунтов в килограммы\n";

    bool inputOk = readValue("Введите вес в фунтах и нажмите Enter -> ", pounds);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double GRAMS_IN_POUND = 405.9;

        if (pounds < 0) {
            cout << "Ошибка! Вес не может быть отрицательным\n";
        } else if (pounds > 1e12) {
            cout << "Ошибка! Слишком большое число\n";
        } else {
            // По образцу доли грамма отбрасываются; 1e-6 защищает от ошибок дробных чисел
            long long grams = static_cast<long long>(pounds * GRAMS_IN_POUND + 1e-6);
            cout << setprecision(15) << pounds << " фунт(а/ов) - это " << grams / 1000 << " кг " << grams % 1000 << " гр.\n";
        }
    }
}

// Задача 5. Сопротивление цепи
void task05() {
    double r1, r2;
    int connection;

    cout << "Вычисление сопротивления электрической цепи\n";
    cout << "Введите исходные данные:\n";

    bool inputOk = readValue("Величина первого сопротивления (Ом) -> ", r1)
        && readValue("Величина второго сопротивления (Ом) -> ", r2)
        && readValue("Тип соединения (1-последовательное, 2-параллельное) -> ", connection);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        // Последовательно: R = R1 + R2, параллельно: R = R1 * R2 / (R1 + R2)
        cout << fixed << setprecision(2);
        if (r1 <= 0 || r2 <= 0) {
            cout << "Ошибка! Сопротивление должно быть больше нуля\n";
        } else if (connection == 1) {
            cout << "Сопротивление цепи: " << r1 + r2 << " Ом\n";
        } else if (connection == 2) {
            cout << "Сопротивление цепи: " << r1 * r2 / (r1 + r2) << " Ом\n";
        } else {
            cout << "Ошибка! Неверный тип соединения\n";
        }
    }
}

// Задача 6. Вклад: ставка зависит от суммы (2 варианта)
void task06() {
    double amount;
    int months;

    cout << "Доход\n";

    bool inputOk = readValue("Сумма, руб. -> ", amount)
        && readValue("Срок вклада, мес. -> ", months);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (amount <= 0 || months <= 0) {
        cout << "Ошибка! Сумма и срок должны быть больше нуля\n";
    } else {
        // Сумма ровно 5000 руб. в условии не описана, принята ставка 13%
        int rate = amount < 5000 ? 10 : 13;
        double income = amount * rate / 100 * months / 12;

        cout << "----------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Сумма: " << amount << " руб.\n";
        cout << "Срок вклада: " << months << " мес.\n";
        cout << "Процент годовой: " << rate << "\n";
        cout << "Доход: " << income << " руб.\n";
        cout << "Сумма в конце срока вклада: " << amount + income << " руб.\n";
    }
}

// Задача 7. Вклад: ставка зависит от суммы (3 варианта)
void task07() {
    double amount;
    int months;

    cout << "Доход\n";

    bool inputOk = readValue("Сумма, руб. -> ", amount)
        && readValue("Срок вклада, мес. -> ", months);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (amount <= 0 || months <= 0) {
        cout << "Ошибка! Сумма и срок должны быть больше нуля\n";
    } else {
        // Суммы ровно 5000 и 10 000 руб. в условии не описаны, отнесены к большей ставке
        double rate;
        if (amount < 5000) {
            rate = 9;
        } else if (amount < 10000) {
            rate = 11;
        } else {
            rate = 13;
        }

        double income = amount * rate / 100 * months / 12;

        cout << "------------------------------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Сумма: " << amount << " руб.\n";
        cout << "Срок вклада: " << months << " мес.\n";
        cout << "Процент годовой: " << rate << "\n";
        cout << "Доход: " << income << " руб.\n";
        cout << "Сумма в конце срока вклада: " << amount + income << " руб.\n";
    }
}

// Задача 8. Печать фотографий
void task08() {
    int photoFormat, quantity;

    cout << "Фотографии\n";

    bool inputOk = readValue("Формат (1 – 9х12; 2 – 10х15) -> ", photoFormat)
        && readValue("Количество, шт. -> ", quantity);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double PRICE_9X12 = 2.50;  // в условии цены нет, значение принято самостоятельно
        const double PRICE_10X15 = 3.20;

        if (photoFormat != 1 && photoFormat != 2) {
            cout << "Ошибка! Неверный формат\n";
        } else if (quantity <= 0) {
            cout << "Ошибка! Количество должно быть больше нуля\n";
        } else {
            double price = photoFormat == 1 ? PRICE_9X12 : PRICE_10X15;
            double total = price * quantity;
            // Скидка 5% предоставляется, если фотографий больше 10
            double discount = quantity > 10 ? total * 0.05 : 0;

            cout << "----------------------------\n";
            cout << fixed << setprecision(2);
            cout << "Цена: " << price << " руб.\n";
            cout << "Количество: " << quantity << " шт.\n";
            cout << "Сумма: " << total << " руб.\n";
            cout << "Скидка: " << discount << " руб.\n";
            cout << "К оплате: " << total - discount << " руб.\n";
        }
    }
}

// Задача 9. Ток в электрической цепи
void task09() {
    double power, voltage;

    cout << "Ток в электрической цепи\n";

    bool inputOk = readValue("Мощность, Вт -> ", power)
        && readValue("Напряжение, В -> ", voltage);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (voltage == 0) {
        cout << "Ошибка! Напряжение не должно быть равно нулю\n";
    } else {
        double current = power / voltage + 0.0;  // + 0.0 убирает вывод "-0.00"
        cout << fixed << setprecision(2);
        cout << "Ток: " << current << " А\n";
    }
}

// Задача 10. Площадь кольца
void task10() {
    double ringRadius, holeRadius;

    cout << "Введите исходные данные:\n";

    bool inputOk = readValue("радиус кольца (см) -> ", ringRadius)
        && readValue("радиус отверстия (см) -> ", holeRadius);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        const double PI = 3.14159265358979;

        if (ringRadius <= 0 || holeRadius <= 0) {
            cout << "Ошибка! Радиус должен быть больше нуля\n";
        } else if (holeRadius > ringRadius) {
            cout << "Ошибка! Радиус отверстия больше радиуса кольца\n";
        } else if (holeRadius == ringRadius) {
            cout << "Ошибка! Радиус отверстия равен радиусу кольца\n";
        } else {
            // Площадь кольца: S = пи * (R^2 - r^2)
            double area = PI * (ringRadius * ringRadius - holeRadius * holeRadius);
            cout << fixed << setprecision(2);
            cout << "Площадь кольца: " << area << " кв.см\n";
        }
    }
}

// Задача 11. Минуты и секунды в секунды
void task11() {
    double value;

    bool inputOk = readValue("Введите время (минут.секунд) -> ", value);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (value < 0) {
        cout << "Ошибка! Время не может быть отрицательным\n";
    } else if (value > 1000000) {
        cout << "Ошибка! Слишком большое число\n";
    } else {
        // Целая часть числа - минуты, две цифры после точки - секунды: 2.30 = 2 мин. 30 сек.
        int minutes = static_cast<int>(value);
        int seconds = static_cast<int>((value - minutes) * 100 + 0.5);

        if (seconds > 60) {
            cout << "Ошибка! Число секунд не может быть больше 60\n";
        } else {
            cout << minutes << " мин. " << seconds << " сек. - это "
                 << minutes * 60 + seconds << " сек.\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    cin.get();
}

// Задача 12. Високосный год
void task12() {
    int year;

    cout << "Введите год, например 2000,\n";

    bool inputOk = readValue("и нажмите Enter -> ", year);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        // Високосный год делится на 4, но не на 100, либо делится на 400
        if (year <= 0) {
            cout << "Ошибка! Год должен быть больше нуля\n";
        } else if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            cout << year << " год – високосный\n";
        } else {
            cout << year << " год – не високосный\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    cin.get();
}

// Задача 13. Квадратное уравнение
void task13() {
    double a, b, c;
    string line;

    cout << "Решение квадратного уравнения\n";
    cout << "Введите в одной строке коэффициенты и нажмите Enter -> ";
    getline(cin, line);

    istringstream stream(line);
    char extra;
    bool inputOk = (stream >> a >> b >> c) && !(stream >> extra);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (a == 0) {
        cout << "Ошибка! Коэффициент при второй степени неизвестного не должен быть равен нулю\n";
    } else {
        // Корни: x = (-b +- sqrt(D)) / (2a). Дискриминант сравниваем с допуском,
        // потому что дробные коэффициенты дают его с небольшой погрешностью
        double discriminant = b * b - 4 * a * c;
        cout << fixed << setprecision(3);
        if (discriminant < -1e-9) {
            cout << "Уравнение не имеет действительных корней\n";
        } else if (abs(discriminant) <= 1e-9) {
            double x = -b / (2 * a) + 0.0;  // + 0.0 убирает вывод "-0.000"
            cout << "Корень уравнения: x= " << x << "\n";
        } else {
            double root = sqrt(discriminant);
            double x1 = (-b + root) / (2 * a) + 0.0;
            double x2 = (-b - root) / (2 * a) + 0.0;
            cout << "Корни уравнения: x1= " << x1 << " x2= " << x2 << "\n";
        }
    }
}

// Задача 14. Скидка 10%
void task14() {
    double total;

    cout << "Вычисление стоимости покупки с учетом скидки\n";

    bool inputOk = readValue("Сумма покупки -> ", total);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (total < 0) {
        cout << "Ошибка! Сумма не может быть отрицательной\n";
    } else {
        if (total > 1000) {
            cout << "Вам предоставляется скидка 10%\n";
            total = total * 0.9;
        } else {
            cout << "Скидка не предоставляется\n";
        }

        cout << fixed << setprecision(2);
        cout << "Сумма покупки с учетом скидки: " << total << " руб.\n";
    }
}

// Задача 15. Скидка 3% или 5%
void task15() {
    double total;

    cout << "Вычисление стоимости покупки с учетом скидки\n";

    bool inputOk = readValue("Введите сумму покупки и нажмите Enter -> ", total);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (total < 0) {
        cout << "Ошибка! Сумма не может быть отрицательной\n";
    } else {
        // Сначала проверяем больший порог
        int discount;
        if (total > 1000) {
            discount = 5;
        } else if (total > 500) {
            discount = 3;
        } else {
            discount = 0;
        }

        if (discount > 0) {
            cout << "Вам предоставляется скидка " << discount << "%\n";
            total = total * (100 - discount) / 100;
        } else {
            cout << "Скидка не предоставляется\n";
        }

        cout << fixed << setprecision(2);
        cout << "Сумма с учетом скидки: " << total << " руб.\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

    while (true) {
        // Задачи меняют формат вывода чисел: возвращаем обычный перед каждым запуском
        cout << defaultfloat << setprecision(6);

        cout << "\n=============================================\n";
        cout << " 1. Доход по вкладу\n";
        cout << " 2. Минуты в часы и минуты\n";
        cout << " 3. Денежный формат\n";
        cout << " 4. Фунты в килограммы\n";
        cout << " 5. Сопротивление цепи\n";
        cout << " 6. Вклад: ставка зависит от суммы (2 варианта)\n";
        cout << " 7. Вклад: ставка зависит от суммы (3 варианта)\n";
        cout << " 8. Печать фотографий\n";
        cout << " 9. Ток в электрической цепи\n";
        cout << "10. Площадь кольца\n";
        cout << "11. Минуты и секунды в секунды\n";
        cout << "12. Високосный год\n";
        cout << "13. Квадратное уравнение\n";
        cout << "14. Скидка 10%\n";
        cout << "15. Скидка 3% или 5%\n";
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
            case 15: task15(); break;
            default: cout << "Нет такой задачи\n";
        }
    }

    return 0;
}
