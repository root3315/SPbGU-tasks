# Задача 6. Максимальное число
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    maximum = 0  # все числа положительные, поэтому любое из них больше нуля

    print("Определение максимального числа из последовательности положительных чисел.")
    print("Вводите числа после стрелки. Для завершения ввода введите ноль.")
    while True:
        number = read_number("> ")
        if number <= 0:
            break
        maximum = max(maximum, number)
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if number < 0:
        print("Ошибка! Число должно быть положительным")
    elif maximum == 0:
        print("Не введено ни одного числа")
    else:
        print(f"Максимальное число: {maximum:.15g}")
