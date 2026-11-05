# Задача 4. Фунты в килограммы
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Пересчет веса из фунтов в килограммы")
    pounds = read_number("Введите вес в фунтах и нажмите Enter -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    grams_in_pound = 405.9

    if pounds < 0:
        print("Ошибка! Вес не может быть отрицательным")
    elif pounds > 1e12:
        print("Ошибка! Слишком большое число")
    else:
        # По образцу доли грамма отбрасываются; 1e-6 защищает от ошибок дробных чисел
        grams = int(pounds * grams_in_pound + 1e-6)
        print(f"{pounds:.15g} фунт(а/ов) - это {grams // 1000} кг {grams % 1000} гр.")
