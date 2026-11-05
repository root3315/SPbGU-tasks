// Задача 11. Минуты и секунды в секунды
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

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // кириллица в консоли Windows
#endif

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

    return 0;
}
