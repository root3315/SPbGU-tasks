# Задача 13. Среднее арифметическое пяти чисел
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
