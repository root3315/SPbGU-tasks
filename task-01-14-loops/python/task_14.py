# Задача 14. Обработка последовательности
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


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
