# Задача 5. Сумма и среднее до нуля
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    count = 0
    total = 0

    print("Вычисление среднего арифметического последовательности положительных чисел.")
    print("Вводите после стрелки числа. Для завершения ввода введите ноль.")
    while True:
        number = read_number("> ")
        if number <= 0:
            break
        count += 1
        total += number
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if number < 0:
        print("Ошибка! Число должно быть положительным")
    elif count == 0:
        print("Не введено ни одного числа")
    else:
        print(f"Введено чисел: {count}")
        print(f"Сумма чисел: {total:.15g}")
        print(f"Среднее арифметическое: {total / count:.2f}")
