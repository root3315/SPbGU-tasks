#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

const int NUMBER_LIMIT = 1000000;  // граница для чисел в массивах (задачи 2, 5, 14)
const string CONTACTS_FILE = "contacts.txt";

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

// Показывает подсказку и читает числа, введённые в одной строке через пробел
template <typename T>
bool readValues(const string& prompt, vector<T>& values) {
    cout << prompt;

    string line;
    getline(cin, line);

    istringstream stream(line);
    string word;
    values.clear();
    while (stream >> word) {
        // Каждое слово должно быть числом целиком, без лишних символов
        istringstream wordStream(word);
        T value;
        char extra;
        if (!(wordStream >> value) || (wordStream >> extra)) {
            return false;
        }
        values.push_back(value);
    }
    return true;
}

// Проверяет, что все числа не больше NUMBER_LIMIT по модулю
template <typename T>
bool inLimit(const vector<T>& numbers) {
    for (T number : numbers) {
        if (abs(number) > NUMBER_LIMIT) {
            return false;
        }
    }
    return true;
}

// Убирает пробельные символы по краям строки
string trim(const string& text) {
    const string SPACES = " \t\r\n\v\f";
    size_t begin = text.find_first_not_of(SPACES);
    if (begin == string::npos) {
        return "";
    }
    size_t end = text.find_last_not_of(SPACES);
    return text.substr(begin, end - begin + 1);
}

// Показывает подсказку и читает строку целиком, без пробелов по краям
string readLine(const string& prompt) {
    cout << prompt;
    string line;
    getline(cin, line);
    return trim(line);
}

