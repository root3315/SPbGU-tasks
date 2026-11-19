# Задача 4. Результаты экзамена
import math

grades = ("пятерок", "четверок", "троек", "двоек")
counts = []

try:
    print("Обработка результатов экзамена")
    print("Введите исходные данные:")
    for grade in grades:
        counts.append(int(input(f"{grade}-> ")))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    total = sum(counts)

    if min(counts) < 0:
        print("Ошибка! Количество не может быть отрицательным")
    elif max(counts) > 100000:
        print("Ошибка! Слишком большое количество")
    elif total == 0:
        print("Ошибка! Не введено ни одной оценки")
    else:
        print("--------------------------")
        print("Результаты экзамена:")
        for grade, count in zip(grades, counts):
            # Процент с точностью до десятых, половина округляется вверх (6.25 -> 6.3)
            percent = math.floor(count * 1000 / total + 0.5) / 10
            print(f"{grade} {percent:.1f}%")
        print("--------------------------")

input("Для завершения нажмите Enter")
