# Задача 14. Скидка 10%
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Вычисление стоимости покупки с учетом скидки")
    total = read_number("Сумма покупки -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if total < 0:
        print("Ошибка! Сумма не может быть отрицательной")
    else:
        if total > 1000:
            print("Вам предоставляется скидка 10%")
            total = total * 0.9
        else:
            print("Скидка не предоставляется")

        print(f"Сумма покупки с учетом скидки: {total:.2f} руб.")
