# Задача 5. Массив 3х5
import math

NUMBER_LIMIT = 1000000


def read_numbers(prompt):
    """Читает дробные числа, введённые в одной строке через пробел."""
    numbers = [float(part) for part in input(prompt).split()]
    if not all(math.isfinite(number) for number in numbers):
        raise ValueError
    return numbers


def in_limit(numbers):
    """Проверяет, что все числа не больше NUMBER_LIMIT по модулю."""
    return all(abs(number) <= NUMBER_LIMIT for number in numbers)


rows, columns = 3, 5
matrix = []

try:
    print("Ввод и обработка массива (3х5)")
    print("Введите массив по строкам")
    for i in range(rows):
        row = read_numbers(f"Строка {i + 1} -> ")
        if len(row) != columns:
            break
        matrix.append(row)
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if len(matrix) != rows:
        print(f"Ошибка! В строке должно быть {columns} чисел")
    elif not all(in_limit(row) for row in matrix):
        print("Ошибка! Числа должны быть от -1000000 до 1000000")
    else:
        title = "Массив: "
        print("-------------------------------------")
        for i, row in enumerate(matrix):
            # Первая строка идёт после заголовка, остальные выровнены под неё
            prefix = title if i == 0 else " " * len(title)
            print(prefix + " ".join(f"{number:.15g}" for number in row))

        print("Среднее арифметическое:")
        for i, row in enumerate(matrix):
            print(f"Строка {i + 1}: {sum(row) / columns:.2f}")

input("Для завершения нажмите Enter")
