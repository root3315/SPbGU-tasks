# Задача 5. Сопротивление цепи
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Вычисление сопротивления электрической цепи")
    print("Введите исходные данные:")
    r1 = read_number("Величина первого сопротивления (Ом) -> ")
    r2 = read_number("Величина второго сопротивления (Ом) -> ")
    connection = int(input("Тип соединения (1-последовательное, 2-параллельное) -> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    # Последовательно: R = R1 + R2, параллельно: R = R1 * R2 / (R1 + R2)
    if r1 <= 0 or r2 <= 0:
        print("Ошибка! Сопротивление должно быть больше нуля")
    elif connection == 1:
        print(f"Сопротивление цепи: {r1 + r2:.2f} Ом")
    elif connection == 2:
        print(f"Сопротивление цепи: {r1 * r2 / (r1 + r2):.2f} Ом")
    else:
        print("Ошибка! Неверный тип соединения")
