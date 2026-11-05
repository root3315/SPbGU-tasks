# Задача 15. Скидка 3% или 5%
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Вычисление стоимости покупки с учетом скидки")
    total = read_number("Введите сумму покупки и нажмите Enter -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if total < 0:
        print("Ошибка! Сумма не может быть отрицательной")
    else:
        # Сначала проверяем больший порог
        if total > 1000:
            discount = 5
        elif total > 500:
            discount = 3
        else:
            discount = 0

        if discount > 0:
            print(f"Вам предоставляется скидка {discount}%")
            total = total * (100 - discount) / 100
        else:
            print("Скидка не предоставляется")

        print(f"Сумма с учетом скидки: {total:.2f} руб.")
