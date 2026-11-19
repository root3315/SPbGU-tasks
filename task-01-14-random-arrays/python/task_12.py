# Задача 12. Ненулевые элементы
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
