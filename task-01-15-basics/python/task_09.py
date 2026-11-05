# Задача 9. Ток в электрической цепи
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
