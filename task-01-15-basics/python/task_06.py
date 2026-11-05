# Задача 6. Вклад: ставка зависит от суммы (2 варианта)
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Доход")
    amount = read_number("Сумма, руб. -> ")
    months = int(input("Срок вклада, мес. -> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if amount <= 0 or months <= 0:
        print("Ошибка! Сумма и срок должны быть больше нуля")
    else:
        # Сумма ровно 5000 руб. в условии не описана, принята ставка 13%
        rate = 10 if amount < 5000 else 13
        income = amount * rate / 100 * months / 12

        print("----------------------------")
        print(f"Сумма: {amount:.2f} руб.")
        print(f"Срок вклада: {months} мес.")
        print(f"Процент годовой: {rate}")
        print(f"Доход: {income:.2f} руб.")
        print(f"Сумма в конце срока вклада: {amount + income:.2f} руб.")
