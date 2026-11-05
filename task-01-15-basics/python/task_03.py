# Задача 3. Денежный формат
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
