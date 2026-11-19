import math

NUMBER_LIMIT = 1000000  # граница для чисел в массивах (задачи 2, 5, 14)
CONTACTS_FILE = "contacts.txt"


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


def read_numbers(prompt):
    """Читает дробные числа, введённые в одной строке через пробел."""
    numbers = [float(part) for part in input(prompt).split()]
    if not all(math.isfinite(number) for number in numbers):
        raise ValueError
    return numbers


def read_integers(prompt):
    """Читает целые числа, введённые в одной строке через пробел."""
    return [int(part) for part in input(prompt).split()]


def in_limit(numbers):
    """Проверяет, что все числа не больше NUMBER_LIMIT по модулю."""
    return all(abs(number) <= NUMBER_LIMIT for number in numbers)


# Задача 1. Средняя температура за неделю
def task_01():
    days = ("Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье")
    total = 0
    in_range = True

    try:
        print("Введите температуру воздуха за неделю")
        for day in days:
            temperature = read_number(f"{day} -> ")
            if not -100 <= temperature <= 100:
                in_range = False
                break
            total += temperature
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if not in_range:
            print("Ошибка! Температура должна быть от -100 до 100 град.")
        else:
            print("------------------------------")
            print(f"Средняя температура за неделю: {total / len(days):.2f} град.")


# Задача 2. Слияние упорядоченных массивов
def is_sorted(numbers):
    """Проверяет, что числа идут по неубыванию."""
    return all(numbers[i] <= numbers[i + 1] for i in range(len(numbers) - 1))


def merge_sorted(first, second):
    """Сливает два упорядоченных массива в один: каждый раз берём меньший из текущих элементов."""
    result = []
    i = j = 0
    while i < len(first) and j < len(second):
        if first[i] <= second[j]:
            result.append(first[i])
            i += 1
        else:
            result.append(second[j])
            j += 1
    # Один из массивов закончился: дописываем остаток другого
    result.extend(first[i:])
    result.extend(second[j:])
    return result


