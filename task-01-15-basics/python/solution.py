import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


# Задача 1. Доход по вкладу
def task_01():
    try:
        print("Вычисление дохода по вкладу")
        print("Введите исходные данные:")
        amount = read_number("Сумма вклада (руб.) -> ")
        months = int(input("Срок вклада (месяцев) -> "))
        rate = read_number("Процентная ставка (годовых) -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if amount <= 0 or months <= 0 or rate < 0:
            print("Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля")
        else:
            income = amount * rate / 100 * months / 12
            print("-------------------------------------")
            print(f"Доход: {income:.2f} руб.")
            print(f"Сумма по окончании срока вклада: {amount + income:.2f} руб.")


# Задача 2. Минуты в часы и минуты
def task_02():
    try:
        interval = int(input("Введите временной интервал (в минутах) -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if interval < 0:
            print("Ошибка! Интервал не может быть отрицательным")
        else:
            print(f"{interval} минут - это {interval // 60} ч. {interval % 60} мин.")


# Задача 3. Денежный формат
def task_03():
    try:
        print("Преобразование числа в денежный формат")
        value = read_number("Введите дробное число -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if value < 0:
            print("Ошибка! Число не может быть отрицательным")
        elif value > 1e12:
            print("Ошибка! Слишком большое число")
        else:
            # Считаем в копейках: + 0.5 защищает от ошибок дробных чисел (1.15 * 100 = 114.99...)
            total = int(value * 100 + 0.5)
            print(f"{value:.15g} руб. - это {total // 100} руб. {total % 100:02d} коп.")


# Задача 4. Фунты в килограммы
def task_04():
    try:
        print("Пересчет веса из фунтов в килограммы")
        pounds = read_number("Введите вес в фунтах и нажмите Enter -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        grams_in_pound = 405.9

        if pounds < 0:
            print("Ошибка! Вес не может быть отрицательным")
        elif pounds > 1e12:
            print("Ошибка! Слишком большое число")
        else:
            # По образцу доли грамма отбрасываются; 1e-6 защищает от ошибок дробных чисел
            grams = int(pounds * grams_in_pound + 1e-6)
            print(f"{pounds:.15g} фунт(а/ов) - это {grams // 1000} кг {grams % 1000} гр.")


# Задача 5. Сопротивление цепи
def task_05():
    try:
        print("Вычисление сопротивления электрической цепи")
        print("Введите исходные данные:")
        r1 = read_number("Величина первого сопротивления (Ом) -> ")
        r2 = read_number("Величина второго сопротивления (Ом) -> ")
        connection = int(input("Тип соединения (1-последовательное, 2-параллельное) -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        # Последовательно: R = R1 + R2, параллельно: R = R1 * R2 / (R1 + R2)
        if r1 <= 0 or r2 <= 0:
            print("Ошибка! Сопротивление должно быть больше нуля")
        elif connection == 1:
            print(f"Сопротивление цепи: {r1 + r2:.2f} Ом")
        elif connection == 2:
            print(f"Сопротивление цепи: {r1 * r2 / (r1 + r2):.2f} Ом")
        else:
            print("Ошибка! Неверный тип соединения")


# Задача 6. Вклад: ставка зависит от суммы (2 варианта)
def task_06():
    try:
        print("Доход")
        amount = read_number("Сумма, руб. -> ")
        months = int(input("Срок вклада, мес. -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if amount <= 0 or months <= 0:
            print("Ошибка! Сумма и срок должны быть больше нуля")
        else:
            # Сумма ровно 5000 руб. в условии не описана, принята ставка 13%
            rate = 10 if amount < 5000 else 13
            income = amount * rate / 100 * months / 12

            print("----------------------------")
            print(f"Сумма: {amount:.2f} руб.")
            print(f"Срок вклада: {months} мес.")
            print(f"Процент годовой: {rate}")
            print(f"Доход: {income:.2f} руб.")
            print(f"Сумма в конце срока вклада: {amount + income:.2f} руб.")


# Задача 7. Вклад: ставка зависит от суммы (3 варианта)
def task_07():
    try:
        print("Доход")
        amount = read_number("Сумма, руб. -> ")
        months = int(input("Срок вклада, мес. -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if amount <= 0 or months <= 0:
            print("Ошибка! Сумма и срок должны быть больше нуля")
        else:
            # Суммы ровно 5000 и 10 000 руб. в условии не описаны, отнесены к большей ставке
            if amount < 5000:
                rate = 9.0
            elif amount < 10000:
                rate = 11.0
            else:
                rate = 13.0

            income = amount * rate / 100 * months / 12

            print("------------------------------------------------------")
            print(f"Сумма: {amount:.2f} руб.")
            print(f"Срок вклада: {months} мес.")
            print(f"Процент годовой: {rate:.2f}")
            print(f"Доход: {income:.2f} руб.")
            print(f"Сумма в конце срока вклада: {amount + income:.2f} руб.")


# Задача 8. Печать фотографий
def task_08():
    try:
        print("Фотографии")
        photo_format = int(input("Формат (1 – 9х12; 2 – 10х15) -> "))
        quantity = int(input("Количество, шт. -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        price_9x12 = 2.50  # в условии цены нет, значение принято самостоятельно
        price_10x15 = 3.20

        if photo_format not in (1, 2):
            print("Ошибка! Неверный формат")
        elif quantity <= 0:
            print("Ошибка! Количество должно быть больше нуля")
        else:
            price = price_9x12 if photo_format == 1 else price_10x15
            total = price * quantity
            # Скидка 5% предоставляется, если фотографий больше 10
            discount = total * 0.05 if quantity > 10 else 0

            print("----------------------------")
            print(f"Цена: {price:.2f} руб.")
            print(f"Количество: {quantity} шт.")
            print(f"Сумма: {total:.2f} руб.")
            print(f"Скидка: {discount:.2f} руб.")
            print(f"К оплате: {total - discount:.2f} руб.")


# Задача 9. Ток в электрической цепи
def task_09():
    try:
        print("Ток в электрической цепи")
        power = read_number("Мощность, Вт -> ")
        voltage = read_number("Напряжение, В -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if voltage == 0:
            print("Ошибка! Напряжение не должно быть равно нулю")
        else:
            current = power / voltage + 0.0  # + 0.0 убирает вывод "-0.00"
            print(f"Ток: {current:.2f} А")


# Задача 10. Площадь кольца
def task_10():
    try:
        print("Введите исходные данные:")
        ring_radius = read_number("радиус кольца (см) -> ")
        hole_radius = read_number("радиус отверстия (см) -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if ring_radius <= 0 or hole_radius <= 0:
            print("Ошибка! Радиус должен быть больше нуля")
        elif hole_radius > ring_radius:
            print("Ошибка! Радиус отверстия больше радиуса кольца")
        elif hole_radius == ring_radius:
            print("Ошибка! Радиус отверстия равен радиусу кольца")
        else:
            # Площадь кольца: S = пи * (R^2 - r^2)
            area = math.pi * (ring_radius * ring_radius - hole_radius * hole_radius)
            print(f"Площадь кольца: {area:.2f} кв.см")


# Задача 11. Минуты и секунды в секунды
def task_11():
    try:
        value = read_number("Введите время (минут.секунд) -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if value < 0:
            print("Ошибка! Время не может быть отрицательным")
        elif value > 1000000:
            print("Ошибка! Слишком большое число")
        else:
            # Целая часть числа - минуты, две цифры после точки - секунды: 2.30 = 2 мин. 30 сек.
            minutes = int(value)
            seconds = int((value - minutes) * 100 + 0.5)

            if seconds > 60:
                print("Ошибка! Число секунд не может быть больше 60")
            else:
                print(f"{minutes} мин. {seconds} сек. - это {minutes * 60 + seconds} сек.")

    input("Для завершения нажмите Enter")


# Задача 12. Високосный год
def task_12():
    try:
        print("Введите год, например 2000,")
        year = int(input("и нажмите Enter -> "))
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        # Високосный год делится на 4, но не на 100, либо делится на 400
        if year <= 0:
            print("Ошибка! Год должен быть больше нуля")
        elif (year % 4 == 0 and year % 100 != 0) or year % 400 == 0:
            print(f"{year} год – високосный")
        else:
            print(f"{year} год – не високосный")

    input("Для завершения нажмите Enter")


# Задача 13. Квадратное уравнение
def task_13():
    try:
        print("Решение квадратного уравнения")
        prompt = "Введите в одной строке коэффициенты и нажмите Enter -> "
        a, b, c = map(float, input(prompt).split())
        if not all(map(math.isfinite, (a, b, c))):
            raise ValueError
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if a == 0:
            print("Ошибка! Коэффициент при второй степени неизвестного не должен быть равен нулю")
        else:
            # Корни: x = (-b +- sqrt(D)) / (2a). Дискриминант сравниваем с допуском,
            # потому что дробные коэффициенты дают его с небольшой погрешностью
            discriminant = b * b - 4 * a * c
            if discriminant < -1e-9:
                print("Уравнение не имеет действительных корней")
            elif abs(discriminant) <= 1e-9:
                x = -b / (2 * a) + 0.0  # + 0.0 убирает вывод "-0.000"
                print(f"Корень уравнения: x= {x:.3f}")
            else:
                root = math.sqrt(discriminant)
                x1 = (-b + root) / (2 * a) + 0.0
                x2 = (-b - root) / (2 * a) + 0.0
                print(f"Корни уравнения: x1= {x1:.3f} x2= {x2:.3f}")


# Задача 14. Скидка 10%
def task_14():
    try:
        print("Вычисление стоимости покупки с учетом скидки")
        total = read_number("Сумма покупки -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if total < 0:
            print("Ошибка! Сумма не может быть отрицательной")
        else:
            if total > 1000:
                print("Вам предоставляется скидка 10%")
                total = total * 0.9
            else:
                print("Скидка не предоставляется")

            print(f"Сумма покупки с учетом скидки: {total:.2f} руб.")


# Задача 15. Скидка 3% или 5%
def task_15():
    try:
        print("Вычисление стоимости покупки с учетом скидки")
        total = read_number("Введите сумму покупки и нажмите Enter -> ")
    except ValueError:
        print("Ошибка! Неверный формат числа")
    else:
        if total < 0:
            print("Ошибка! Сумма не может быть отрицательной")
        else:
            # Сначала проверяем больший порог
            if total > 1000:
                discount = 5
            elif total > 500:
                discount = 3
            else:
                discount = 0

            if discount > 0:
                print(f"Вам предоставляется скидка {discount}%")
                total = total * (100 - discount) / 100
            else:
                print("Скидка не предоставляется")

            print(f"Сумма с учетом скидки: {total:.2f} руб.")


TASKS = {
    "1": ("Доход по вкладу", task_01),
    "2": ("Минуты в часы и минуты", task_02),
    "3": ("Денежный формат", task_03),
    "4": ("Фунты в килограммы", task_04),
    "5": ("Сопротивление цепи", task_05),
    "6": ("Вклад: ставка зависит от суммы (2 варианта)", task_06),
    "7": ("Вклад: ставка зависит от суммы (3 варианта)", task_07),
    "8": ("Печать фотографий", task_08),
    "9": ("Ток в электрической цепи", task_09),
    "10": ("Площадь кольца", task_10),
    "11": ("Минуты и секунды в секунды", task_11),
    "12": ("Високосный год", task_12),
    "13": ("Квадратное уравнение", task_13),
    "14": ("Скидка 10%", task_14),
    "15": ("Скидка 3% или 5%", task_15),
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
