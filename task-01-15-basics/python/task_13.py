# Задача 13. Квадратное уравнение
import math

try:
    print("Решение квадратного уравнения")
    prompt = "Введите в одной строке коэффициенты и нажмите Enter -> "
    a, b, c = map(float, input(prompt).split())
    if not all(map(math.isfinite, (a, b, c))):
        raise ValueError
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if a == 0:
        print("Ошибка! Коэффициент при второй степени неизвестного не должен быть равен нулю")
    else:
        # Корни: x = (-b +- sqrt(D)) / (2a). Дискриминант сравниваем с допуском,
        # потому что дробные коэффициенты дают его с небольшой погрешностью
        discriminant = b * b - 4 * a * c
        if discriminant < -1e-9:
            print("Уравнение не имеет действительных корней")
        elif abs(discriminant) <= 1e-9:
            x = -b / (2 * a) + 0.0  # + 0.0 убирает вывод "-0.000"
            print(f"Корень уравнения: x= {x:.3f}")
        else:
            root = math.sqrt(discriminant)
            x1 = (-b + root) / (2 * a) + 0.0
            x2 = (-b - root) / (2 * a) + 0.0
            print(f"Корни уравнения: x1= {x1:.3f} x2= {x2:.3f}")
