# Задача 10. Число Пи
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
