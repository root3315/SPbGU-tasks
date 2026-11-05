import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


# Задача 1. Печать фотографий
def task_01():
    try:
        print("Фото")
        print("Размер:")
        print("1 – 9х12")
        print("2 – 10х15")
        print("3 – 18х24")
        choice = int(input("Ваш выбор –> "))
        quantity = int(input("Количество –> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        # Цены из присланного образца
        prices = {1: 3.50, 2: 5.00, 3: 10.00}

        if choice not in prices:
            print("Ошибка! Неверный выбор размера")
        elif quantity <= 0:
            print("Ошибка! Количество должно быть больше нуля")
        elif quantity > 1000000:
            print("Ошибка! Слишком большое количество")
        else:
            price = prices[choice]
            total = price * quantity
            # Скидка 10% предоставляется, если фотографий больше 10
            discount = total * 0.10 if quantity > 10 else 0

            print("-----------------------------")
            print(f"Цена: {price:.2f} руб.")
            print(f"Количество: {quantity} шт.")
            print(f"Сумма: {total:.2f} руб.")
            print(f"Скидка: {discount:.2f} руб.")
            print(f"К оплате: {total - discount:.2f} руб.")


# Задача 2. Заправка автомобиля
def task_02():
    try:
        print("Бензин")
        print("Марка бензина:")
        print("1 – 92")
        print("2 – 95")
        print("3 – 98")
        print("4 – DT")
        choice = int(input("Ваш выбор –> "))
        liters = read_number("Литров –> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        # В условии есть только итог для марки 95 (20.30 руб.), остальные цены приняты самостоятельно
        prices = {1: 19.50, 2: 20.30, 3: 22.10, 4: 18.70}

        if choice not in prices:
            print("Ошибка! Неверный выбор марки")
        elif liters <= 0:
            print("Ошибка! Количество литров должно быть больше нуля")
        elif liters > 1000000:
            print("Ошибка! Слишком большое количество")
        else:
            price = prices[choice]
            # Округляем до копеек; 1e-6 защищает от ошибок дробных чисел (18.70 * 0.25 = 4.675)
            total = int(price * liters * 100 + 0.5 + 1e-6) / 100

            print("-----------------------------")
            print(f"Цена за литр: {price:.2f} руб.")
            print(f"Литров: {liters:.15g}")
            print(f"К оплате: {total:.2f} руб.")


# Задача 3. Таблица квадратов
def task_03():
    print("Таблица квадратов")
    print("--------------")
    print("Число Квадрат")
    print("--------------")
    for number in range(1, 11):
        print(f"{number:3}{number * number:9}")
    print("--------------")


# Задача 4. Таблица квадратов нечетных чисел
def task_04():
    print("Таблица квадратов нечетных чисел")
    print("--------------")
    print("Число Квадрат")
    print("--------------")
    for number in range(1, 10, 2):
        print(f"{number:3}{number * number:9}")
    print("--------------")


# Задача 5. Скорость свободного падения
def task_05():
    g = 9.8  # ускорение свободного падения, м/с2
    step = 0.5  # шаг по времени, с

    print("-----------------------")
    print("Время, с Скорость, м/с")
    print("-----------------------")
    # Время считаем через номер шага: так дробная ошибка не накапливается
    for i in range(7):
        time = i * step
        print(f"{time:5.1f}{g * time:12.2f}")
    print("-----------------------")


# Задача 6. Платежи по кредиту
def task_06():
    try:
        amount = read_number("Сумма кредита (руб.) -> ")
        months = int(input("Срок (мес.) -> "))
        rate = read_number("Процентная ставка (годовых) -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if amount <= 0 or months <= 0 or rate < 0:
            print("Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля")
        elif amount > 10000000:
            print("Ошибка! Слишком большая сумма")
        elif rate > 100:
            print("Ошибка! Слишком большая ставка")
        elif months > 1200:
            print("Ошибка! Слишком большой срок")
        else:
            share = amount / months  # равная доля долга, возвращаемая каждый месяц
            total_interest = 0

            print("---------------------------------------")
            print("           Долг     Процент      Платеж")
            print("---------------------------------------")
            for month in range(1, months + 1):
                # Проценты начисляются на остаток долга за один месяц
                debt = amount - share * (month - 1)
                interest = debt * rate / 100 / 12
                total_interest += interest
                print(f"{month:3}{debt:12.2f}{interest:12.2f}{share + interest:12.2f}")
            print("---------------------------------------")
            print(f"Всего процентов: {total_interest:.2f}")


# Задача 7. Цельсий и Фаренгейт
def task_07():
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


# Задача 8. Сумма первых n чисел
def task_08():
    try:
        print("Сумма положительных чисел")
        count = int(input("Введите количество суммируемых чисел -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if count <= 0:
            print("Ошибка! Количество должно быть больше нуля")
        elif count > 1000000:
            print("Ошибка! Слишком большое количество")
        else:
            total = 0
            for number in range(1, count + 1):
                total += number
            print(f"Сумма первых {count} положительных чисел равна {total}")


# Задача 9. Сумма первых n четных чисел
def task_09():
    try:
        print("Вычисление суммы четных положительных чисел")
        print("Введите количество суммируемых чисел и нажмите Enter")
        count = int(input("-> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if count <= 0:
            print("Ошибка! Количество должно быть больше нуля")
        elif count > 1000000:
            print("Ошибка! Слишком большое количество")
        else:
            total = 0
            for i in range(1, count + 1):
                total += 2 * i
            print(f"Сумма первых {count} положительных четных чисел равна {total}")


# Задача 10. Сумма ряда 1, 3, 5, 7
def task_10():
    try:
        print("Вычисление частичной суммы ряда: 1,3,5,7, ...")
        count = int(input("Введите количество суммируемых членов ряда -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if count <= 0:
            print("Ошибка! Количество должно быть больше нуля")
        elif count > 1000000:
            print("Ошибка! Слишком большое количество")
        else:
            total = 0
            for i in range(1, count + 1):
                total += 2 * i - 1
            print(f"Сумма первых {count} членов ряда равна {total}")


# Задача 11. Таблица степеней двойки
def task_11():
    print("Таблица степеней двойки")
    print()
    power = 1
    for exponent in range(11):
        print(f"{exponent:3}{power:7}")
        power *= 2


# Задача 12. Факториал
def task_12():
    try:
        print("Вычисление факториала")
        print("Введите число, факториал которого надо вычислить")
        number = int(input("-> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if number < 0:
            print("Ошибка! Число не может быть отрицательным")
        elif number > 20:
            print("Ошибка! Слишком большое число")
        else:
            factorial = 1
            for i in range(2, number + 1):
                factorial *= i
            print(f"Факториал {number} равен {factorial}")


# Задача 13. Среднее арифметическое пяти чисел
def task_13():
    try:
        count = 5
        total = 0

        print("Среднее арифметическое последовательности дробных чисел.")
        print("После ввода каждого числа нажимайте Enter")
        for _ in range(count):
            total += read_number("-> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        print(f"Среднее арифметическое введенной последовательности: {total / count:.2f}")

    input("Для завершения нажмите Enter")


# Задача 14. Обработка последовательности
def task_14():
    try:
        numbers = []

        print("Обработка последовательности дробных чисел.")
        count = int(input("Введите количество чисел последовательности -> "))
        if 0 < count <= 1000:
            print("Вводите последовательность. После ввода каждого числа нажимайте Enter")
            for _ in range(count):
                numbers.append(read_number("-> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if count <= 0:
            print("Ошибка! Количество должно быть больше нуля")
        elif count > 1000:
            print("Ошибка! Слишком большое количество")
        else:
            print(f"Количество чисел: {count}")
            print(f"Среднее арифметическое: {sum(numbers) / count:.2f}")
            print(f"Минимальное число: {min(numbers):.15g}")
            print(f"Максимальное число: {max(numbers):.15g}")

    input("Для завершения нажмите Enter")


TASKS = {
    "1": ("Печать фотографий", task_01),
    "2": ("Заправка автомобиля", task_02),
    "3": ("Таблица квадратов", task_03),
    "4": ("Таблица квадратов нечетных чисел", task_04),
    "5": ("Скорость свободного падения", task_05),
    "6": ("Платежи по кредиту", task_06),
    "7": ("Цельсий и Фаренгейт", task_07),
    "8": ("Сумма первых n чисел", task_08),
    "9": ("Сумма первых n четных чисел", task_09),
    "10": ("Сумма ряда 1, 3, 5, 7", task_10),
    "11": ("Таблица степеней двойки", task_11),
    "12": ("Факториал", task_12),
    "13": ("Среднее арифметическое пяти чисел", task_13),
    "14": ("Обработка последовательности", task_14),
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