// Задача 1. Средняя температура за неделю
void task01() {
    const string DAYS[] = {"Понедельник", "Вторник", "Среда", "Четверг",
                           "Пятница", "Суббота", "Воскресенье"};
    const int DAY_COUNT = 7;
    double total = 0;
    bool inputOk = true, inRange = true;

    cout << "Введите температуру воздуха за неделю\n";
    for (int i = 0; i < DAY_COUNT && inputOk && inRange; i++) {
        double temperature = 0;
        inputOk = readValue(DAYS[i] + " -> ", temperature);
        inRange = temperature >= -100 && temperature <= 100;
        total += temperature;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (!inRange) {
        cout << "Ошибка! Температура должна быть от -100 до 100 град.\n";
    } else {
        cout << "------------------------------\n";
        cout << fixed << setprecision(2);
        cout << "Средняя температура за неделю: " << total / DAY_COUNT << " град.\n";
    }
}

// Задача 2. Слияние упорядоченных массивов

// Проверяет, что числа идут по неубыванию
bool isSorted(const vector<int>& numbers) {
    for (size_t i = 1; i < numbers.size(); i++) {
        if (numbers[i - 1] > numbers[i]) {
            return false;
        }
    }
    return true;
}

// Сливает два упорядоченных массива в один: каждый раз берём меньший из текущих элементов
vector<int> mergeSorted(const vector<int>& first, const vector<int>& second) {
    vector<int> result;
    size_t i = 0, j = 0;
    while (i < first.size() && j < second.size()) {
        if (first[i] <= second[j]) {
            result.push_back(first[i++]);
        } else {
            result.push_back(second[j++]);
        }
    }
    // Один из массивов закончился: дописываем остаток другого
    while (i < first.size()) {
        result.push_back(first[i++]);
    }
    while (j < second.size()) {
        result.push_back(second[j++]);
    }
    return result;
}

void task02() {
    const size_t SIZE = 5;
    vector<int> first, second;

    cout << "Объединение двух массивов, упорядоченных по возрастанию\n";
    cout << "Введите в одной строке элементы первого массива,\n";
    bool inputOk = readValues("(5 целых чисел) -> ", first);
    if (inputOk) {
        cout << "Введите в одной строке элементы второго массива,\n";
        inputOk = readValues("(5 целых чисел) -> ", second);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (first.size() != SIZE || second.size() != SIZE) {
        cout << "Ошибка! В каждом массиве должно быть 5 чисел\n";
    } else if (!(inLimit(first) && inLimit(second))) {
        cout << "Ошибка! Числа должны быть от -1000000 до 1000000\n";
    } else if (!(isSorted(first) && isSorted(second))) {
        cout << "Ошибка! Массивы должны быть упорядочены по возрастанию\n";
    } else {
        cout << "----------------------------------------\n";
        cout << "Массив - результат";
        for (int number : mergeSorted(first, second)) {
            cout << " " << number;
        }
        cout << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

// Задача 3. Рост учеников
void task03() {
    vector<double> heights;
    double total = 0;
    bool inputOk = true, inRange = true;

    cout << "*** Анализ роста учеников ***\n";
    cout << "Введите рост (см) учеников\n";
    cout << "Для завершения введите 0 и нажмите Enter\n";
    while (true) {
        double height = 0;
        inputOk = readValue("-> ", height);
        if (!inputOk || height == 0) {
            break;
        }
        if (height < 0 || height > 300) {
            inRange = false;
            break;
        }
        heights.push_back(height);
        total += height;
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (!inRange) {
        cout << "Ошибка! Рост должен быть больше 0 и не больше 300 см\n";
    } else if (heights.empty()) {
        cout << "Ошибка! Не введен рост ни одного ученика\n";
    } else {
        double count = heights.size();
        // Сравниваем без деления, чтобы на результат не влияла погрешность среднего
        int taller = 0;
        for (double height : heights) {
            if (height * count > total) {
                taller++;
            }
        }

        cout << "-----------------------------\n";
        cout << fixed << setprecision(1) << "Средний рост: " << total / count << " см\n";
        cout << "У " << taller << " человек рост превышает средний\n";
    }
}

// Задача 4. Результаты экзамена
void task04() {
    const string GRADES[] = {"пятерок", "четверок", "троек", "двоек"};
    const int GRADE_COUNT = 4;
    int counts[GRADE_COUNT] = {};
    bool inputOk = true;

    cout << "Обработка результатов экзамена\n";
    cout << "Введите исходные данные:\n";
    for (int i = 0; i < GRADE_COUNT && inputOk; i++) {
        inputOk = readValue(GRADES[i] + "-> ", counts[i]);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else {
        int total = 0, minimum = counts[0], maximum = counts[0];
        for (int count : counts) {
            total += count;
            minimum = min(minimum, count);
            maximum = max(maximum, count);
        }

        if (minimum < 0) {
            cout << "Ошибка! Количество не может быть отрицательным\n";
        } else if (maximum > 100000) {
            cout << "Ошибка! Слишком большое количество\n";
        } else if (total == 0) {
            cout << "Ошибка! Не введено ни одной оценки\n";
        } else {
            cout << "--------------------------\n";
            cout << "Результаты экзамена:\n";
            cout << fixed << setprecision(1);
            for (int i = 0; i < GRADE_COUNT; i++) {
                // Процент с точностью до десятых, половина округляется вверх (6.25 -> 6.3)
                double percent = floor(counts[i] * 1000.0 / total + 0.5) / 10;
                cout << GRADES[i] << " " << percent << "%\n";
            }
            cout << "--------------------------\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

// Задача 5. Массив 3х5
void task05() {
    const size_t ROWS = 3, COLUMNS = 5;
    vector<vector<double>> matrix;
    bool inputOk = true;

    cout << "Ввод и обработка массива (3х5)\n";
    cout << "Введите массив по строкам\n";
    for (size_t i = 0; i < ROWS; i++) {
        vector<double> row;
        inputOk = readValues("Строка " + to_string(i + 1) + " -> ", row);
        if (!inputOk || row.size() != COLUMNS) {
            break;
        }
        matrix.push_back(row);
    }

    bool inRange = true;
    for (const vector<double>& row : matrix) {
        inRange = inRange && inLimit(row);
    }

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (matrix.size() != ROWS) {
        cout << "Ошибка! В строке должно быть 5 чисел\n";
    } else if (!inRange) {
        cout << "Ошибка! Числа должны быть от -1000000 до 1000000\n";
    } else {
        const string TITLE = "Массив: ";
        const string INDENT(8, ' ');  // ширина заголовка в символах (в байтах UTF-8 она больше)
        cout << "-------------------------------------\n";
        cout << defaultfloat << setprecision(15);
        for (size_t i = 0; i < ROWS; i++) {
            // Первая строка идёт после заголовка, остальные выровнены под неё
            cout << (i == 0 ? TITLE : INDENT);
            for (size_t j = 0; j < COLUMNS; j++) {
                cout << (j == 0 ? "" : " ") << matrix[i][j];
            }
            cout << "\n";
        }

        cout << "Среднее арифметическое:\n";
        cout << fixed << setprecision(2);
        for (size_t i = 0; i < ROWS; i++) {
            double total = 0;
            for (double number : matrix[i]) {
                total += number;
            }
            cout << "Строка " << i + 1 << ": " << total / COLUMNS << "\n";
        }
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

// Задача 6. Приветствие
void task06() {
    cout << "Как Вас зовут?\n";
    cout << "Введите свое имя и фамилию, затем нажмите Enter\n";
    string name = readLine("-> ");

    if (name.empty()) {
        cout << "Ошибка! Имя не введено\n";
    } else {
        cout << "Здравствуйте, " << name << "!\n";
    }
}

// Задача 7. Код символа

// Если строка в UTF-8 состоит ровно из одного символа, записывает его код Unicode в code
bool decodeSingleChar(const string& text, long& code) {
    if (text.empty()) {
        return false;
    }

    // По первому байту определяем, сколько байт занимает символ
    unsigned char first = text[0];
    size_t length;
    if (first < 0x80) {
        length = 1;
        code = first;
    } else if ((first & 0xE0) == 0xC0) {
        length = 2;
        code = first & 0x1F;
    } else if ((first & 0xF0) == 0xE0) {
        length = 3;
        code = first & 0x0F;
    } else if ((first & 0xF8) == 0xF0) {
        length = 4;
        code = first & 0x07;
    } else {
        return false;
    }

    if (text.size() != length) {
        return false;
    }
    // Каждый следующий байт имеет вид 10xxxxxx и добавляет 6 бит кода
    for (size_t i = 1; i < length; i++) {
        unsigned char next = text[i];
        if ((next & 0xC0) != 0x80) {
            return false;
        }
        code = (code << 6) | (next & 0x3F);
    }
    return true;
}

void task07() {
    cout << "Введите символ и нажмите Enter.\n";
    cout << "Для завершения введите точку.\n";
    while (true) {
        cout << "-> ";
        string symbol;
        if (!getline(cin, symbol) || symbol == ".") {
            break;
        }

        long code;
        if (decodeSingleChar(symbol, code)) {
            cout << "Символ: " << symbol << " Код: " << code << "\n";
        } else {
            cout << "Ошибка! Введите один символ\n";
        }
    }
}

// Задача 8. Имя, отчество и фамилия
void task08() {
    cout << "Введите в одной строке имя, отчество и фамилию\n";
    cout << "-> ";
    string line;
    getline(cin, line);

    istringstream stream(line);
    vector<string> words;
    string word;
    while (stream >> word) {
        words.push_back(word);
    }

    if (words.size() != 3) {
        cout << "Ошибка! Нужно ввести три слова: имя, отчество и фамилию\n";
    } else {
        cout << "Имя: " << words[0] << "\n";
        cout << "Отчество: " << words[1] << "\n";
        cout << "Фамилия: " << words[2] << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

// Задача 9. Проверка целого числа

// Проверяет посимвольно: необязательный знак + или -, затем хотя бы одна цифра
bool isInteger(const string& text) {
    size_t start = (!text.empty() && (text[0] == '+' || text[0] == '-')) ? 1 : 0;
    if (start == text.size()) {
        return false;
    }
    for (size_t i = start; i < text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

void task09() {
    cout << "Введите число и нажмите Enter\n";
    string text = readLine("-> ");

    if (isInteger(text)) {
        cout << "Введенная строка является целым числом.\n";
    } else {
        cout << "Введенная строка не является целым числом.\n";
    }
}

// Задача 10. Двоичное в десятичное
void task10() {
    cout << "Введите восьмиразрядное двоичное число и нажмите Enter\n";
    string binary = readLine("-> ");

    bool isBinary = binary.size() == 8;
    for (char digit : binary) {
        if (digit != '0' && digit != '1') {
            isBinary = false;
        }
    }

    if (!isBinary) {
        cout << "Ошибка! Нужно ввести 8 цифр 0 или 1\n";
    } else {
        int decimal = 0;
        for (char digit : binary) {
            decimal = decimal * 2 + (digit == '1' ? 1 : 0);
        }
        cout << "Двоичному числу " << binary << " соответствует десятичное " << decimal << "\n";
    }

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

// Задача 11. Перевод в другую систему

// Переводит неотрицательное целое число в систему с основанием base делением
string toBase(long long number, int base) {
    if (number == 0) {
        return "0";
    }

    string digits;
    while (number > 0) {
        // Остатки от деления дают цифры с конца
        digits = to_string(number % base) + digits;
        number /= base;
    }
    return digits;
}

void task11() {
    long long number;
    int base;

    bool inputOk = readValue("Введите целое число -> ", number)
        && readValue("Введите основание системы счисления -> ", base);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (llabs(number) > 1000000000) {
        cout << "Ошибка! Число должно быть от -1000000000 до 1000000000\n";
    } else if (base < 2 || base > 10) {
        cout << "Ошибка! Основание должно быть от 2 до 10\n";
    } else {
        string converted = (number < 0 ? "-" : "") + toBase(llabs(number), base);
        cout << "Десятичному числу " << number << " соответствует число " << converted
             << " по основанию " << base << "\n";
    }
}

// Задача 12. Добавление в справочник

// Запрашивает фамилию, имя и телефон и дописывает их в справочник
void addContact() {
    cout << "Добавление информации в телефонный справочник\n";
    string surname = readLine("Фамилия -> ");
    string name = readLine("Имя -> ");
    string phone = readLine("Телефон -> ");

    if (surname.empty() || name.empty() || phone.empty()) {
        cout << "Ошибка! Все поля должны быть заполнены\n";
    } else {
        // Режим app дописывает в конец файла и создаёт файл, если его нет
        ofstream file(CONTACTS_FILE, ios::app);
        file << surname << "\n" << name << "\n" << phone << "\n";

        if (!file) {
            cout << "Ошибка! Не удалось записать файл\n";
        } else {
            cout << "Информация добавлена\n";
        }
    }
}

void task12() {
    addContact();

    cout << "Для завершения нажмите Enter";
    string pause;
    getline(cin, pause);
}

// Задача 13. Телефонный справочник

// Ищет в справочнике абонентов с введённой фамилией
void findContacts() {
    cout << "Поиск в телефонном справочнике\n";
    string surname = readLine("Фамилия -> ");

    if (surname.empty()) {
        cout << "Ошибка! Фамилия не введена\n";
        return;
    }

    ifstream file(CONTACTS_FILE);
    if (!file) {
        cout << "Справочник пуст\n";
        return;
    }

    // На каждого абонента в файле три строки: фамилия, имя, телефон
    int found = 0;
    string fileSurname, name, phone;
    while (getline(file, fileSurname) && getline(file, name) && getline(file, phone)) {
        if (trim(fileSurname) == surname) {
            cout << trim(fileSurname) << " " << trim(name) << ": " << trim(phone) << "\n";
            found++;
        }
    }

    if (found == 0) {
        cout << "Абонент не найден\n";
    }
}

void task13() {
    while (true) {
        cout << "*** Телефонный справочник ***\n";
        cout << "1 - Добавление\n";
        cout << "2 - Поиск\n";
        cout << "0 - Завершение работы\n";
        string choice = readLine("Ваш выбор -> ");
        if (cin.eof() || choice == "0") {
            break;
        }

        if (choice == "1") {
            addContact();
        } else if (choice == "2") {
            findContacts();
        } else {
            cout << "Ошибка! Неверный выбор\n";
        }
        cout << "\n";
    }
}

// Задача 14. Среднее без min и max
void task14() {
    const size_t SIZE = 10;
    vector<int> numbers;

    cout << "Среднее арифметическое без учета min и max значений\n";
    bool inputOk = readValues("Введите массив (10 целых чисел в одной строке) -> ", numbers);

    if (!inputOk) {
        cout << "Ошибка! Неверный формат числа\n";
    } else if (numbers.size() != SIZE) {
        cout << "Ошибка! Нужно ввести 10 чисел\n";
    } else if (!inLimit(numbers)) {
        cout << "Ошибка! Числа должны быть от -1000000 до 1000000\n";
    } else {
        int minimum = numbers[0], maximum = numbers[0];
        long long total = 0;
        for (int number : numbers) {
            total += number;
            minimum = min(minimum, number);
            maximum = max(maximum, number);
        }
        // Исключаем по одному вхождению минимума и максимума
        double average = static_cast<double>(total - minimum - maximum) / (SIZE - 2);
        // Округляем до сотых, половина вверх: 10.375 -> 10.38
        average = floor(average * 100 + 0.5) / 100;

        cout << "------------------------------\n";
        cout << "Минимальный элемент: " << minimum << "\n";
        cout << "Максимальный элемент: " << maximum << "\n";
        cout << fixed << setprecision(2);
        cout << "Среднее арифм. без учета min и max значений: " << average << "\n";
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
    SetConsoleCP(CP_UTF8);        // ввод кириллицы тоже в UTF-8
#endif

    while (true) {
        // Задачи меняют формат вывода чисел: возвращаем обычный перед каждым запуском
        cout << defaultfloat << setprecision(6);

        cout << "\n=============================================\n";
        cout << " 1. Средняя температура за неделю\n";
        cout << " 2. Слияние упорядоченных массивов\n";
        cout << " 3. Рост учеников\n";
        cout << " 4. Результаты экзамена\n";
        cout << " 5. Массив 3х5\n";
        cout << " 6. Приветствие\n";
        cout << " 7. Код символа\n";
        cout << " 8. Имя, отчество и фамилия\n";
        cout << " 9. Проверка целого числа\n";
        cout << "10. Двоичное в десятичное\n";
        cout << "11. Перевод в другую систему\n";
        cout << "12. Добавление в справочник\n";
        cout << "13. Телефонный справочник\n";
        cout << "14. Среднее без min и max\n";
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
