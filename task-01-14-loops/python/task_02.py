# Задача 2. Заправка автомобиля
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Бензин")
    print("Марка бензина:")
    print("1 – 92")
    print("2 – 95")
    print("3 – 98")
    print("4 – DT")
    choice = int(input("Ваш выбор –> "))
    liters = read_number("Литров –> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    # В условии есть только итог для марки 95 (20.30 руб.), остальные цены приняты самостоятельно
    prices = {1: 19.50, 2: 20.30, 3: 22.10, 4: 18.70}

    if choice not in prices:
        print("Ошибка! Неверный выбор марки")
    elif liters <= 0:
        print("Ошибка! Количество литров должно быть больше нуля")
    elif liters > 1000000:
        print("Ошибка! Слишком большое количество")
    else:
        price = prices[choice]
        # Округляем до копеек; 1e-6 защищает от ошибок дробных чисел (18.70 * 0.25 = 4.675)
        total = int(price * liters * 100 + 0.5 + 1e-6) / 100

        print("-----------------------------")
        print(f"Цена за литр: {price:.2f} руб.")
        print(f"Литров: {liters:.15g}")
        print(f"К оплате: {total:.2f} руб.")
