# Задача 7. Цельсий и Фаренгейт
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    t1 = read_number("t1 –> ")
    t2 = read_number("t2 –> ")
    dt = read_number("dt –> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if dt <= 0:
        print("Ошибка! Шаг должен быть больше нуля")
    elif t1 > t2:
        print("Ошибка! Начальная температура больше конечной")
    elif (t2 - t1) / dt > 10000:
        print("Ошибка! Слишком много строк в таблице")
    else:
        # Температуру считаем через номер шага: так дробная ошибка не накапливается.
        # 1e-9 нужно, чтобы последний шаг не потерялся из-за такой же ошибки в делении
        steps = int((t2 - t1) / dt + 1e-9)

        print("----------------")
        print("    C         F")
        print("----------------")
        for i in range(steps + 1):
            celsius = round(t1 + i * dt, 9) + 0.0  # округление убирает вывод "-0.00"
            fahrenheit = 9 / 5 * celsius + 32
            print(f"{celsius:6.2f}{fahrenheit:10.2f}")
