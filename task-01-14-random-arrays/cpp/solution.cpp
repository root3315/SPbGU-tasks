#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Один генератор случайных чисел на всю программу
mt19937 generator(random_device{}());

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

// Показывает подсказку и читает целые числа из одной строки; false, если в строке не только числа
bool readNumbersLine(const string& prompt, vector<long long>& numbers) {
    cout << prompt;

    string line;
    getline(cin, line);

    // Каждое слово строки должно целиком быть целым числом
    istringstream stream(line);
    string word;
    while (stream >> word) {
        istringstream wordStream(word);
        long long number;
        char extra;
        if (!(wordStream >> number) || (wordStream >> extra)) {
            return false;
        }
        numbers.push_back(number);
    }
    return true;
}

// Задача 1. Десять случайных чисел
void task01() {
    const int COUNT = 10;
    uniform_int_distribution<int> distribution(1, 10);
    int total = 0;

    cout << "Случайные числа\n";
    for (int i = 0; i < COUNT; i++) {
        int number = distribution(generator);
        cout << number << "\n";
        total += number;
    }
    cout << fixed << setprecision(2) << "Сред. арифм.: " << static_cast<double>(total) / COUNT << "\n";
}

// Задача 2. Три случайные последовательности
void task02() {
    const int COUNT = 10;
    uniform_int_distribution<int> distribution(1, 10);

    cout << "Случайные числа\n";
    cout << fixed << setprecision(2);
    for (int row = 0; row < 3; row++) {
        int total = 0;
        for (int i = 0; i < COUNT; i++) {
            int number = distribution(generator);
            cout << number << " ";
            total += number;
        }
        cout << "сред. арифм.: " << static_cast<double>(total) / COUNT << "\n";
    }
}

// Задача 3. Стоимость яблок
void task03() {
    double price;

    cout << "Введите цену одного килограмма и нажмите Enter\n";
    cout << "(копейки от рублей отделяйте точкой)\n";

    bool inputOk = readValue("-> ", price) && isfinite(price);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (price <= 0) {
        cout << "Ошибка! Цена должна быть больше нуля\n";
    } else if (price > 1000000) {
        cout << "Ошибка! Слишком большая цена\n";
    } else {
        cout << "-------------------------\n";
        cout << "Вес, гр.  Стоимость, руб.\n";
        cout << "-------------------------\n";
        cout << fixed << setprecision(2);
        for (int weight = 100; weight <= 1000; weight += 100) {
            // Округляем до копеек; 1e-6 защищает от ошибок дробных чисел
            long long kopecks = static_cast<long long>(price * weight / 10 + 0.5 + 1e-6);
            cout << setw(8) << weight << setw(17) << kopecks / 100.0 << "\n";
        }
        cout << "-------------------------\n";
    }
}

