# Задача 14. Среднее без min и max
import math

NUMBER_LIMIT = 1000000


def read_integers(prompt):
    """Читает целые числа, введённые в одной строке через пробел."""
    return [int(part) for part in input(prompt).split()]


size = 10

try:
    print("Среднее арифметическое без учета min и max значений")
    numbers = read_integers(f"Введите массив ({size} целых чисел в одной строке) -> ")
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if len(numbers) != size:
        print(f"Ошибка! Нужно ввести {size} чисел")
    elif not all(abs(number) <= NUMBER_LIMIT for number in numbers):
        print("Ошибка! Числа должны быть от -1000000 до 1000000")
    else:
        minimum = min(numbers)
        maximum = max(numbers)
        # Исключаем по одному вхождению минимума и максимума
        average = (sum(numbers) - minimum - maximum) / (size - 2)
        # Округляем до сотых, половина вверх: 10.375 -> 10.38
        average = math.floor(average * 100 + 0.5) / 100

        print("------------------------------")
        print(f"Минимальный элемент: {minimum}")
        print(f"Максимальный элемент: {maximum}")
        print(f"Среднее арифм. без учета min и max значений: {average:.2f}")
