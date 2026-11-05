# Задача 11. Минуты и секунды в секунды
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    value = read_number("Введите время (минут.секунд) -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if value < 0:
        print("Ошибка! Время не может быть отрицательным")
    elif value > 1000000:
        print("Ошибка! Слишком большое число")
    else:
        # Целая часть числа - минуты, две цифры после точки - секунды: 2.30 = 2 мин. 30 сек.
        minutes = int(value)
        seconds = int((value - minutes) * 100 + 0.5)

        if seconds > 60:
            print("Ошибка! Число секунд не может быть больше 60")
        else:
            print(f"{minutes} мин. {seconds} сек. - это {minutes * 60 + seconds} сек.")

input("Для завершения нажмите Enter")
