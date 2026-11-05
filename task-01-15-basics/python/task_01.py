# Задача 1. Доход по вкладу
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Вычисление дохода по вкладу")
    print("Введите исходные данные:")
    amount = read_number("Сумма вклада (руб.) -> ")
    months = int(input("Срок вклада (месяцев) -> "))
    rate = read_number("Процентная ставка (годовых) -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if amount <= 0 or months <= 0 or rate < 0:
        print("Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля")
    else:
        income = amount * rate / 100 * months / 12
        print("-------------------------------------")
        print(f"Доход: {income:.2f} руб.")
        print(f"Сумма по окончании срока вклада: {amount + income:.2f} руб.")
