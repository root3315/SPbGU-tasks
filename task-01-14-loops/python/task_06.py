# Задача 6. Платежи по кредиту
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    amount = read_number("Сумма кредита (руб.) -> ")
    months = int(input("Срок (мес.) -> "))
    rate = read_number("Процентная ставка (годовых) -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if amount <= 0 or months <= 0 or rate < 0:
        print("Ошибка! Сумма и срок должны быть больше нуля, а ставка не меньше нуля")
    elif amount > 10000000:
        print("Ошибка! Слишком большая сумма")
    elif rate > 100:
        print("Ошибка! Слишком большая ставка")
    elif months > 1200:
        print("Ошибка! Слишком большой срок")
    else:
        share = amount / months  # равная доля долга, возвращаемая каждый месяц
        total_interest = 0

        print("---------------------------------------")
        print("           Долг     Процент      Платеж")
        print("---------------------------------------")
        for month in range(1, months + 1):
            # Проценты начисляются на остаток долга за один месяц
            debt = amount - share * (month - 1)
            interest = debt * rate / 100 / 12
            total_interest += interest
            print(f"{month:3}{debt:12.2f}{interest:12.2f}{share + interest:12.2f}")
        print("---------------------------------------")
        print(f"Всего процентов: {total_interest:.2f}")
