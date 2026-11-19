# Задача 1. Средняя температура за неделю
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
