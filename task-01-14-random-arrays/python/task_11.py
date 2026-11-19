# Задача 11. Массив из семи чисел
try:
    size = 7
    numbers = []

    print("Ввод массива целых чисел")
    print("После ввода каждого числа нажмите Enter")
    for i in range(size):
        numbers.append(int(input(f"a[{i}] -> ")))
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if any(abs(number) > 10**9 for number in numbers):
        print("Ошибка! Слишком большое по модулю число")
    else:
        print("Массив:", *numbers)
        print(f"Среднее арифметическое: {sum(numbers) / size:.2f}")
