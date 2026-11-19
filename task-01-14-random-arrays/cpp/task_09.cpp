// Задача 9. Угадай число
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Генератор случайных чисел
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

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

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
                return 0;  // ввод закрыт: продолжать игру нельзя
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

    return 0;
}
