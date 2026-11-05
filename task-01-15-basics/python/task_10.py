# Задача 10. Площадь кольца
import math


def read_number(prompt):
    """Читает дробное число; бесконечность и nan считаются ошибкой ввода."""
    value = float(input(prompt))
    if not math.isfinite(value):
        raise ValueError
    return value


try:
    print("Введите исходные данные:")
    ring_radius = read_number("радиус кольца (см) -> ")
    hole_radius = read_number("радиус отверстия (см) -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if ring_radius <= 0 or hole_radius <= 0:
        print("Ошибка! Радиус должен быть больше нуля")
    elif hole_radius > ring_radius:
        print("Ошибка! Радиус отверстия больше радиуса кольца")
    elif hole_radius == ring_radius:
        print("Ошибка! Радиус отверстия равен радиусу кольца")
    else:
        # Площадь кольца: S = пи * (R^2 - r^2)
        area = math.pi * (ring_radius * ring_radius - hole_radius * hole_radius)
        print(f"Площадь кольца: {area:.2f} кв.см")
