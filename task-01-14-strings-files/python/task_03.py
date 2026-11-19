# Задача 3. Рост учеников
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