def task_02():
    size = 5

    try:
        print("Объединение двух массивов, упорядоченных по возрастанию")
        print("Введите в одной строке элементы первого массива,")
        first = read_integers(f"({size} целых чисел) -> ")
        print("Введите в одной строке элементы второго массива,")
        second = read_integers(f"({size} целых чисел) -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if len(first) != size or len(second) != size:
            print(f"Ошибка! В каждом массиве должно быть {size} чисел")
        elif not (in_limit(first) and in_limit(second)):
            print("Ошибка! Числа должны быть от -1000000 до 1000000")
        elif not (is_sorted(first) and is_sorted(second)):
            print("Ошибка! Массивы должны быть упорядочены по возрастанию")
        else:
            print("----------------------------------------")
            print("Массив - результат", *merge_sorted(first, second))

    input("Для завершения нажмите Enter")


# Задача 3. Рост учеников
def task_03():
    heights = []
    total = 0
    in_range = True

    try:
        print("*** Анализ роста учеников ***")
        print("Введите рост (см) учеников")
        print("Для завершения введите 0 и нажмите Enter")
        while True:
            height = read_number("-> ")
            if height == 0:
                break
            if not 0 < height <= 300:
                in_range = False
                break
            heights.append(height)
            total += height
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if not in_range:
            print("Ошибка! Рост должен быть больше 0 и не больше 300 см")
        elif not heights:
            print("Ошибка! Не введен рост ни одного ученика")
        else:
            count = len(heights)
            # Сравниваем без деления, чтобы на результат не влияла погрешность среднего
            taller = 0
            for height in heights:
                if height * count > total:
                    taller += 1

            print("-----------------------------")
            print(f"Средний рост: {total / count:.1f} см")
            print(f"У {taller} человек рост превышает средний")


# Задача 4. Результаты экзамена
def task_04():
    grades = ("пятерок", "четверок", "троек", "двоек")
    counts = []

    try:
        print("Обработка результатов экзамена")
        print("Введите исходные данные:")
        for grade in grades:
            counts.append(int(input(f"{grade}-> ")))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        total = sum(counts)

        if min(counts) < 0:
            print("Ошибка! Количество не может быть отрицательным")
        elif max(counts) > 100000:
            print("Ошибка! Слишком большое количество")
        elif total == 0:
            print("Ошибка! Не введено ни одной оценки")
        else:
            print("--------------------------")
            print("Результаты экзамена:")
            for grade, count in zip(grades, counts):
                # Процент с точностью до десятых, половина округляется вверх (6.25 -> 6.3)
                percent = math.floor(count * 1000 / total + 0.5) / 10
                print(f"{grade} {percent:.1f}%")
            print("--------------------------")

    input("Для завершения нажмите Enter")


# Задача 5. Массив 3х5
def task_05():
    rows, columns = 3, 5
    matrix = []

    try:
        print("Ввод и обработка массива (3х5)")
        print("Введите массив по строкам")
        for i in range(rows):
            row = read_numbers(f"Строка {i + 1} -> ")
            if len(row) != columns:
                break
            matrix.append(row)
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if len(matrix) != rows:
            print(f"Ошибка! В строке должно быть {columns} чисел")
        elif not all(in_limit(row) for row in matrix):
            print("Ошибка! Числа должны быть от -1000000 до 1000000")
        else:
            title = "Массив: "
            print("-------------------------------------")
            for i, row in enumerate(matrix):
                # Первая строка идёт после заголовка, остальные выровнены под неё
                prefix = title if i == 0 else " " * len(title)
                print(prefix + " ".join(f"{number:.15g}" for number in row))

            print("Среднее арифметическое:")
            for i, row in enumerate(matrix):
                print(f"Строка {i + 1}: {sum(row) / columns:.2f}")

    input("Для завершения нажмите Enter")


# Задача 6. Приветствие
def task_06():
    print("Как Вас зовут?")
    print("Введите свое имя и фамилию, затем нажмите Enter")
    name = input("-> ").strip()

    if not name:
        print("Ошибка! Имя не введено")
    else:
        print(f"Здравствуйте, {name}!")


# Задача 7. Код символа
def task_07():
    print("Введите символ и нажмите Enter.")
    print("Для завершения введите точку.")
    while True:
        symbol = input("-> ")
        if symbol == ".":
            break

        if len(symbol) == 1:
            print(f"Символ: {symbol} Код: {ord(symbol)}")
        else:
            print("Ошибка! Введите один символ")


# Задача 8. Имя, отчество и фамилия
def task_08():
    print("Введите в одной строке имя, отчество и фамилию")
    words = input("-> ").split()

    if len(words) != 3:
        print("Ошибка! Нужно ввести три слова: имя, отчество и фамилию")
    else:
        name, patronymic, surname = words
        print(f"Имя: {name}")
        print(f"Отчество: {patronymic}")
        print(f"Фамилия: {surname}")

    input("Для завершения нажмите Enter")


# Задача 9. Проверка целого числа
def is_integer(text):
    """Проверяет посимвольно: необязательный знак + или -, затем хотя бы одна цифра."""
    if text[:1] in ("+", "-"):
        text = text[1:]
    return text != "" and all("0" <= char <= "9" for char in text)


def task_09():
    print("Введите число и нажмите Enter")
    text = input("-> ").strip()

    if is_integer(text):
        print("Введенная строка является целым числом.")
    else:
        print("Введенная строка не является целым числом.")


# Задача 10. Двоичное в десятичное
def task_10():
    print("Введите восьмиразрядное двоичное число и нажмите Enter")
    binary = input("-> ").strip()

    if len(binary) != 8 or any(digit not in ("0", "1") for digit in binary):
        print("Ошибка! Нужно ввести 8 цифр 0 или 1")
    else:
        decimal = 0
        for digit in binary:
            decimal = decimal * 2 + (1 if digit == "1" else 0)
        print(f"Двоичному числу {binary} соответствует десятичное {decimal}")

    input("Для завершения нажмите Enter")


# Задача 11. Перевод в другую систему
def to_base(number, base):
    """Переводит неотрицательное целое число в систему с основанием base делением."""
    if number == 0:
        return "0"

    digits = ""
    while number > 0:
        # Остатки от деления дают цифры с конца
        digits = str(number % base) + digits
        number //= base
    return digits


def task_11():
    try:
        number = int(input("Введите целое число -> "))
        base = int(input("Введите основание системы счисления -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if abs(number) > 1000000000:
            print("Ошибка! Число должно быть от -1000000000 до 1000000000")
        elif not 2 <= base <= 10:
            print("Ошибка! Основание должно быть от 2 до 10")
        else:
            sign = "-" if number < 0 else ""
            converted = sign + to_base(abs(number), base)
            print(f"Десятичному числу {number} соответствует число {converted} по основанию {base}")


# Задача 12. Добавление в справочник
def add_contact():
    """Запрашивает фамилию, имя и телефон и дописывает их в справочник."""
    print("Добавление информации в телефонный справочник")
    surname = input("Фамилия -> ").strip()
    name = input("Имя -> ").strip()
    phone = input("Телефон -> ").strip()

    if not (surname and name and phone):
        print("Ошибка! Все поля должны быть заполнены")
    else:
        try:
            # Режим "a" дописывает в конец файла и создаёт файл, если его нет
            with open(CONTACTS_FILE, "a", encoding="utf-8") as file:
                file.write(f"{surname}\n{name}\n{phone}\n")
        except OSError:
            print("Ошибка! Не удалось записать файл")
        else:
            print("Информация добавлена")


def task_12():
    add_contact()
    input("Для завершения нажмите Enter")


# Задача 13. Телефонный справочник
def find_contacts():
    """Ищет в справочнике абонентов с введённой фамилией."""
    print("Поиск в телефонном справочнике")
    surname = input("Фамилия -> ").strip()

    if not surname:
        print("Ошибка! Фамилия не введена")
        return

    try:
        with open(CONTACTS_FILE, encoding="utf-8") as file:
            lines = [line.strip() for line in file]
    except FileNotFoundError:
        print("Справочник пуст")
    else:
        found = 0
        # На каждого абонента в файле три строки: фамилия, имя, телефон
        for i in range(0, len(lines) - 2, 3):
            if lines[i] == surname:
                print(f"{lines[i]} {lines[i + 1]}: {lines[i + 2]}")
                found += 1

        if found == 0:
            print("Абонент не найден")


def task_13():
    while True:
        print("*** Телефонный справочник ***")
        print("1 - Добавление")
        print("2 - Поиск")
        print("0 - Завершение работы")
        choice = input("Ваш выбор -> ").strip()
        if choice == "0":
            break

        if choice == "1":
            add_contact()
        elif choice == "2":
            find_contacts()
        else:
            print("Ошибка! Неверный выбор")
        print()


# Задача 14. Среднее без min и max
def task_14():
    size = 10

    try:
        print("Среднее арифметическое без учета min и max значений")
        numbers = read_integers(f"Введите массив ({size} целых чисел в одной строке) -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if len(numbers) != size:
            print(f"Ошибка! Нужно ввести {size} чисел")
        elif not in_limit(numbers):
            print("Ошибка! Числа должны быть от -1000000 до 1000000")
        else:
            minimum = min(numbers)
            maximum = max(numbers)
            # Исключаем по одному вхождению минимума и максимума
            average = (sum(numbers) - minimum - maximum) / (size - 2)
            # Округляем до сотых, половина вверх: 10.375 -> 10.38
            average = math.floor(average * 100 + 0.5) / 100

            print("------------------------------")
            print(f"Минимальный элемент: {minimum}")
            print(f"Максимальный элемент: {maximum}")
            print(f"Среднее арифм. без учета min и max значений: {average:.2f}")


TASKS = {
    "1": ("Средняя температура за неделю", task_01),
    "2": ("Слияние упорядоченных массивов", task_02),
    "3": ("Рост учеников", task_03),
    "4": ("Результаты экзамена", task_04),
    "5": ("Массив 3х5", task_05),
    "6": ("Приветствие", task_06),
    "7": ("Код символа", task_07),
    "8": ("Имя, отчество и фамилия", task_08),
    "9": ("Проверка целого числа", task_09),
    "10": ("Двоичное в десятичное", task_10),
    "11": ("Перевод в другую систему", task_11),
    "12": ("Добавление в справочник", task_12),
    "13": ("Телефонный справочник", task_13),
    "14": ("Среднее без min и max", task_14),
}


def main():
    while True:
        print("\n" + "=" * 45)
        for number, (title, _) in TASKS.items():
            print(f"{number:>2}. {title}")
        print(" 0. Выход")
        print("=" * 45)

        choice = input("Номер задачи -> ").strip()
        if choice == "0":
            break

        print()
        if choice in TASKS:
            TASKS[choice][1]()
        else:
            print("Нет такой задачи")


if __name__ == "__main__":
    try:
        main()
    except EOFError:
        pass  # ввод закрыт: просто завершаем программу
