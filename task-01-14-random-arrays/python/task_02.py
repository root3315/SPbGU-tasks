# Задача 2. Три случайные последовательности
import random

count = 10

print("Случайные числа")
for _ in range(3):
    numbers = [random.randint(1, 10) for _ in range(count)]
    line = " ".join(str(number) for number in numbers)
    print(f"{line} сред. арифм.: {sum(numbers) / count:.2f}")
