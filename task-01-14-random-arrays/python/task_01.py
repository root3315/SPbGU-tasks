# Задача 1. Десять случайных чисел
import random

count = 10
total = 0

print("Случайные числа")
for _ in range(count):
    number = random.randint(1, 10)
    print(number)
    total += number
print(f"Сред. арифм.: {total / count:.2f}")
