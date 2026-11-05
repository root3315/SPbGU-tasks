# Задача 7. Вклад: ставка зависит от суммы (3 варианта)
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
        # Суммы ровно 5000 и 10 000 руб. в условии не описаны, отнесены к большей ставке
        if amount < 5000:
            rate = 9.0
        elif amount < 10000:
            rate = 11.0
        else:
            rate = 13.0

        income = amount * rate / 100 * months / 12

        print("------------------------------------------------------")
        print(f"Сумма: {amount:.2f} руб.")
        print(f"Срок вклада: {months} мес.")
        print(f"Процент годовой: {rate:.2f}")
        print(f"Доход: {income:.2f} руб.")
        print(f"Сумма в конце срока вклада: {amount + income:.2f} руб.")
