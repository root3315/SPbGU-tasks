# Задача 14. Среднее ненулевых элементов
try:
    size = 10

    print(f"Введите элементы массива ({size} целых чисел в одной строке) и нажмите Enter")
    numbers = [int(part) for part in input("-> ").split()]
except ValueError:
    print("Ошибка! Неверный формат числа")
else:
    if len(numbers) != size:
        print(f"Ошибка! Нужно ввести ровно {size} чисел")
    elif any(abs(number) > 10**9 for number in numbers):
        print("Ошибка! Слишком большое по модулю число")
    else:
        total = sum(numbers)
        nonzero = sum(1 for number in numbers if number != 0)

        print("-------------------------------")
        if nonzero == 0:
            print("Ненулевых элементов нет")
        else:
            print(f"Сумма элементов массива: {total}")
            print(f"Количество ненулевых элементов: {nonzero}")
            print(f"Среднее арифметическое ненулевых элементов: {total / nonzero:.2f}")
