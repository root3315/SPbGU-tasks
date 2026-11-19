# Задача 3. Стоимость яблок
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Введите цену одного килограмма и нажмите Enter")
    print("(копейки от рублей отделяйте точкой)")
    price = read_number("-> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if price <= 0:
        print("Ошибка! Цена должна быть больше нуля")
    elif price > 1000000:
        print("Ошибка! Слишком большая цена")
    else:
        print("-------------------------")
        print("Вес, гр.  Стоимость, руб.")
        print("-------------------------")
        for weight in range(100, 1001, 100):
            # Округляем до копеек; 1e-6 защищает от ошибок дробных чисел
            kopecks = int(price * weight / 10 + 0.5 + 1e-6)
            print(f"{weight:8}{kopecks / 100:17.2f}")
        print("-------------------------")