// Задача 4. Цельсий и Фаренгейт
void task04() {
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

// Задача 5. Сумма и среднее до нуля
void task05() {
    int count = 0;
    double number = 0, total = 0;
    bool inputOk = true;

    cout << "Вычисление среднего арифметического последовательности положительных чисел.\n";
    cout << "Вводите после стрелки числа. Для завершения ввода введите ноль.\n";
    while (true) {
        inputOk = readValue("> ", number) && isfinite(number);
        if (!inputOk || number <= 0) {
            break;
        }
        count++;
        total += number;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number < 0) {
        cout << "Ошибка! Число должно быть положительным\n";
    } else if (count == 0) {
        cout << "Не введено ни одного числа\n";
    } else {
        cout << "Введено чисел: " << count << "\n";
        cout << defaultfloat << setprecision(15) << "Сумма чисел: " << total << "\n";
        cout << fixed << setprecision(2) << "Среднее арифметическое: " << total / count << "\n";
    }
}

// Задача 6. Максимальное число
void task06() {
    double number = 0;
    double maximum = 0;  // все числа положительные, поэтому любое из них больше нуля
    bool inputOk = true;

    cout << "Определение максимального числа из последовательности положительных чисел.\n";
    cout << "Вводите числа после стрелки. Для завершения ввода введите ноль.\n";
    while (true) {
        inputOk = readValue("> ", number) && isfinite(number);
        if (!inputOk || number <= 0) {
            break;
        }
        if (number > maximum) {
            maximum = number;
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number < 0) {
        cout << "Ошибка! Число должно быть положительным\n";
    } else if (maximum == 0) {
        cout << "Не введено ни одного числа\n";
    } else {
        cout << defaultfloat << setprecision(15) << "Максимальное число: " << maximum << "\n";
    }
}

// Задача 7. Минимальное число
void task07() {
    int count = 0;
    double number = 0, minimum = 0;
    bool inputOk = true;

    cout << "Определение минимального числа в последовательности положительных чисел.\n";
    cout << "Вводите после стрелки числа. Для завершения ввода введите ноль.\n";
    while (true) {
        inputOk = readValue("> ", number) && isfinite(number);
        if (!inputOk || number <= 0) {
            break;
        }
        // Первое число сразу считаем минимумом
        if (count == 0 || number < minimum) {
            minimum = number;
        }
        count++;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number < 0) {
        cout << "Ошибка! Число должно быть положительным\n";
    } else if (count == 0) {
        cout << "Не введено ни одного числа\n";
    } else {
        cout << defaultfloat << setprecision(15) << "Минимальное число: " << minimum << "\n";
    }
}

// Задача 8. Простое число
void task08() {
    const long long LIMIT = 1000000000000LL;
    long long number;

    cout << "Введите целое число и нажмите Enter\n";
    bool inputOk = readValue("> ", number);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (number > LIMIT || number < -LIMIT) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        // Числа меньше 2 простыми не считаются; делители ищем до корня из числа
        bool isPrime = number >= 2;
        for (long long divisor = 2; isPrime && divisor * divisor <= number; divisor++) {
            if (number % divisor == 0) {
                isPrime = false;
            }
        }

        if (isPrime) {
            cout << number << " - простое число.\n";
        } else {
            cout << number << " - не простое число.\n";
        }
    }
}

// Задача 9. Угадай число
void task09() {
    uniform_int_distribution<int> distribution(1, 10);
    int secret = distribution(generator);
    int attemptsLeft = 5;
    string prompt = "> ";
    bool won = false;

    cout << "Игра \"Угадай число\".\n";
    cout << "Компьютер \"задумал\" число от 1 до 10.\n";
    cout << "Угадайте его за пять попыток.\n";
    cout << "Введите число и нажмите Enter\n";
    while (attemptsLeft > 0) {
        // Ошибка ввода попытку не тратит
        int guess;
        if (!readValue(prompt, guess)) {
            if (cin.eof()) {
                return;  // ввод закрыт: продолжать игру нельзя
            }
            cout << "Ошибка! Неверный формат числа\n";
            continue;
        }
        if (guess < 1 || guess > 10) {
            cout << "Ошибка! Число должно быть от 1 до 10\n";
            continue;
        }

        if (guess == secret) {
            won = true;
            break;
        }
        attemptsLeft--;
        cout << "Нет.\n";
        prompt = "-> ";
    }

    if (won) {
        cout << "Вы выиграли! Поздравляю!\n";
    } else {
        cout << "Вы проиграли. Компьютер задумал число " << secret << ".\n";
    }
}

// Задача 10. Число Пи
void task10() {
    double eps;

    bool inputOk = readValue("Задайте точность вычисления Пи -> ", eps) && isfinite(eps);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (eps <= 0 || eps >= 1) {
        cout << "Ошибка! Точность должна быть больше нуля и меньше единицы\n";
    } else if (eps < 1e-6) {
        cout << "Ошибка! Точность не может быть меньше 0.000001\n";
    } else {
        // Ряд 1 - 1/3 + 1/5 - ... сходится к Пи/4. Суммируем, пока
        // только что прибавленный член не станет меньше точности
        double total = 0;
        long long count = 0;
        int sign = 1;
        while (true) {
            count++;
            double term = 1.0 / (2 * count - 1);
            total += sign * term;
            sign = -sign;
            if (term < eps) {
                break;
            }
        }

        cout << fixed << setprecision(6);
        cout << "Значение числа Пи с точностью " << eps << " равно " << 4 * total << "\n";
        cout << "Просуммировано " << count << " членов ряда.\n";
    }
}

// Задача 11. Массив из семи чисел
void task11() {
    const int SIZE = 7;
    const long long LIMIT = 1000000000;
    long long numbers[SIZE] = {};
    bool inputOk = true;

    cout << "Ввод массива целых чисел\n";
    cout << "После ввода каждого числа нажмите Enter\n";
    for (int i = 0; i < SIZE && inputOk; i++) {
        inputOk = readValue("a[" + to_string(i) + "] -> ", numbers[i]);
    }

    bool inRange = true;
    long long total = 0;
    for (int i = 0; i < SIZE; i++) {
        if (numbers[i] > LIMIT || numbers[i] < -LIMIT) {
            inRange = false;
        }
        total += numbers[i];
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (!inRange) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        cout << "Массив:";
        for (int i = 0; i < SIZE; i++) {
            cout << " " << numbers[i];
        }
        cout << "\n";
        cout << fixed << setprecision(2);
        cout << "Среднее арифметическое: " << static_cast<double>(total) / SIZE << "\n";
    }
}

// Задача 12. Ненулевые элементы
void task12() {
    const int SIZE = 5;
    double numbers[SIZE] = {};
    bool inputOk = true;

    cout << "Ввод массива дробных чисел\n";
    cout << "После ввода каждого числа нажмите Enter\n";
    for (int i = 0; i < SIZE && inputOk; i++) {
        inputOk = readValue("a[" + to_string(i + 1) + "] -> ", numbers[i]) && isfinite(numbers[i]);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        int nonzero = 0;
        for (int i = 0; i < SIZE; i++) {
            if (numbers[i] != 0) {
                nonzero++;
            }
        }
        cout << "------------------------\n";
        cout << "Ненулевых элементов: " << nonzero << "\n";
    }
}

// Задача 13. Минимальный элемент массива
void task13() {
    const size_t SIZE = 5;
    const long long LIMIT = 1000000000;
    vector<long long> numbers;

    cout << "Поиск минимального элемента массива\n";
    cout << "Введите в одной строке " << SIZE << " целых чисел и нажмите Enter\n";
    bool inputOk = readNumbersLine("-> ", numbers);

    bool inRange = true;
    long long minimum = numbers.empty() ? 0 : numbers[0];
    for (long long number : numbers) {
        if (number > LIMIT || number < -LIMIT) {
            inRange = false;
        }
        if (number < minimum) {
            minimum = number;
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (numbers.size() != SIZE) {
        cout << "Ошибка! Нужно ввести ровно " << SIZE << " чисел\n";
    } else if (!inRange) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        cout << "Минимальный элемент массива: " << minimum << "\n";
    }
}

// Задача 14. Среднее ненулевых элементов
void task14() {
    const size_t SIZE = 10;
    const long long LIMIT = 1000000000;
    vector<long long> numbers;

    cout << "Введите элементы массива (" << SIZE << " целых чисел в одной строке) и нажмите Enter\n";
    bool inputOk = readNumbersLine("-> ", numbers);

    bool inRange = true;
    long long total = 0;
    int nonzero = 0;
    for (long long number : numbers) {
        if (number > LIMIT || number < -LIMIT) {
            inRange = false;
        }
        total += number;
        if (number != 0) {
            nonzero++;
        }
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (numbers.size() != SIZE) {
        cout << "Ошибка! Нужно ввести ровно " << SIZE << " чисел\n";
    } else if (!inRange) {
        cout << "Ошибка! Слишком большое по модулю число\n";
    } else {
        cout << "-------------------------------\n";
        if (nonzero == 0) {
            cout << "Ненулевых элементов нет\n";
        } else {
            cout << "Сумма элементов массива: " << total << "\n";
            cout << "Количество ненулевых элементов: " << nonzero << "\n";
            cout << fixed << setprecision(2);
            cout << "Среднее арифметическое ненулевых элементов: "
                 << static_cast<double>(total) / nonzero << "\n";
        }
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
        cout << " 1. Десять случайных чисел\n";
        cout << " 2. Три случайные последовательности\n";
        cout << " 3. Стоимость яблок\n";
        cout << " 4. Цельсий и Фаренгейт\n";
        cout << " 5. Сумма и среднее до нуля\n";
        cout << " 6. Максимальное число\n";
        cout << " 7. Минимальное число\n";
        cout << " 8. Простое число\n";
        cout << " 9. Угадай число\n";
        cout << "10. Число Пи\n";
        cout << "11. Массив из семи чисел\n";
        cout << "12. Ненулевые элементы\n";
        cout << "13. Минимальный элемент массива\n";
        cout << "14. Среднее ненулевых элементов\n";
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
