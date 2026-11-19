# Задача 7. Минимальное число
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    count = 0
    minimum = 0

    print("Определение минимального числа в последовательности положительных чисел.")
    print("Вводите после стрелки числа. Для завершения ввода введите ноль.")
    while True:
        number = read_number("> ")
        if number <= 0:
            break
        # Первое число сразу считаем минимумом
        if count == 0 or number < minimum:
            minimum = number
        count += 1
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if number < 0:
        print("Ошибка! Число должно быть положительным")
    elif count == 0:
        print("Не введено ни одного числа")
    else:
        print(f"Минимальное число: {minimum:.15g}")
