# Задача 13. Минимальный элемент массива
try:
    size = 5

    print("Поиск минимального элемента массива")
    print(f"Введите в одной строке {size} целых чисел и нажмите Enter")
    numbers = [int(part) for part in input("-> ").split()]
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if len(numbers) != size:
        print(f"Ошибка! Нужно ввести ровно {size} чисел")
    elif any(abs(number) > 10**9 for number in numbers):
        print("Ошибка! Слишком большое по модулю число")
    else:
        print(f"Минимальный элемент массива: {min(numbers)}")
