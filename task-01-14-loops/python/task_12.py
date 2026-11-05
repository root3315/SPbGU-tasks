# Задача 12. Факториал
try:
    print("Вычисление факториала")
    print("Введите число, факториал которого надо вычислить")
    number = int(input("-> "))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if number < 0:
        print("Ошибка! Число не может быть отрицательным")
    elif number > 20:
        print("Ошибка! Слишком большое число")
    else:
        factorial = 1
        for i in range(2, number + 1):
            factorial *= i
        print(f"Факториал {number} равен {factorial}")
