import math
import random


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


# Задача 1. Десять случайных чисел
def task_01():
    count = 10
    total = 0

    print("Случайные числа")
    for _ in range(count):
        number = random.randint(1, 10)
        print(number)
        total += number
    print(f"Сред. арифм.: {total / count:.2f}")


# Задача 2. Три случайные последовательности
def task_02():
    count = 10

    print("Случайные числа")
    for _ in range(3):
        numbers = [random.randint(1, 10) for _ in range(count)]
        line = " ".join(str(number) for number in numbers)
        print(f"{line} сред. арифм.: {sum(numbers) / count:.2f}")


# Задача 3. Стоимость яблок
def task_03():
    try:
        print("Введите цену одного килограмма и нажмите Enter")
        print("(копейки от рублей отделяйте точкой)")
        price = read_number("-> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if price <= 0:
            print("Ошибка! Цена должна быть больше нуля")
        elif price > 1000000:
            print("Ошибка! Слишком большая цена")
        else:
            print("-------------------------")
            print("Вес, гр.  Стоимость, руб.")
            print("-------------------------")
            for weight in range(100, 1001, 100):
                # Округляем до копеек; 1e-6 защищает от ошибок дробных чисел
                kopecks = int(price * weight / 10 + 0.5 + 1e-6)
                print(f"{weight:8}{kopecks / 100:17.2f}")
            print("-------------------------")


# Задача 4. Цельсий и Фаренгейт
def task_04():
    try:
        t1 = read_number("t1 –> ")
        t2 = read_number("t2 –> ")
        dt = read_number("dt –> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if dt <= 0:
            print("Ошибка! Шаг должен быть больше нуля")
        elif t1 > t2:
            print("Ошибка! Начальная температура больше конечной")
        elif (t2 - t1) / dt > 10000:
            print("Ошибка! Слишком много строк в таблице")
        else:
            # Температуру считаем через номер шага: так дробная ошибка не накапливается.
            # 1e-9 нужно, чтобы последний шаг не потерялся из-за такой же ошибки в делении
            steps = int((t2 - t1) / dt + 1e-9)

            print("----------------")
            print("    C         F")
            print("----------------")
            for i in range(steps + 1):
                celsius = round(t1 + i * dt, 9) + 0.0  # округление убирает вывод "-0.00"
                fahrenheit = 9 / 5 * celsius + 32
                print(f"{celsius:6.2f}{fahrenheit:10.2f}")


# Задача 5. Сумма и среднее до нуля
def task_05():
    try:
        count = 0
        total = 0

        print("Вычисление среднего арифметического последовательности положительных чисел.")
        print("Вводите после стрелки числа. Для завершения ввода введите ноль.")
        while True:
            number = read_number("> ")
            if number <= 0:
                break
            count += 1
            total += number
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if number < 0:
            print("Ошибка! Число должно быть положительным")
        elif count == 0:
            print("Не введено ни одного числа")
        else:
            print(f"Введено чисел: {count}")
            print(f"Сумма чисел: {total:.15g}")
            print(f"Среднее арифметическое: {total / count:.2f}")


# Задача 6. Максимальное число
def task_06():
    try:
        maximum = 0  # все числа положительные, поэтому любое из них больше нуля

        print("Определение максимального числа из последовательности положительных чисел.")
        print("Вводите числа после стрелки. Для завершения ввода введите ноль.")
        while True:
            number = read_number("> ")
            if number <= 0:
                break
            maximum = max(maximum, number)
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if number < 0:
            print("Ошибка! Число должно быть положительным")
        elif maximum == 0:
            print("Не введено ни одного числа")
        else:
            print(f"Максимальное число: {maximum:.15g}")


# Задача 7. Минимальное число
def task_07():
    try:
        count = 0
        minimum = 0

        print("Определение минимального числа в последовательности положительных чисел.")
        print("Вводите после стрелки числа. Для завершения ввода введите ноль.")
        while True:
            number = read_number("> ")
            if number <= 0:
                break
            # Первое число сразу считаем минимумом
            if count == 0 or number < minimum:
                minimum = number
            count += 1
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if number < 0:
            print("Ошибка! Число должно быть положительным")
        elif count == 0:
            print("Не введено ни одного числа")
        else:
            print(f"Минимальное число: {minimum:.15g}")


# Задача 8. Простое число
def task_08():
    try:
        print("Введите целое число и нажмите Enter")
        number = int(input("> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if abs(number) > 10**12:
            print("Ошибка! Слишком большое по модулю число")
        else:
            # Числа меньше 2 простыми не считаются; делители ищем до корня из числа
            is_prime = number >= 2
            divisor = 2
            while is_prime and divisor * divisor <= number:
                if number % divisor == 0:
                    is_prime = False
                divisor += 1

            if is_prime:
                print(f"{number} - простое число.")
            else:
                print(f"{number} - не простое число.")


# Задача 9. Угадай число
def task_09():
    secret = random.randint(1, 10)
    attempts_left = 5
    prompt = "> "
    won = False

    print('Игра "Угадай число".')
    print('Компьютер "задумал" число от 1 до 10.')
    print("Угадайте его за пять попыток.")
    print("Введите число и нажмите Enter")
    while attempts_left > 0:
        # Ошибка ввода попытку не тратит
        try:
            guess = int(input(prompt))
        except ValueError:
            print("Ошибка! Неверный формат числа")
            continue
        if guess < 1 or guess > 10:
            print("Ошибка! Число должно быть от 1 до 10")
            continue

        if guess == secret:
            won = True
            break
        attempts_left -= 1
        print("Нет.")
        prompt = "-> "

    if won:
        print("Вы выиграли! Поздравляю!")
    else:
        print(f"Вы проиграли. Компьютер задумал число {secret}.")


# Задача 10. Число Пи
def task_10():
    try:
        eps = read_number("Задайте точность вычисления Пи -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if eps <= 0 or eps >= 1:
            print("Ошибка! Точность должна быть больше нуля и меньше единицы")
        elif eps < 1e-6:
            print("Ошибка! Точность не может быть меньше 0.000001")
        else:
            # Ряд 1 - 1/3 + 1/5 - ... сходится к Пи/4. Суммируем, пока
            # только что прибавленный член не станет меньше точности
            total = 0
            count = 0
            sign = 1
            while True:
                count += 1
                term = 1 / (2 * count - 1)
                total += sign * term
                sign = -sign
                if term < eps:
                    break

            print(f"Значение числа Пи с точностью {eps:.6f} равно {4 * total:.6f}")
            print(f"Просуммировано {count} членов ряда.")


# Задача 11. Массив из семи чисел
def task_11():
    try:
        size = 7
        numbers = []

        print("Ввод массива целых чисел")
        print("После ввода каждого числа нажмите Enter")
        for i in range(size):
            numbers.append(int(input(f"a[{i}] -> ")))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if any(abs(number) > 10**9 for number in numbers):
            print("Ошибка! Слишком большое по модулю число")
        else:
            print("Массив:", *numbers)
            print(f"Среднее арифметическое: {sum(numbers) / size:.2f}")


# Задача 12. Ненулевые элементы
def task_12():
    try:
        size = 5
        numbers = []

        print("Ввод массива дробных чисел")
        print("После ввода каждого числа нажмите Enter")
        for i in range(1, size + 1):
            numbers.append(read_number(f"a[{i}] -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        nonzero = sum(1 for number in numbers if number != 0)
        print("------------------------")
        print(f"Ненулевых элементов: {nonzero}")


# Задача 13. Минимальный элемент массива
def task_13():
    try:
        size = 5

        print("Поиск минимального элемента массива")
        print(f"Введите в одной строке {size} целых чисел и нажмите Enter")
        numbers = [int(part) for part in input("-> ").split()]
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if len(numbers) != size:
            print(f"Ошибка! Нужно ввести ровно {size} чисел")
        elif any(abs(number) > 10**9 for number in numbers):
            print("Ошибка! Слишком большое по модулю число")
        else:
            print(f"Минимальный элемент массива: {min(numbers)}")


# Задача 14. Среднее ненулевых элементов
def task_14():
    try:
        size = 10

        print(f"Введите элементы массива ({size} целых чисел в одной строке) и нажмите Enter")
        numbers = [int(part) for part in input("-> ").split()]
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if len(numbers) != size:
            print(f"Ошибка! Нужно ввести ровно {size} чисел")
        elif any(abs(number) > 10**9 for number in numbers):
            print("Ошибка! Слишком большое по модулю число")
        else:
            total = sum(numbers)
            nonzero = sum(1 for number in numbers if number != 0)

            print("-------------------------------")
            if nonzero == 0:
                print("Ненулевых элементов нет")
            else:
                print(f"Сумма элементов массива: {total}")
                print(f"Количество ненулевых элементов: {nonzero}")
                print(f"Среднее арифметическое ненулевых элементов: {total / nonzero:.2f}")


TASKS = {
    "1": ("Десять случайных чисел", task_01),
    "2": ("Три случайные последовательности", task_02),
    "3": ("Стоимость яблок", task_03),
    "4": ("Цельсий и Фаренгейт", task_04),
    "5": ("Сумма и среднее до нуля", task_05),
    "6": ("Максимальное число", task_06),
    "7": ("Минимальное число", task_07),
    "8": ("Простое число", task_08),
    "9": ("Угадай число", task_09),
    "10": ("Число Пи", task_10),
    "11": ("Массив из семи чисел", task_11),
    "12": ("Ненулевые элементы", task_12),
    "13": ("Минимальный элемент массива", task_13),
    "14": ("Среднее ненулевых элементов", task_14),
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
